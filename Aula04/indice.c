#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int compara(const void *e1, const void *e2) //recebe dois endereços e compara
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

int main(int argc, char**argv)
{
	FILE *f;
	Endereco *e;
    Indice *i;
	long posicao, qtd;
    int cont = 0;

	f = fopen("cep.dat","rb");
	fseek(f,0,SEEK_END);
	posicao = ftell(f);
	qtd = posicao/sizeof(Endereco); //qtd de registros
	e = (Endereco*) malloc(posicao); //alocar area de memoria que caiba o TAM do arq todo
	if(e == NULL) {
		printf("Erro: Nao consegui alocar a memoria\n");
		fclose(f);
		return -1;
	}
	rewind(f); // Vai para o inicio do arquivo, coloca o ponteiro do byte 0 do arquivo e anula o seek_end
	if(fread(e,sizeof(Endereco),qtd,f) == qtd) { 
		printf("Lido = OK\n");
	}
	fclose(f);
	qsort(e,qtd,sizeof(Endereco),compara); //quem? quantos? qual o tam? função de call back
	printf("Ordenado = OK\n");
	f = fopen("cep_ordenado2.dat","wb");
	fwrite(e,sizeof(Endereco),qtd,f);
	fclose(f);
	printf("Escrito = OK\n");
	free(e); //desaloca memoria
}


