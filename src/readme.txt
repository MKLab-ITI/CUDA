Instructions to compile Linux GPU-Accelerated LIBSVM

1. Install the NVIDIA drivers, CUDA toolkit and GPU Computing SDK code samples. You can find them in:

http://developer.nvidia.com/object/cuda_3_2_downloads.html (January 2011)

You may need some additional packets to be installed in order to complete the installations above. 
Please refer to the web for more details.

2. Copy this folder to "/NVIDIA_GPU_Computing_SDK/C/src"

3. Use the Makefile found in "/NVIDIA_GPU_Computing_SDK/C"

4. Find the "svm-train-gpu" executable in /NVIDIA_GPU_Computing_SDK/C/bin/linux/release


Troubleshooting

1.You may need some additional packets to be installed in order to complete the installations above. 
Please refer to the web for more details according to error messages you get.


2.The following error "error while loading shared libraries: libcudart.so.3: cannot open shared object file: No such file or directory"
can be resolved with:

export PATH=/usr/local/cuda/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda/lib:$LD_LIBRARY_PATH

