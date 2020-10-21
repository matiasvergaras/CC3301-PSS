
// Tarea 3: Estructuras recursivas
// Created by Matías Vergara on 18/10/2020.
//

#include "t3.h"

void desbalancear(Nodo **pa, Nodo **pult){

    if ((*pa)->izq == NULL && (*pa)->der == NULL){
        (*pult) = (*pa);
    }

    else if ((*pa)->izq == NULL && (*pa)->der != NULL){
        desbalancear(&((*pa)->der), pult);
    }

    else if((*pa)->izq != NULL && (*pa)->der == NULL){
        desbalancear(&((*pa)->izq), pult);
        Nodo* nuevacabeza = (*pa)->izq;
        //que el nodo al que apunta pult tenga por hijo derecho al nodo padre
        (*pult)->der=(*pa);
        //que el puntero al ultimo nodo apunte al padre
        (*pult) = (*pult)->der;
        //que el hijo izquierdo del padre sea nulo
        (*pa)->izq = NULL;
        //que el puntero pa pase a apuntar al hijo izquierdo, nueva cabeza
        (*pa) = nuevacabeza;
    }

    else if((*pa)->der != NULL && (*pa)->izq != NULL){
        desbalancear(&(*pa)->izq, pult);
        Nodo* nuevacabeza = (*pa)->izq;
        (*pult)->der=(*pa);
        (*pa)->izq=NULL;
        desbalancear(&(*pa)->der, pult);
        (*pa)=nuevacabeza;
    }

}


Nodo* desbalanceado(Nodo *a, Nodo **pult){
    Nodo* nuevoNodo = malloc(sizeof(Nodo));
    nuevoNodo->id = a->id;
    nuevoNodo->hash = a->hash;

    if (a->izq == NULL && a->der == NULL){
        nuevoNodo->izq = NULL;
        nuevoNodo->der = NULL;
        (*pult) = nuevoNodo;
        return nuevoNodo;
    }

    else if (a->izq == NULL && a->der != NULL){
        Nodo* hder = desbalanceado(a->der, pult);
        nuevoNodo->izq = NULL;
        nuevoNodo->der = hder;
        return nuevoNodo;
    }

    else if(a->izq != NULL && a->der == NULL){
        Nodo* hizq = desbalanceado(a->izq, pult);
        (*pult)->der = nuevoNodo;
        (*pult)=(*pult)->der;
        nuevoNodo->izq = NULL;
        nuevoNodo->der = NULL;

        return hizq;
    }

    else if(a->der != NULL && a->izq != NULL){
        Nodo* hizq = desbalanceado(a->izq, pult);
        (*pult)->der=nuevoNodo;
        nuevoNodo->izq=NULL;
        Nodo* hder = desbalanceado(a->der, pult);
        nuevoNodo->der = hder;
        return hizq;
    }
    return nuevoNodo;
}

