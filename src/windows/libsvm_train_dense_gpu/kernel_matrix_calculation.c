#include <cuda_runtime.h>
#include "cublas_v2.h"

// Scalars
const float alpha = 1;
const float beta = 0;

void ckm( struct svm_problem *prob, struct svm_problem *pecm, float *gamma  )
{
	cublasStatus_t status;

	double g_val = *gamma;

	long int nfa;
	
	int len_tv;
	int ntv;
	int i_v;
	int i_el;
	int i_r, i_c;
	int trvei;

	double *tv_sq;
	double *v_f_g;

	float *tr_ar;
	float *tva, *vtm, *DP;
	float *g_tva = 0, *g_vtm = 0, *g_DotProd = 0;

	cudaError_t cudaStat;   
	cublasHandle_t handle;
	
	status = cublasCreate(&handle);

	len_tv = prob-> x[0].dim;
	ntv   = prob-> l;

	nfa = len_tv * ntv; 

	tva = (float*) malloc ( len_tv * ntv* sizeof(float) );
	vtm = (float*) malloc ( len_tv * sizeof(float) );
	DP  = (float*) malloc ( ntv * sizeof(float) );

	tr_ar = (float*) malloc ( len_tv * ntv* sizeof(float) );

	tv_sq = (double*) malloc ( ntv * sizeof(double) );

	v_f_g  = (double*) malloc ( ntv * sizeof(double) );

	for ( i_r = 0; i_r < ntv ; i_r++ )
	{				 
		for ( i_c = 0; i_c < len_tv; i_c++ ) 
			tva[i_r * len_tv + i_c] = (float)prob-> x[i_r].values[i_c];
	}

	cudaStat = cudaMalloc((void**)&g_tva, len_tv * ntv * sizeof(float));
	
	if (cudaStat != cudaSuccess) {
		free( tva );
		free( vtm );
		free( DP  );

		free( v_f_g );
		free( tv_sq );

		cudaFree( g_tva );
		cublasDestroy( handle );	
	
		fprintf (stderr, "!!!! Device memory allocation error (A)\n");
		getchar();
		return;
    }

	cudaStat = cudaMalloc((void**)&g_vtm, len_tv * sizeof(float));

	cudaStat = cudaMalloc((void**)&g_DotProd, ntv * sizeof(float));

	for( i_r = 0; i_r < ntv; i_r++ )
		for( i_c = 0; i_c < len_tv; i_c++ )
			tr_ar[i_c * ntv + i_r] = tva[i_r * len_tv + i_c];

	// Copy cpu vector to gpu vector
	status = cublasSetVector( len_tv * ntv, sizeof(float), tr_ar, 1, g_tva, 1 );
    
	free( tr_ar );

	for( i_v = 0; i_v < ntv; i_v++ )
	{
		tv_sq[ i_v ] = 0;
		for( i_el = 0; i_el < len_tv; i_el++ )
			tv_sq[i_v] += pow( tva[i_v*len_tv + i_el], (float)2.0 );
	}



	for ( trvei = 0; trvei < ntv; trvei++ )
	{
		status = cublasSetVector( len_tv, sizeof(float), &tva[trvei * len_tv], 1, g_vtm, 1 );
		
		status = cublasSgemv( handle, CUBLAS_OP_N, ntv, len_tv, &alpha, g_tva, ntv , g_vtm, 1, &beta, g_DotProd, 1 );

		status = cublasGetVector( ntv, sizeof(float), g_DotProd, 1, DP, 1 );

		for ( i_c = 0; i_c < ntv; i_c++ )
			v_f_g[i_c] = exp( -g_val * (tv_sq[trvei] + tv_sq[i_c]-((double)2.0)* (double)DP[i_c] ));
		

		pecm-> x[trvei].values[0] = trvei + 1;
		
		for ( i_c = 0; i_c < ntv; i_c++ )
			pecm-> x[trvei].values[i_c + 1] = v_f_g[i_c];				
		

	}

	free( tva );
	free( vtm );
	free( DP  );
	free( v_f_g );
	free( tv_sq );

	cudaFree( g_tva );
	cudaFree( g_vtm );
	cudaFree( g_DotProd );

	cublasDestroy( handle );
}

void cal_km( struct svm_problem * p_km)
{
	float gamma = param.gamma;

	ckm(&prob, p_km, &gamma);
}