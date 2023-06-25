#include <stdio.h>

int main()
{
    FILE *f = fopen("dados2.txt","w");
    int i;
    static char buffer[4096];
    for(i=0; i<1000; i++) {
        sprintf(buffer,"Linha %i,%f\n",i,i*0.001);
        fputs(buffer,f);
    }
    fclose(f);
    return 0;
}
