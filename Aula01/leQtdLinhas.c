#include <stdio.h>

int main(int argc, char** argv){

    FILE* entrada;
    int c, cont = 0;

    if(argc != 2){
        printf("Precisa de dois argumentos.\n");
        return 1;
    }
    entrada = fopen(argv[1], "rb");

    if(!entrada){
        printf("Erro na abertura do arquivo.\n");
        return 1;
    }

    c = fgetc(entrada);
    while (c != EOF)
    {
        if(c == '\n')
            cont+=1;
        c = fgetc(entrada);    
    }
    printf("Qtd de linhas: %d", cont);
    return 0;
}