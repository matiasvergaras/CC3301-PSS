//CC3301 - Programación de Software de Sistemas
//Tarea 8 - Metodología B - Matías Vergara Silva.

/**
 * Esta implementación podría fallar entregando una distancia mínima que no corresponda
 * a la distancia de lo que esté escrito en el arreglo z. Esto se debe a que, al implementarlo
 * de esta forma - mediante jumps y no como una condición para iterar -, el proceso se interrumpirá
 * en el momento exacto que se reciba la señal, independientemente si es al inicio, al fin o en medio de una
 * iteración del ciclo. En particular, podría llegar tras asignar la nueva distancia mínima, pero antes de
 * cambiar el arreglo, o peor aún, cuando solo se haya cambiado parte de él. La otra metodología no presenta
 * este defecto, pues la consecuencia de recibir la señal (cambio en la variable global) solo tendrá efecto al
 * volver a evaluar la condición del for, mientras que acá apenas se reciba la señal se lanzará longjmp, lo cual
 * detendrá todo para encontrar su setjmp correspondiente y continuar desde ahí.
 */
#define _XOPEN_SOURCE 500


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <setjmp.h>
#include "viajante.h"

jmp_buf excp;

void ring(){
    longjmp(excp, 1);
}


double viajante(int z[], int n, double **m, int nperm) {
  double min= DBL_MAX; // la distancia mas corta hasta el momento
  void (*hdlr) () = signal(SIGINT, ring);
  if (setjmp(excp)==0){
      for (int i= 1; i<=nperm; i++) {
          int x[n+1];          // almacenara una ruta aleatoria
          gen_ruta_alea(x, n); // genera ruta x[0]=0, x[1], x[2], ..., x[n], x[0]=0
          // calcula la distancia al recorrer 0, x[1], ..., x[n], 0
          double d= dist(x, n, m);
          if (d<min) {    // si distancia es menor a la mas corta hasta el momento
              min= d;       // d es la nueva distancia mas corta
              for (int j= 0; j<=n; j++)
                  z[j]= x[j]; // guarda ruta mas corta en parametro z
          }
      }
  }
  else{}
  signal(SIGINT, hdlr);
  return min;
}
