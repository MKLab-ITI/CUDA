

#include "/usr/local/cuda/include/cublas.h"


void ckm( struct svm_problem *prob, struct svm_problem *pecm, float *gamma  )
{

	cublasStatus status;

	double g_val = *gamma;


	long int nfa;
	float * tr_ar ;
	double *tv_sq;

	float * tva, *vtm, * DP;
	int len_tv;
	int ntv;
	double *v_f_g;
	int i_v;
	int i_el;

	int i_r, i_c;

	int trvei;

	float * g_tva, *g_vtm, * g_DotProd;

	len_tv = prob->x[0].dim;
	ntv   = prob->l;

	nfa = len_tv * ntv; 

	tva = (float*)malloc( len_tv * ntv* sizeof(float));
	vtm = (float*)malloc( len_tv * sizeof(float));
	DP  = (float*)malloc( ntv * sizeof(float));

	tr_ar = (float*)malloc( len_tv * ntv* sizeof(float));

	tv_sq =  (double*) malloc( ntv * sizeof(double) );

	v_f_g  = (double*) malloc( ntv * sizeof(double) );

	for( i_r=0; i_r < ntv ;i_r++)
	{				 
		for ( i_c = 0; i_c < len_tv; i_c++) 
				tva[i_r * len_tv + i_c] = (float)prob->x[i_r].values[i_c];
	}

	cublasInit();

	//cublasAlloc(len_tv * ntv, sizeof(float), (void**)&g_tva);
	
	status = cublasAlloc(len_tv * ntv, sizeof(float), (void**)&g_tva);
    if (status != CUBLAS_STATUS_SUCCESS) {
				free( tva );
				free( vtm     );
				free( DP  );

				free( v_f_g );
				free( tv_sq );

				cublasFree(g_tva);

				cublasShutdown();		
		
                fprintf (stderr, "!!!! device memory allocation error (A)\n");
                getchar();
                return;
        }

	
	
	cublasAlloc(len_tv, sizeof(float), (void**)&g_vtm);

	cublasAlloc(ntv, sizeof(float), (void**)&g_DotProd);

	for( i_r=0; i_r<ntv; i_r++)
		for( i_c=0; i_c<len_tv; i_c++)
			tr_ar[i_c * ntv + i_r] = tva[i_r * len_tv + i_c];

	cublasSetVector(len_tv * ntv, sizeof(float), tr_ar, 1, g_tva, 1);

	free( tr_ar );

	for( i_v=0; i_v< ntv; i_v++)
	{
		tv_sq[ i_v ] = 0;
		for( i_el=0; i_el < len_tv; i_el++)
			tv_sq[i_v] += pow( tva[i_v*len_tv + i_el], (float)2.0);
	}


	for ( trvei = 0; trvei < ntv; trvei++)
	{
		cublasSetVector(len_tv, sizeof(float), &tva[trvei*len_tv], 1, g_vtm, 1);

		cublasSgemv('n', ntv, len_tv, 1, g_tva, ntv , g_vtm, 1, 0, g_DotProd, 1);

		cublasGetVector(ntv, sizeof(float), g_DotProd, 1, DP, 1);

		for( i_c =0; i_c< ntv; i_c++ )
		{
			v_f_g[i_c] = 
				exp( -g_val * (tv_sq[trvei] + tv_sq[i_c]-((double)2.0)* (double)DP[i_c] ));
		}

			pecm->x[trvei].values[0] = trvei+1;
			for( i_c =0; i_c< ntv; i_c++ )
			{
				pecm->x[trvei].values[i_c+1] = v_f_g[i_c];				
			}

	}

	free( tva );
	free( vtm     );
	free( DP  );

	free( v_f_g );

	free( tv_sq );

	cublasFree(g_tva);
	cublasFree(g_vtm);
	cublasFree(g_DotProd);

	cublasShutdown();

}


void cal_km( struct svm_problem * p_km)
{
	float gamma = param.gamma;

	ckm(&prob, p_km, &gamma);
}

