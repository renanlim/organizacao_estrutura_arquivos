#include <stdio.h>

int main(int argc, char** argv){

    FILE *entrada, *saida;
    int c;

    entrada = fopen("arqUNIX.txt", "rb");
    saida = fopen("arqDOS.txt", "wb");


    if(!entrada){
        printf("Erro na abertura do arquivo.\n");
        return 1;
    }

    c = fgetc(entrada);
    while (c != EOF)
    {
        if(c == '\n'){
           fputc('\r', saida);
           fputc('\n', saida);   
        }else{
            fputc(c,saida);
        }
        c = fgetc(entrada);
    }
    fclose(entrada);
    fclose(saida);
    return 0;

}