#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Ocorrencia Ocorrencia;

struct _Ocorrencia {
    char palavra[11];
    int quantidade;
};
int comparaPalavras(const void* a, const void* b){
    return strcmp(((Ocorrencia*)a)->palavra, ((Ocorrencia*)b)->palavra);
}

int main(int argc, char** argv){
    Ocorrencia o;
    char palavra[11];
    FILE *f = fopen(argv[1], "r");
    FILE *saida = fopen("ocorrencias.dat", "wb");

    int qt = 0;
    //o fscanf dentro do while para contar 12 lala e nao 11, porque o fscanf 
    while (fscanf(f, "%s", o.palavra))
    {
        //strcpy(o.palavra, palavra); se usar o o.palavra no fscanf voce le direto na estrutura e tira o strcpy
        o.quantidade = 1;
        fwrite(&o, sizeof(Ocorrencia), 1, saida);
        printf("%s\n", palavra);
        fscanf(f, "%s", o.palavra); 
        qt++;  
    }
    

    fclose(f);
    fclose(saida);

    //Remover repetidos -- ORDENA
    Ocorrencia *ocorrencias = (Ocorrencia*)malloc(qt*sizeof(Ocorrencia));
    f = fopen("ocorrencias.dat", "rb");
    saida = fopen("ocorrencias.dat", "wb");
    fread(ocorrencias, sizeof(Ocorrencia), qt, f);

    //qsort(ocorrencias, qt, size, comparaPalavra);
    qsort(ocorrencias, qt, sizeof(Ocorrencia), comparaPalavras);

    int j;
    int k;
    //char* ultima = NULL;
    for(j=0; j < qt; j++){
        if(j == 0){
            k = j;
            //ultima = ocorrencias[j].palavra;
        }else 
            if(strcmp(ocorrencias[j].palavra, ocorrencias[k].palavra)==0){
                ocorrencias[k].quantidade++;
            }else {
                fwrite(&ocorrencias[k], sizeof(Ocorrencia), 1,saida);
                k = j;
            }
    }
    fwrite(&ocorrencias[k], sizeof(Ocorrencia), 1,saida);

    fclose(f);
    free(ocorrencias);
    return 0;
}