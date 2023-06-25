#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

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

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int qt, inicio, fim, meio, achei, compara;
	int c;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

	c = 0;
	f = fopen("cep_ordenado.dat","r");
	fseek(f, 0, SEEK_END);
	fim = (ftell(f)/sizeof(Endereco))-1;
    achei=0;

	while(inicio <= fim && !achei)
	{
		meio=(inicio+fim)/2;

        fseek(f, meio*sizeof(Endereco), SEEK_SET);
        qt = fread(&e, sizeof(Endereco), 1, f);
		// argv[1] < e.cep  => strcmp(argv[1],e.cep) < 0
		// argv[1] > e.cep  => strcmp(argv[1],e.cep) > 0
		// argv[1] == e.cep  => strcmp(argv[1],e.cep) == 0
        compara = strncmp(argv[1],e.cep,8);
		if(compara==0){
			achei = 1;
        }else if(compara < 0){
            fim = meio - 1;
        }else{
            inicio = meio + 1;
        }
        c++;	
	}

    if(achei){
        printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
    }else
        printf("Nao achei\n");

	printf("Total Lido: %d\n", c);
	fclose(f);
}

