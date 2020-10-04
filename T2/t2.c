#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reducir(char *s){
    int esp = 0; //Funciona como un bool. Nos indica si paso un espacio.
    char*act = s; //Caracter 'actual'
    char*sig = s; //Caracter 'siguiente'
    while (*sig != '\0'){
        if(*sig==' '){
            if(esp==1){
                *act=*sig;
                sig++;
            }
            else{
                *act=*sig;
                sig++;
                act++;
                esp++;
            }
        }
        else if(*sig!=' '){
            if(esp == 1){
                *act=*sig;
                act++;
                sig++;
                esp--;
            }
            else{
                *act=*sig;
                sig++;
                act++;
            }

        }
    }
    *act=*sig; //Agregamos el final de string
}

char* reduccion(char* s){
    char *c = s;
    //Primero contamos los char que queremos mantener para pedir memoria
    int chars=0;
    int esp=0;
    for(int i=0; i<strlen(s); i++){
        if(esp==0){
            if (*c==' ') {
                esp++;
                chars++;
            }
            else{
                chars++;
            }
        }
        else if(esp==1){
            if(*c!=' '){
                esp--;
                chars++;
            }
            else{
            }
        }
        c++;
    }

    char* salida = (char*)malloc( sizeof(char)*(chars+1));
    char* iter = salida;
    esp=0;
    int largooriginal=strlen(s);
    for(int j=0; j<=largooriginal; j++){
        if(esp==0){
            if(*s!=' '){
                *iter++=*s;
                s++;
            }
            else{
                *iter++=*s;
                esp++;
                s++;
            }
        }
        else if(esp==1){
            if(*s!=' '){
                *iter++=*s;
                esp--;
                s++;
            }
            else{
                s++;
            }
        }
    }
    return salida;
}


