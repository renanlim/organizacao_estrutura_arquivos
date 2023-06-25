// http://10.101.1.135:1234/sinasc.csv.gz
// Teresina = 221100
// Curitiba = 410690

#include <stdio.h>
#include <string.h>
#include <stdlib.h> //atoi
#define MAX 2048

// index,CODMUNRES,data_nasc,PESO,SEMAGESTAC,adeq_peso_id_gestac,SEXO,IDANOMAL,RACACOR,ESCMAEAGR1,ESTCIVMAE,IDADEMAE,CONSULTAS,PARTO,STTRABPART,KOTELCHUCK,APGAR5,TPROBSON

struct DadosNascimento {
    int index;
    int CODMUNRES;
    char data_nasc[11];
    int PESO;
    int SEMAGESTAC;
    float adeq_peso_id_gestac;
    int SEXO;
    int IDANOMAL;
    int RACACOR;
    int ESCMAEAGR1;
    int ESTCIVMAE;
    int IDADEMAE;
    int CONSULTAS;
    int PARTO;
    int STTRABPART;
    int KOTELCHUCK;
    int APGAR5;
    int TPROBSON;
    int dia;
    int mes;
    int ano;
};

void separaData(char* data, int *dia, int *mes, int *ano)
{
    *ano = atoi(strtok(data,"-"));
    *mes = atoi(strtok(NULL,"-"));
    *dia = atoi(strtok(NULL,"-"));
}

float totalPesoTeresina = 0;
float totalPesoCuritiba = 0;
int contadorTeresina = 0;
int contadorCuritiba = 0;
int ano = 2015;
int Teresina = 221100;
int Curitiba = 410690;
int RioJaneiro=330455;

void processa(struct DadosNascimento* dn) {
    int dia, mes, ano;
    separaData(dn->data_nasc, &dia, &mes, &ano);

    printf("%d %d %d %d\n",dn->CODMUNRES, dia, mes, ano);
}

int main()
{

    int anoAtual,contAno=0,isRio=0;

    char *prox = NULL;
    int lc = 0;
    static char buffer[MAX];
    struct DadosNascimento dn;
    char* linha[18];
    int i;
    FILE *f = fopen("sinasc.csv","r");
    fgets(buffer,MAX,f);
    fgets(buffer,MAX,f);

    printf("Ano e quatidade de pre-maturo extremos nascidos na cidade do Rio de Janeiro:");

    while(!feof(f)) {
        linha[0] = strtok_r(buffer,",\n",&prox);
        for(i=1; i<18; i++) {
            linha[i] = strtok_r(NULL,",\n",&prox);
            if(linha[i]==NULL) {
                linha[i]="";
            }
        }
        dn.index = atoi(linha[0]);
        dn.CODMUNRES = atoi(linha[1]);
        strcpy(dn.data_nasc,linha[2]);
        dn.PESO = atoi(linha[3]);
        dn.SEMAGESTAC = atoi(linha[4]);
        dn.adeq_peso_id_gestac = atof(linha[5]);
        dn.SEXO = atoi(linha[6]);
        dn.IDANOMAL = atoi(linha[7]);
        dn.RACACOR = atoi(linha[8]);
        dn.ESCMAEAGR1 = atoi(linha[9]);
        dn.ESTCIVMAE = atoi(linha[10]);
        dn.IDADEMAE = atoi(linha[11]);
        dn.CONSULTAS = atoi(linha[12]);
        dn.PARTO = atoi(linha[13]);
        dn.STTRABPART = atoi(linha[14]);
        dn.KOTELCHUCK = atoi(linha[15]);
        dn.APGAR5 = atoi(linha[16]);
        dn.TPROBSON = atoi(linha[17]);
        //processa(&dn); //printa na tela o municipio e a data
        // lc++;
        // if(lc==1000) {
        //     break;
        // }

        //MEU CODIGO

        separaData(dn.data_nasc, &(dn.dia), &(dn.mes), &(dn.ano));

        //1) Qual o peso médio dos nascidos em 2015 em Teresina e em Curitiba?
        if(dn.ano==2015){
            if(dn.CODMUNRES==Teresina){
                totalPesoTeresina+=dn.PESO;
                contadorTeresina++;
            }
            if(dn.CODMUNRES==Curitiba){
                totalPesoCuritiba+=dn.PESO;
                contadorCuritiba++;
            }
        }


        //2) Intique por ano a quantidade de pré-maturos extremos nascido na cidade do rio de janeiro.
        //Dica: o arquivo esta ordenado por municipio e depois por data de nascimento
        
        if(dn.CODMUNRES ==RioJaneiro){
            if(isRio==0){
                anoAtual=dn.ano;
                isRio=1;
            }
            if(isRio==1 && dn.ano!=anoAtual){
                printf("\nAno: %d - Quantidade: %d",anoAtual,contAno);
                anoAtual=dn.ano;
                contAno=0;
            }
            if(dn.SEMAGESTAC<=37){
                contAno++;
            }
            
        }

        fgets(buffer,MAX,f);
    }

    totalPesoTeresina/=contadorTeresina;
    totalPesoCuritiba/=contadorCuritiba;
    printf("\n\nPeso medio dos nascidos em 2015:");
    printf("\nTeresina: %f",totalPesoTeresina);
    printf("\nCuritiba: %f\n",totalPesoCuritiba);




    fclose(f);
    return 0;
}