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
    int borrar=0;
    int esp=0;
    for(int i=0; i<strlen(s); i++){
        switch(esp){
            case 0:
                if(*c==' '){
                    esp++;
                }
            case 1:
                if(*c!=' '){
                    esp--;
                }
                else if(*c==' '){
                    borrar++;
                }

        }
        c++;
    }

    char* salida = (char*)malloc( sizeof(char)*(strlen(s)-borrar+1));
    char* iter = salida;
    esp=0;
    int largooriginal=strlen(s);
    for(int j=0; j<=largooriginal; j++){
        switch(esp){
            case 0:
                if(*s!=' '){
                    *iter++=*s;
                }
                else if(*s==' '){
                    *iter++=*s;
                    esp++;
                }
                break;

            case 1:
                if(*s!=' '){
                    *iter++=*s;
                    esp--;
                }
                break;
        }
        s++;
    }
    return salida;
}



