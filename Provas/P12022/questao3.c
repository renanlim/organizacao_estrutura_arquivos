#include <stdio.h>
#include <string.h>

typedef struct _Registro Registro;

struct _Registro
{
	char cpf[15];
	char curso[20];
	char dataNascimento[11];
	char sexo;
	char email[40];
	char opcaoQuadro;
};

int main(int argc, char**argv){

    FILE *entrada1, *entrada2, *saida;
	Registro reg2021, reg2022;

    entrada1 = fopen("candidatos2021.dat","rb");
    entrada2 = fopen("candidatos2022.dat","rb");
    saida = fopen("saida.dat","wb"); //escrita

    //Lê um registro do arquivo fa e outro do fb.
    fread(&entrada1, sizeof(Registro), 1, entrada1);
    fread(&entrada2, sizeof(Registro), 1, entrada2);

    //Loop para intercalar os dados dos arquivos fa e fb em ordem crescente de CEP e escrever no arquivo fc.
    while (!feof(entrada1) && !feof(entrada2))
    {
        if(strncmp(reg2021.cpf,reg2022.cpf,15)==0){ //compara os CEPs dos registros.
            fwrite(&reg2021, sizeof(Registro), 1, saida); //escreve o registro de fa no arquivo de saída fc.
            fread(&reg2021, sizeof(Registro), 1, entrada1); //lê o próximo registro de fa.
            fread(&reg2022, sizeof(Registro), 1, entrada2);
        }else if(strncmp(reg2021.cpf,reg2022.cpf,15)<0){
            fwrite(&reg2022, sizeof(Registro), 1, saida); //escreve o registro de fb no arquivo de saída fc.
            fread(&reg2022, sizeof(Registro), 1, entrada2); //lê o próximo registro de fb.
        }
    }

    fclose(entrada1);
    fclose(entrada2);
    fclose(saida);
    return 0;
}