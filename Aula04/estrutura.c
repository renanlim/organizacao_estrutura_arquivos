#include <stdio.h>
#include <stdlib.h>

int main( int argc, char**argv){
    int v[] = {10, 20, 30, 40, 50, 60, 70};
    int procurado = atoi(argv[1]);
    int meio;
    int inicio = 0;
    int fim = 6;

    meio = (inicio+fim)/2;
    
    if(procurado > v[meio]){
        inicio = meio + 1;
        printf("Numero %d e maior que o meio\n", procurado);
    }
    else if(procurado < v[meio]){
        fim = meio - 1;
        printf("Numero %d e menor que o meio\n", procurado);
    }
    else{
        printf("Numero %d e o meio\n", procurado);
    }
        
}