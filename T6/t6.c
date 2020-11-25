#include <pthread.h>
#include <stdio.h>

#include "t6.h"


pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int visor = 1;
int num_entrega = 0;

void ocupar() {
    pthread_mutex_lock(&m);
    num_entrega++;
    int turno_act = num_entrega;
    //printf("entrante toma numero: %d - visor muestra: %d\n", turno_act, visor);
    while(turno_act !=  visor){
        pthread_cond_wait(&cond, &m);
    }
    pthread_mutex_unlock(&m);
    //printf("Atendiendo numero: %d - visor muestra: %d\n", turno_act, visor);
}

void desocupar() {
    pthread_mutex_lock(&m);
    visor++;
    pthread_mutex_unlock(&m);
    //printf("Consulta libre. Visor muestra: %d\n", visor);
    pthread_cond_broadcast(&cond);

}
