#include <stdio.h>
#include <string.h>

int main()
{
    FILE *f = fopen("dados2.txt","r");
    static char buffer[4096];
    fgets(buffer,4096,f);
    while(!feof(f)) {
        buffer[strlen(buffer)-1] = '*';
        puts(buffer);
//        printf("%s",buffer);
        fgets(buffer,4096,f);
    }
    fclose(f);
    return 0;
}
