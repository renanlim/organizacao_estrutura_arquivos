#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    static char buffer[4096];
    strcpy(buffer,"ABC,DEF\tGHI;123\n");
    char *tok = strtok(buffer,"\t;,\n");
    while(tok) {
        puts(tok);
        tok = strtok(NULL,"\t;,\n");
    }

    return 0;
}