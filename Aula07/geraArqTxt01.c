#include <stdio.h>

int main()
{
    FILE *f = fopen("dados.csv","w");
    int i;
    fprintf(f,"Numero Linha, Valor\n");
    for(i=0; i<1000; i++) {
        fprintf(f,"Linha %d\t%f\n",i,i/1000.0);
    }
    fclose(f);
    return 0;
}
