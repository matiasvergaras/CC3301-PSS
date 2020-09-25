#include <stdio.h>
#include <stdlib.h>

#include "t1.h"

unsigned long long dupMasLargo(unsigned long long x){
    int tam= 0;
    unsigned sec= 0;
    for (int i= 1; i<=32; i++){
        unsigned long long maskModi=(~1);
        unsigned long long maskMod2i =(~1);
        maskModi=maskModi>>(64-i);
        maskMod2i=maskMod2i>>(64-i-i);
        unsigned long long x_2i_bits=x&(maskMod2i);
        if (i==32){
            x_2i_bits= x;
        }
        unsigned long long x_i_bits_sup= (x_2i_bits >> i);
        unsigned long long x_i_bits_inf= (x_2i_bits & maskModi);
        if (x_i_bits_sup == x_i_bits_inf){
            tam= i;
            sec= x_i_bits_inf;
        }
    }
    return ((unsigned long long)tam<<32) | sec;
}