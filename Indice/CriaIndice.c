#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma pack(1)

typedef struct _Endereco Endereco;
typedef struct _Indice Indice;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

struct _Indice {
	char cep[8];
    unsigned int posicao;
};

int compara(const void *e1, const void *e2) {
	return strncmp(((Indice*)e1)->cep,((Indice*)e2)->cep,8);
}

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
    Indice* ind;
	int qtRegistros, qt, i;

	f = fopen("cep.dat","rb");
    fseek(f,0,SEEK_END);
    qtRegistros = ftell(f)/sizeof(Endereco);
    rewind(f);
    ind = (Indice*) malloc(sizeof(Indice)*qtRegistros);
	qt = fread(&e,sizeof(Endereco),1,f);
    i = 0;
	while(qt > 0) {
        strncpy(ind[i].cep,e.cep,8);
        ind[i].posicao = i;
		qt = fread(&e,sizeof(Endereco),1,f);		
        i++;
	}
	fclose(f);
    qsort(ind,qtRegistros,sizeof(Indice),compara);
    f = fopen("indice.dat","wb");
    fwrite(ind,sizeof(Indice),qtRegistros,f);
    fclose(f);
    free(ind);
    return 0;
}

