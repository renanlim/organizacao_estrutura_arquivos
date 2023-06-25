#include <stdio.h>
#include <string.h>

#define MAX_REGISTROS 10000
#define MAX_CURSOS 100

struct Registro {
    char cpf[15];
    char curso[20];
    char dataNacimento[11];
    char sexo;
    char email[40];
    char opcaoQuadro;
};

int main() {
    FILE *arquivo;
    struct Registro candidato;
    int i, j, num_registros = 0, num_cursos = 0;
    int contagem_cursos[MAX_CURSOS] = {0}; // vetor que armazena a contagem de inscritos para cada curso
    char cursos[MAX_CURSOS][20]; // matriz que armazena os nomes de cada curso
    int curso_existe; // variável auxiliar para verificar se um curso já foi cadastrado

    // Abrir arquivo de registros
    arquivo = fopen("candidatos.dat", "rb");
    if (!arquivo) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    // Ler registros do arquivo e contar o número de inscritos para cada curso
    while (fread(&candidato, sizeof(struct Registro), 1, arquivo)) {
        // Verificar se o curso do candidato já foi cadastrado
        curso_existe = 0;
        for (i = 0; i < num_cursos; i++) {
            if (strcmp(cursos[i], candidato.curso) == 0) {
                contagem_cursos[i]++;
                curso_existe = 1;
                break;
            }
        }

        // Caso contrário, cadastrar o curso e inicializar a contagem
        if (!curso_existe) {
            strcpy(cursos[num_cursos], candidato.curso);
            contagem_cursos[num_cursos]++;
            num_cursos++;
        }

        num_registros++;
    }

    // Imprimir resultado
    printf("Total de candidatos inscritos: %d\n", num_registros);
    printf("Contagem de inscritos por curso:\n");
    for (i = 0; i < num_cursos; i++) {
        printf("%s: %d\n", cursos[i], contagem_cursos[i]);
    }

    fclose(arquivo);
    return 0;
}
