#include <stdio.h>
#include "maleta.h"
#include <pthread.h>
#include <limits.h>
#include <stdlib.h>

typedef struct{
    double* w;
    double* v;
    int* z;
    int n, kp;
    double maxW, best;
}Args;

void* thread_function(void *params){
    Args *p = (Args *)params;
    double* w = p->w;
    double* v = p->v;
    int* z = p->z;
    int n = p -> n, kp = p -> kp;
    double maxW = p -> maxW;
    p -> best = llenarMaletaSec(w, v, z, n, maxW, kp);
    return NULL;
}

double llenarMaletaPar(double w[], double v[], int z[], int n,
                       double maxW, int kp) {
    int n_threads = 8;
    pthread_t t[n_threads];
    Args args[n_threads];
    int index_best = 0;
    for (int k = 0; k < n_threads; k++){
        int* z_thr = malloc(sizeof(int)*n);
        args[k].w = w;
        args[k].v = v;
        args[k].z = z_thr;
        args[k].n = n;
        args[k].kp = kp/8;
        args[k].maxW = maxW;
        pthread_create(&t[k], NULL, thread_function, &args[k]);
    }
    double best = INT_MIN;
    for (int k=0; k < n_threads; k++){
        pthread_join(t[k], NULL);
        if (args[k].best > best){
            best = args[k].best;
            index_best = k;
        }
    }
    for (int i=0; i<n; i++){
        z[i] = args[index_best].z[i];
    }
    for (int k=0; k<8; k++){
        free(args[k].z);
    }

    return best;
}
