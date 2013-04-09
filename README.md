CUDA
====

GPU-accelerated LIBSVM is a modification of the original LIBSVM that exploits the CUDA framework to significantly reduce processing time while producing identical results. The functionality and interface of LIBSVM remains the same. The modifications were done in the kernel computation, that is now performed using the GPU.