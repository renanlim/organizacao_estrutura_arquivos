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

struct _Indice
{
    char cep[8];
    int pos;
};

int main(int argc, char **argv)
{

    FILE *f;
    Endereco e;
    Indice i;
    int inicio, fim, posicao, meio, c = 0;

    f = fopen("indice.dat", "rb");
    // Determinando o início e o fim do arquivo
    inicio = 0;
    fseek(f, 0, SEEK_END);
    fim = ftell(f) / sizeof(Indice) - 1;
    posicao = -1;

    // Realizando a busca binária no arquivo de índice
    while (inicio <= fim)
    {
        c++; // Contando o número de iterações
        meio = (inicio + fim) / 2;  // Determinando a posição do meio do arquivo
        fseek(f, meio * sizeof(Indice), SEEK_SET); // Posicionando o ponteiro do arquivo na posição do meio
        fread(&i, sizeof(Indice), 1, f); // Lendo o registro de índice da posição do meio

        // Verificando se o CEP buscado é igual ao CEP do registro de índice da posição do meio
        if (strncmp(argv[1], i.cep, 8) == 0)
        {
            posicao = i.pos; // Armazenando a posição do registro correspondente no arquivo de endereços
            break;
        }else{
            // Caso o CEP buscado seja menor que o CEP do registro de índice da posição do meio, ajustando o fim da busca
            if (strncmp(argv[1], i.cep, 8) > 0)
            {
                inicio = meio + 1;
            }
            else
            {
                fim = meio - 1;
            }
        }
    }

    if (posicao == -1)
    {
        printf("Nao achei");
    }else{
        f = fopen("cep.dat", "rb");
        fseek(f, posicao * sizeof(Endereco), SEEK_SET);
        fread(&e, sizeof(Endereco), 1, f);
        printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n", e.logradouro, e.bairro, e.cidade, e.uf, e.sigla, e.cep);
        fclose(f);
    }
    printf("Total lido: %d \n", c);
}