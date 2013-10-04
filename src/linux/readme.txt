Instructions to compile Linux GPU-Accelerated LIBSVM

1. Install the NVIDIA drivers, CUDA toolkit and GPU Computing SDK code samples. You can find them all in one package here: 

https://developer.nvidia.com/cuda-downloads (Version 5.5)

You may need some additional packets to be installed in order to complete the installation above. 

A very helpful and descriptive guide is on the CUDA webpage: 

http://docs.nvidia.com/cuda/cuda-getting-started-guide-for-linux/index.html

Make sure you have followed every step that is relevant to your system, like declaring $PATH and $LD_LIBRARY_PATH on your bash configuration file.

2. Copy this folder anywhere you like.

3. Use the Makefile found inside this folder.

4. Find the "svm-train-gpu" executable inside this folder.


Troubleshooting

1. Nearly all problems are resolved by reading carefully through the nvidia guidelines.

2. When making, there is a chance a "cannot find cublas_v2.h" or "cuda_runtime.h" error to arise. Find where these files are located (Default path is: "/usr/local/cuda-5.5/include") and replace the paths on the header files in "kernel_matrix_calculation.c" file with your system paths.

Or you can change the location of the default CUDA toolkit path on the makefile (CUDA_PATH ?= "/usr/local/cuda-5.5") to your cuda toolkit path
