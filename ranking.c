#include <stdio.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_RANKING 10

/*Todos os arquivos devem ser passados para a sua versão .h
(Por exemplo, Splash.c irá virar Splash.h para fazer parte do arquivo main.c)*/

typedef struct {
    char nome[MAX_NOME];
    int dificuldade;
    int movimentos;
    int ouro;
} Registro;

void salvar_ranking(char nome[], int dificuldade, int movimentos, int ouro) {
    FILE *arquivo;
    arquivo = fopen("ranking.txt", "a");

    if (arquivo != NULL) {
        fprintf(arquivo, "%s,%d,%d,%d\n", nome, dificuldade, movimentos, ouro);
        fclose(arquivo);
    }
}

void exibir() {
    Registro ranking[MAX_RANKING];
    printf("\n\nOs formados são...\n\n");

    FILE *arquivo;
    arquivo = fopen("ranking.txt", "r");

    if (arquivo != NULL) {
        int i = 0;
        while (fscanf(arquivo, "%[^,],%d,%d,%d\n", ranking[i].nome, &ranking[i].dificuldade, &ranking[i].movimentos, &ranking[i].ouro) != EOF && i < MAX_RANKING) {
            i++;
        }
        fclose(arquivo);

        // Ordenar os dados pelo ouro em ordem decrescente
        for (int j = 0; j < i - 1; j++) {
            for (int k = j + 1; k < i; k++) {
                if (ranking[j].ouro < ranking[k].ouro) {
                    Registro temp = ranking[j];
                    ranking[j] = ranking[k];
                    ranking[k] = temp;
                }
            }
        }

        // Imprimir o cabeçalho
        printf("%-20s %-10s %-15s %-15s\n", "Nome", "Dificuldade", "Movimentos", "Ouro");
        printf("\n");

        // Imprimir os dados
        for (int j = 0; j < i && j < MAX_RANKING; j++) {
            // Converte o valor da dificuldade para o nome
            const char *dificuldades[] = {"Fácil", "Médio", "Difícil"};
            const char *dificuldade_str = dificuldades[ranking[j].dificuldade];
            printf("%-20s %-10s %-15d %-15d\n", ranking[j].nome, dificuldade_str, ranking[j].movimentos, ranking[j].ouro);
        }
    } else {
        printf("Seja o primeiro a se formar!\n");
    }
}

int main() {
    // Exemplo de chamadas
    salvar_ranking("Joaquim", 1, 50, 100);
    salvar_ranking("Maria", 0, 40, 90);
    exibir();

    return 0;
}
