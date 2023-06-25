#include <stdio.h>
#include <string.h>
#include <math.h>

//Diretiva de pré-processamento para garantir que a estrutura de dados cabecalho seja armazenada na memória sem espaços vazios.
#pragma pack(1)

typedef struct _cabecalho cabecalho;

struct _cabecalho{
    char tipo[2];
    unsigned int tamanhoArquivo;
    unsigned short reservado1;
    unsigned short reservado2;
    unsigned int inicioBitmap;
    unsigned int tamanhoCab2;
    int largura;
    int altura;
    unsigned short planos; //1
    unsigned bitsPorPixel; //24 (3 bytes)
    unsigned int metdoCompresao; //0
    unsigned int tamanhoBitmapBytes; // w * h * 3
    unsigned int resolucaoHorizontal; //0
    unsigned int resolucaoVertical; //0
    unsigned int numeroCores; //0
    unsigned int coresImportantes; //0
};

int main(){

    //Declara a estrutura cabecalho e preenche seus campos com valores apropriados para criar uma imagem BMP com 400x400 pixels. 
    //O tamanho do arquivo é calculado multiplicando o número de pixels pelo tamanho de cada pixel, que é de 3 bytes para a imagem colorida (24 bits por pixel).
    cabecalho c;
    strncpy(c.tipo, "BM", 2);
    c.tamanhoArquivo = sizeof(cabecalho) + 400 * 400 * 3; // 24/8 = 3 pixel
    c.reservado1 = 0;
    c.reservado2 = 0;
    c.inicioBitmap = 54;
    c.tamanhoCab2 = 40;
    c.largura = 400;
    c.altura = 400;
    c.planos = 1;
    c.bitsPorPixel = 24;
    c.metdoCompresao = 0;
    c.tamanhoBitmapBytes = 400 * 400 * 3;
    c.resolucaoHorizontal = 0;
    c.resolucaoVertical = 0;
    c.numeroCores = 0;
    c.coresImportantes = 0;

    //Abre um arquivo chamado "minhaimagem.bmp" em modo de escrita binária ("wb") e grava o cabeçalho nele utilizando a função fwrite().
    FILE *f = fopen("minhaimagem.bmp", "wb");
    fwrite(&c, sizeof(cabecalho), 1, f); //Grava o cabeçalho do arquivo BMP (c) no arquivo f.
    for (int i = 0; i < 400; i++)
    {
        for (int j = 0; j < 400; j++)
        {
            int vermelho;
            int verde;
            int azul;
            float distancia = sqrt((i-200)*(i-200)+(j-200)*(j-200)); //Calcula a distância do pixel atual (i, j) ao centro da imagem (200, 200).
            if(distancia < 50){ // Se a distância for menor que 50, o pixel atual é considerado dentro de um círculo no centro da imagem.
            vermelho = 255; //Define a cor do pixel atual como vermelho.
            verde = 0;
            azul = 0;
            }else{ //Caso contrário, o pixel atual é considerado fora do círculo como branco
                vermelho = 255;
                verde = 255;
                azul = 255;    
            }

            fputc(vermelho,f); //Escreve o valor da componente vermelho do pixel atual no arquivo f.
            fputc(azul, f);
            fputc(verde, f);
        }   
    }
    fclose(f);

    return 0;
}