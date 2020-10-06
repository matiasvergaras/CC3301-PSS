#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reducir(char *s){
    char *obj = s; //objetivo: donde modificamos el string s
    char *prev = s; //previo: donde llevamos lo ultimo que pasamos a s
    char *sig = s; //siguiente: donde vamos

    if(*obj!='0'){ //Para evitar un seg fault
        sig++;
    }

    while(*obj){
        if(*sig!=' '){ //Esto incluye el 0 final, que cierra el string obj.
            *++obj=*sig;
        }
        else if(*sig==' ' && *prev!=' '){
            *++obj=*sig;
        }
        sig++;
        prev++;
    }
}

char* reduccion(char* s){
    //Primero contamos los char que queremos mantener para pedir memoria
    char *c = s;
    char *d = s;
    int chars=0;

    if(*c!='0'){ //Para evitar un seg fault
        d++;
    }

    while(*d){
        if(*d!=' ' || (*d==' ' && *c!=' ')){
            chars++;
        }
        d++;
        c++;
    }

    //asignamos la memoria necesaria. Sumamos 2 por el primer caracter y el 0 final.
    char* salida = (char*)malloc(sizeof(char)*(chars+2));
    char* iter = salida;
    if(*s!=0){
        *iter=*s;
        s++;
    }

    while(*s){
        if(*s != ' '){
            iter++;
            *iter=*s;

        }
        else if(*s == ' ' && *iter!=' '){
            iter++;
            *iter=*s;
        }
        s++;
    }

    *++iter=*s;
    return salida;
}
