#include <stdio.h>

int main(void){
    int account;
    char name[30];
    double balance;

    FILE *cfPtr;

    cfPtr = fopen("clients.dat", "w");
    if (cfPtr == NULL){
        printf("Arquivo nao pode ser aberto\n");
    }
    else{
        printf("Digite numero da conta, nome, saldo: \n");
        printf("Digite fim do arquivo para terminar a entrada: \n");
        printf("? ");
        scanf("%d%s%lf", &account, name, &balance);
    while (!feof(stdin))
    {
        fprintf(cfPtr, "%d %s %.2f \n", account, name, balance);
        printf("? ");
        scanf("%d%s%lf", &account, name, &balance);
        
    }
    fclose(cfPtr);
    }
    return 0;
}