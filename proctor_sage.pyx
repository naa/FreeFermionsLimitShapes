from libc.stdlib cimport malloc, free

import numpy as np
from numpy import int8, int32, double
from numpy cimport int8_t, int32_t, double_t, int64_t

cdef struct word:
    int* v
    long len
ctypedef word word_t

cdef extern from "proctor.c":
    word_t* matrix_to_words(int n,int k,int8_t *a)
    void insert_words(word_t *words, long n, long m, int32_t *tabP, int32_t *tabQ)
    int8_t (*make_zero_one_matrix(int n,int k,  double_t *xs, double_t *ys, int seed))[] 

from libc.stdlib cimport rand, srand, RAND_MAX
from libc.time cimport time
from os import getpid

def proctor_insertion_weights(xs:np.ndarray,ys:np.ndarray,seed=117):
    cdef int n=len(xs)
    cdef int k=len(ys)

    cdef:
        int8_t *mat
        double_t[:] xs_view=xs
        double_t *xss=&xs_view[0]
        double_t[:] ys_view=ys
        double_t *yss=&ys_view[0]

    mat=<int8_t *>make_zero_one_matrix(n,2*k,xss,yss,seed)
    cdef word_t* tr=matrix_to_words(n,2*k, <int8_t *>mat)
    free(mat)
    tableP=np.zeros((n,2*k),dtype=int32)
    trtableQ=np.zeros((n,2*k),dtype=int32)
    cdef:
        int32_t[:, :] tabP_view=tableP
        int32_t *c_int_P=&tabP_view[0,0]
        int32_t[:, :] tabQ_view=trtableQ
        int32_t *c_int_Q=&tabQ_view[0,0]
        
    insert_words(tr,n,k,c_int_P,c_int_Q)
    free(tr)
    return ([list(pp[np.nonzero(pp)]) for pp in tableP],[list(pp[np.nonzero(pp)]) for pp in np.transpose(trtableQ)])

def proctor_insertion(matrix:np.ndarray):
    cdef int n=len(matrix)
    cdef int k=0
    if n>0:
        k=len(matrix[0])

    cdef:
        int8_t[:, :] cython_view = matrix
        int8_t *c_integers_array = &cython_view[0, 0]
        int8_t[] *c_2d_array = <int8_t[] *>c_integers_array

    cdef word_t* tr=matrix_to_words(n,k, c_integers_array)
    tableP=np.zeros((n,k),dtype=int32)
    trtableQ=np.zeros((n,k),dtype=int32)
    cdef:
        int32_t[:, :] tabP_view=tableP
        int32_t *c_int_P=&tabP_view[0,0]
        int32_t[:, :] tabQ_view=trtableQ
        int32_t *c_int_Q=&tabQ_view[0,0]
        
    insert_words(tr,n,k//2,c_int_P,c_int_Q)
    free(tr)
    return ([list(pp[np.nonzero(pp)]) for pp in tableP],[list(pp[np.nonzero(pp)]) for pp in np.transpose(trtableQ)])
