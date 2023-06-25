#include <stdio.h>

int main()
{
    FILE *f = fopen("dados3.txt","r");
    int a, b;
    float c;
    fscanf(f,"%d%d%f",&a,&b,&c);
    while(!feof(f))
    {
        printf("Lidos: %d %d %f\n",a,b,c);
        fscanf(f,"%d%d%f",&a,&b,&c);
    }
    fclose(f);
    return 0;
}
