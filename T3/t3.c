// Tarea 3: Estructuras recursivas
// Created by Matías Vergara on 18/10/2020.
//

#include "t3.h"

void desbalancear(Nodo **pa, Nodo **pult){
    Nodo* a = *pa;
    /*
     * -> Si este nodo tiene hijo izquierdo y derecho nulo -> esta desbalanceado al maximo
     *
     * -> Si este nodo tiene hijo izquierdo nulo y derecho no nulo -> itero hacia la derecha. Una vez
     * que se vuelva a este scope, el arbol de la derecha estará balanceado, y como no hay hijo izquierdo,
     * el nodo entero lo estará.
     *
     * -> Si este nodo tiene hijo izquierdo no nulo y derecho nulo -> itero hacia la izquierda. Una vez
     * que se vuelva a este scope, el de la izquierda estará balanceado, pero debo poner padre al final
     * del ultimo nodo de izquierda. Para eso debo tener guardado en *pult el mas menor de todos,
     * hacer que *pa sea el hijo de la izquierda del padre,
     * asignarle a pult padre como hijo de la derecha, hacer que padre tenga hijo izq nulo.
     *
     * -> Si este nodo tiene hijo izquierdo y derecho no nulos -> balanceo el de la derecha,
     * asignando pult, y luego el de la izquierda
     * (pues el de la derecha no cambia el padre, el de la izquierda si).
     */
    if (a->izq == NULL && a->der == NULL){
        pult = &a;
        return 0;
    }
    else if (a->izq == NULL && a->der != NULL){
        desbalancear(&a->der, pult)
    }
    else if(a->izq != NULL && a->der == NULL){
        desbalancear(&a->izq, pult)
        Nodo* pcopy = a;
        pa = &(a->izq);
        Nodo* ult = *pult;
        ult->der = pcopy;
        pcopy->izq = NULL;
    }
    else if(a->der != NULL && a->izq != NULL){
        desbalancear(&a->der, pult);
        Nodo* paux = *pult;
        desbalancear(&a->izq, pult);
        pult = &paux;
    }
}

void desbalanceado(Nodo *a, Nodo **pult);
