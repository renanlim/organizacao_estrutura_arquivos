#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	char lixo[2];
};

struct _Indice{
    char cep[8];
    int pos;
};

int compara(const void *e1, const void *e2) 
{
	return strncmp(((Indice*)e1)->cep,((Indice*)e2)->cep,8);
}

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	Indice* ind;
	int qt,qtd, i;

	f = fopen("cep.dat","rb");
    fseek(f,0,SEEK_END);
	qtd = ftell(f)/sizeof(Endereco);
    ind = (Indice*) malloc(sizeof(Indice)*qtd);
	qt = fread(&e,sizeof(Endereco),1,f);
    //rewind(f);

    qt = fread(&e, sizeof(Endereco),1,f); //&e como o & comercial porque é um endereço
    i = 0;
	while(qt > 0)
	{
        // i[i].pos = i;
        // strncpy(ind[i].cep, e.cep, 8); //ind[i].cep = e.cep;
		// //só pode usar o strncpy se a string for null terminated, ou seja, possui um null no final
		// qt = fread(&e, sizeof(Endereco),1,f);
        // i++;
		strncpy(ind[i].cep,e.cep,8);
        ind[i].pos = i;
		qt = fread(&e,sizeof(Endereco),1,f);		
        i++;
    }
	fclose(f);
    qsort(ind,qtd,sizeof(Indice),compara);

    f = fopen("indice.dat", "wb");
    fwrite(ind,sizeof(Indice), qtd, f); //ind sem o & comercial porque é um ponteiro para um array
    fclose(f);
    free(ind);
	return 0;
}

