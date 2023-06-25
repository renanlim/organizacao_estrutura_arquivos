#include <stdio.h>
#include <string.h>
/* O programa é composto por um conjunto de instruções em linguagem C, que tem como objetivo ler e comparar dados em dois arquivos binários de CEPs, 
    intercalando-os em um terceiro arquivo binário de saída. */

//Grupo : Ana Clara, Davi Macedo e Renan Lima
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

int main(int argc, char**argv){

    FILE *fa, *fb, *fc;
	Endereco ea, eb;

    fa = fopen("cep_a.dat","rb");
    fb = fopen("cep_b.dat","rb");
    fc = fopen("saida.dat","wb"); //escrita

    //Lê um registro do arquivo fa e outro do fb.
    fread(&ea, sizeof(Endereco), 1, fa);
    fread(&eb, sizeof(Endereco), 1, fb);

    //Loop para intercalar os dados dos arquivos fa e fb em ordem crescente de CEP e escrever no arquivo fc.
    while (!feof(fa) && !feof(fb))
    {
        if(strncmp(ea.cep,eb.cep,8)<0){ //compara os CEPs dos registros.
            fwrite(&ea, sizeof(Endereco), 1, fc); //escreve o registro de fa no arquivo de saída fc.
            fread(&ea, sizeof(Endereco), 1, fa); //lê o próximo registro de fa.
        }else{
            fwrite(&eb, sizeof(Endereco), 1, fc); //escreve o registro de fb no arquivo de saída fc.
            fread(&eb, sizeof(Endereco), 1, fb); //lê o próximo registro de fb.
        }
    }

    //Loop para copiar os registros restantes do arquivo fa no arquivo de saída fc.
    while (!feof(fa))
    {
        fwrite(&ea, sizeof(Endereco), 1, fc); //escreve o registro de fa no arquivo de saída fc.
        fread(&ea, sizeof(Endereco), 1, fa); //lê o próximo registro de fa.
    }
    
    while (!feof(fb))
    {
        fwrite(&eb, sizeof(Endereco), 1, fc);
        fread(&eb, sizeof(Endereco), 1, fb);
    }
    fclose(fa);
    fclose(fb);
    fclose(fc);
    return 0;
}