#include <stdio.h>

int main(int argc, char** argv){

    FILE *f;
    int v[256] = {0};
    char c;

    if(argc != 2){
        fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);
		return 1;
    }

    f = fopen(argv[1], "rb");
    if(!f){
        printf("Erro na abertura do arquivo.\n");
        return 1;
    }

    c = fgetc(f);

    while (c != EOF)
    {      
        v[c]++;
        c = fgetc(f);
    }

    for (int i = 0; i < 256; i++){
        printf("%c : %d \n", i, v[i]);
    }

    fclose(f);
    return 0;


}