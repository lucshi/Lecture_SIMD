#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N           0xfffffff
#define SEED        0x1234


float *a, *b, *c;


void gen_data(void) {
    unsigned i;
    a = (float*) malloc(N*sizeof(float));
    b = (float*) malloc(N*sizeof(float));
    c = (float*) malloc(N*sizeof(float));
    
    srand(SEED);
    for(i=0; i<N; i++) {
        a[i] = b[i] = (float)(rand() % N);
    }
}

void free_data(void) {
    free(a);
    free(b);
    free(c);
}

void multiply_group(void) {
    unsigned i;
    for(i=0; i<(N & ((~(unsigned)0x3))); i+=4) {
        c[i]   = a[i]   * b[i];
        c[i+1] = a[i+1] * b[i+1];
        c[i+2] = a[i+2] * b[i+2];
        c[i+3] = a[i+3] * b[i+3];
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
    multiply_group();
    msecs = (clock()-start)/1000;
    print_data();
    printf("Execution time = %2.3lf ms\n", msecs);

    free_data();
    return 0;
}
