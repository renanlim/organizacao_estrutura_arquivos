#include <stdio.h>

int main(){
    FILE *f = fopen("dados.txt", "w");
    int i;
    //[1]static char buffer[4096];
    //[1]sprintf(buffer,"Linha" %i.%f\n", i , i*0.001) : 
    fprintf(f, "Numero Linha, Valor\n");
    for (i = 0; i < 1000; i++)
    {
        fprintf(f, "Linha %i.%f\n", i, i*0.001);
        //[1]sprintf(buffer, "Linha %i.%f\n", i, i*0.001);
        //[1]fputs(buffer,f);
    }
    fclose(f);    
}