#include <stdio.h>
#define TAM 256


int main(int argc, char** argv)
{
	FILE *ptrArq;
    int v[TAM];
    char c;

    if(argc != 2){
        fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);
		return 1;
    }


    for (int i = 0; i < TAM; i++){
        v[i]=0;
    }
    

    ptrArq = fopen(argv[1], "rb");
    if(!ptrArq){
        printf("Erro na abertura do arquivo.\n");
        return 1;
    }

    c = fgetc(ptrArq);

    while (c != EOF)
    {      
        v[c]++;
        c = fgetc(ptrArq);
    }

    for (int i = 0; i < TAM; i++){
        printf("%c : %d \n", i, v[i]);
    }

    fclose(ptrArq);
    return 0;
}
    
