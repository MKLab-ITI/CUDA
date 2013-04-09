CUDA: GPU-accelerated LIBSVM
====
**LIBSVM Accelerated with GPU using the CUDA Framework**

GPU-accelerated LIBSVM is a modification of the [original LIBSVM](http://www.csie.ntu.edu.tw/~cjlin/libsvm/) that exploits the CUDA framework to significantly reduce processing time while producing identical results. The functionality and interface of LIBSVM remains the same. The modifications were done in the kernel computation, that is now performed using the GPU.

Watch a [short video](http://www.youtube.com/watch?v=Fl99tQQd55U) on the capabilities of the GPU-accelerated LIBSVM package

FEATURES
----

Mode Supported

    C-SVC classification with RBF kernel

Functionality / User interface

    Same as LIBSVM

PREREQUISITES
----
    LIBSVM prerequisites
    NVIDIA Graphics card with CUDA support
    Latest NVIDIA drivers for GPU

PERFORMANCE COMPARISON
----
To showcase the performance gain using the GPU-accelerated LIBSVM we present an example run.

PC Setup

    Quad core Intel Q6600 processor
    3.5GB of DDR2 RAM
    Windows-XP 32-bit OS

Input Data

    TRECVID 2007 Dataset for the detection of high level features in video shots
    Training vectors with a dimension of 6000
    20 different feature models with a variable number of input training vectors ranging from 36 up to 3772

Classification parameters

    c-svc
    RBF kernel
    Parameter optimization using the easy.py script provided by LIBSVM.
    4 local workers
    
Discussion

    GPU-accelerated LIBSVM gives a performance gain depending on the size of input data set. This gain is increasing dramatically with the size of the dataset.
    Please take into consideration input data size limitations that can occur from the memory capacity of the graphics card that is used.    
