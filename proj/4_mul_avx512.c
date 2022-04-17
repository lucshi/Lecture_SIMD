#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <x86intrin.h>

#define N           0xfffffff
#define SEED        0x1234


float *a, *b, *c;

void gen_data(void) {
    unsigned i;
    a = (float*) _mm_malloc(N*sizeof(float), 32);
    b = (float*) _mm_malloc(N*sizeof(float), 32);
    c = (float*) _mm_malloc(N*sizeof(float), 32);
    
    srand(SEED);
    for(i=0; i<N; i++) {
        a[i] = b[i] = (float)(rand() % N);
    }
}

void free_data(void) {
    _mm_free(a);
    _mm_free(b);
    _mm_free(c);
}

void multiply_avx512(void) {
    unsigned i;
    __m512 A, B, C;

    for(i=0; i<(N & ((~(unsigned)0x0E))); i+=16) {
        A = _mm512_load_ps(&a[i]);
        B = _mm512_load_ps(&b[i]);
        C = _mm512_mul_ps(A, B);
        _mm512_store_ps(&c[i], C);
    }
    for(; i<N; i++) {
        c[i] = a[i] * b[i];
    }
}

void print_data(void) {
    printf("%f, %f, %f, %f\n", c[0], c[1], c[N-2], c[N-1]);
}


int main(void) {
    clock_t start;
    double msecs;
    gen_data(); 

    start = clock();
    multiply_avx512();
    msecs = (clock()-start)/1000;
    print_data();
    printf("Execution time = %2.3lf ms\n", msecs);

    free_data();
    return 0;
}
