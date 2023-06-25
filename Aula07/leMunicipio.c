#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char* tok;
    int col = 0;
    FILE *f = fopen("dadosMunicipio.csv","r");
    static char buffer[4096];
    fgets(buffer,4096,f);
    while(!feof(f))
    {
        col = 0;
        tok = strtok(buffer,",\n");
        while(tok) {
            if(col == 11) {
                puts(tok);
            }
            tok = strtok(NULL,",\n");
            col++;
        }
        fgets(buffer,4096,f);
    }
    fclose(f);
    return 0;
}