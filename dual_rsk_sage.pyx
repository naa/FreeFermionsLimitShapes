from libc.stdlib cimport malloc, free

import numpy as np
from numpy import int8, int32, double
from numpy cimport int8_t, int32_t, double_t, int64_t

cdef struct tworows:
    int *u
    int *v
    long len
ctypedef tworows tworows_t

cdef extern from "dual-rsk-for-sage.c":
    tworows_t* matrix_to_tworows(int n,int k,int8_t *a)
    void rsk(tworows_t *tr, long n, long k, int32_t *trtabP, int32_t *tabQ)
    int8_t (*make_zero_one_matrix(int n,int k,  double_t *xs, double_t *ys, int seed))[] 

from libc.stdlib cimport rand, srand, RAND_MAX
from libc.time cimport time
from os import getpid

def dual_rsk_with_weights(xs:np.ndarray,ys:np.ndarray,seed=117):
    cdef int n=len(xs)
    cdef int k=len(ys)

    cdef:
        int8_t *mat
        double_t[:] xs_view=xs
        double_t *xss=&xs_view[0]
        double_t[:] ys_view=ys
        double_t *yss=&ys_view[0]

    mat=<int8_t *>make_zero_one_matrix(n,k,xss,yss,seed)
    cdef tworows_t* tr=matrix_to_tworows(n,k, <int8_t *>mat)
    free(mat)
    trtableP=np.zeros((n,k),dtype=int32)
    tableQ=np.zeros((n,k),dtype=int32)
    cdef:
        int32_t[:, :] tabP_view=trtableP
        int32_t *c_int_P=&tabP_view[0,0]
        int32_t[:, :] tabQ_view=tableQ
        int32_t *c_int_Q=&tabQ_view[0,0]
        
    rsk(tr,n,k,c_int_P,c_int_Q)
    free(tr)    
    return ([list(pp[np.nonzero(pp)]) for pp in  np.transpose(trtableP)],[list(pp[np.nonzero(pp)]) for pp in tableQ])

def dual_rsk(matrix:np.ndarray):
    cdef int n=len(matrix)
    cdef int k=0
    if n>0:
        k=len(matrix[0])

    cdef:
        int8_t[:, :] cython_view = matrix
        int8_t *c_integers_array = &cython_view[0, 0]
        int8_t[] *c_2d_array = <int8_t[] *>c_integers_array

    cdef tworows_t *tr=matrix_to_tworows(n,k, c_integers_array)
    trtableP=np.zeros((n,k),dtype=int32)
    tableQ=np.zeros((n,k),dtype=int32)
    cdef:
        int32_t[:, :] tabP_view=trtableP
        int32_t *c_int_P=&tabP_view[0,0]
        int32_t[:, :] tabQ_view=tableQ
        int32_t *c_int_Q=&tabQ_view[0,0]
        
    rsk(tr,n,k,c_int_P,c_int_Q)
    free(tr)

    return ([list(pp[np.nonzero(pp)]) for pp in np.transpose(trtableP)],[list(pp[np.nonzero(pp)]) for pp in tableQ])
