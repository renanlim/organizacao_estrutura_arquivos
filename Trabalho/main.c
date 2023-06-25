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

//É usada para comparar dois registros de "Indice" pelo campo "cep", que é um array de caracteres.
int compara(const void *i1, const void *i2) 
{
	return strncmp(((Indice*)i1)->cep,((Indice*)i2)->cep,8);
}

int main(int argc, char**argv)
{
	FILE *f, *g;
	Endereco *e;
    Indice *i;
	long posicao, qtd;

	//um ponteiro para o arquivo "cep.dat" é criado e, se não for possível abrir o arquivo, uma mensagem de erro é exibida e o programa é encerrado com o valor de retorno -1.
	f = fopen("cep.dat","rb");  
	if(f == NULL) {
		printf("Erro: nao foi possivel abrir o arquivo cep.dat\n");
		return -1;
	}
	//O ponteiro do arquivo é movido para o final do arquivo com a função "fseek", e a posição atual é armazenada em "posicao"
	fseek(f,0,SEEK_END);
	posicao = ftell(f);

	//A quantidade de registros é calculada dividindo "posicao" pelo tamanho de "Endereco". 
	qtd = posicao/sizeof(Endereco);

	//uma área de memória é alocada para armazenar os registros de "Endereco", do tamanho do arquivo "cep.dat".
	e = (Endereco*) malloc(posicao); 

	//Se a alocação de memória falhar, uma mensagem de erro é exibida e o programa é encerrado com o valor de retorno -1.
	if(e == NULL) {
		printf("Erro: Nao consegui alocar a memoria\n");
		fclose(f);
		return -1;
	}

	//O ponteiro do arquivo é reiniciado para o início do arquivo com a função "rewind". 
	rewind(f);

	//A função "fread" é usada para ler os registros do arquivo "cep.dat" e armazená-los em "e".
	//Se houver um problema na leitura do arquivo, uma mensagem de erro é exibida e o programa é encerrado com o valor de retorno -1. O arquivo "cep.dat" é fechado.
	if(fread(e,sizeof(Endereco),qtd,f) != qtd) { 
		printf("Erro: problema ao ler o arquivo cep.dat\n");
		fclose(f);
		return -1;
	}
	fclose(f);

	//a função "qsort" é usada para ordenar os registros em "e" com base no campo "cep", usando a função "compara" para comparar os registros.
	qsort(e, qtd, sizeof(Endereco), compara);
	
	//O arquivo "indice.dat" é aberto em modo de escrita binária, e se não for possível criar o arquivo, uma mensagem de erro é exibida e o programa é encerrado com o valor de retorno -1. 
	g = fopen("indice.dat", "wb");
	if (g == NULL) {
		printf("Erro: Nao consegui criar o arquivo indice.dat\n");
		return -1;
	}

	//Uma área de memória é alocada para armazenar os registros de "Indice", com o tamanho da quantidade de registros de "Endereco".
	//Se a alocação de memória falhar, uma mensagem de erro é exibida e o arquivo "indice.dat" é fechado.
	i = (Indice*) malloc(qtd * sizeof(Indice));
	if (i == NULL) {
		printf("Erro: Nao consegui alocar a memoria\n");
		fclose(g);
		return -1;
	}

	memset(i, 0, qtd * sizeof(Indice));
	
	//O loop "for" é usado para copiar os primeiros 8 caracteres do campo "cep" de cada registro de "Endereco" para o campo "cep" de cada
	//registro de "Indice", e armazenar a posição do registro correspondente de "Endereco" no campo "pos" de cada registro de "Indice".
	for (int j = 0; j < qtd; j++) {
		memcpy(i[j].cep, e[j].cep, 8);
		i[j].pos = j * sizeof(Endereco);
	}

	//Os registros em "i" são, então, ordenados com a função "qsort", usando a função "compara" para comparar os registros.
	qsort(i, qtd, sizeof(Indice), compara);
	printf("Indice ordenado pelo CEP criado com sucesso!\n");

	//A função fwrite é utilizada para escrever os dados da memória para um arquivo binário. 
	//O if verifica se todos os elementos do índice foram escritos corretamente no arquivo. 
	if (fwrite(i, sizeof(Indice), qtd, g) != qtd) {
		printf("Erro ao escrever o arquivo indice.dat\n");
		fclose(g);
		return -1;
	}

	fclose(g);
	free(e);
	free(i);

	return 0;
}
