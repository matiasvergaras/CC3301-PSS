#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>


#include "viajante.h"

int leer(int fd, void *vbuf, int n) {
  char *buf= vbuf;
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
      return 1; /* fracaso: error o fin del archivo/pipe/socket */
    n-= rc; /* descontamos los bytes leídos */
    buf+= rc; /* avanzamos el buffer para no reescribir lo leido previamente */
  } while (n>0); /* mientras no leamos todo lo que esperamos */
  return 0; /* exito */
}

double viajante_par(int z[], int n, double **m, int nperm, int p) {
    int pids[p];
    int infds[p];
    double mindist = DBL_MAX;
    double res;
    int aux[n+1];

    for(int k=0; k<p; k++){
        int fds[2];
        pipe(fds);
        init_rand_seed(random());
        if((pids[k] = fork()) == 0){
            close(fds[0]);
            res = viajante(aux, n, m, nperm/p);
            write(fds[1], &res, sizeof(double));
            write(fds[1], aux, sizeof(int)*(n+1));
            exit(0);
        }
        else{
            close(fds[1]);
            infds[k] = fds[0];
        }
    }
    for(int k=0; k<p; k++){
        leer(infds[k], &res, sizeof(double));
        printf("%f ", res);
        leer(infds[k], aux, sizeof(int)*(n+1));
        waitpid(pids[k], NULL, 0);
        close(infds[k]);
        if(res < mindist){
            mindist = res;
            for(int i=0; i<=n; i++){
                z[i] = aux[i];
            }
        }
    }

  // ... programe aca su solucion ...
  return mindist; /* la distancia recorrida por la mejor ruta */ ;
}

