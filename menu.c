#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*Todos os arquivos devem ser passados para a sua versão .h
(Por exemplo, Splash.c irá virar Splash.h para fazer parte do arquivo main.c)*/

// Estrutura para configurações
struct Config {
    int rateDificuldade;
    int rateMoeda;
    int rateMorcego;
};

// Funções utilizadas
void exibir_menu(char matriz[][80]);
void escolher_menu();
void exibir_configuracoes(char matriz[][80]);
void escolher_configuracao();
void iniciar_jogo();

// Variáveis globais
char splash[5][80] = {
    "    ##     ##  #    #####       #####   #     #  #     #   #####  ######  #####   #     #",
    "    ##     ##  #   #            #     # #     #  ##    #  #       #      #     #  ##    #",
    "    ##     ##     ######        #     # #     #  # #   #  #  #### #####  #     #  # #   #",
    "#   ## #   ##          #        #     # #     #  #  #  #  #     # #      #     #  #  #  #",
    " ####   ####     ######         #####    #####   #    ##   #####  ######  #####   #    ##"
};

struct Config configuracao;

int main() {
    exibir_menu(splash);
    escolher_menu();
    return 0;
}

void exibir_menu(char matriz[][80]) {
    system("clear");
    for (int i = 0; i < 5; i++) {
        printf("%s\n", matriz[i]);
    }
    printf("\n1. Jogar\n");
    printf("2. Configurações\n");
    printf("3. Sair\n");
}

void escolher_menu() {
    int opcao;
    while (1) {
        printf("Digite a sua opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                iniciar_jogo();
                break;
            case 2:
                exibir_configuracoes(splash);
                escolher_configuracao();
                break;
            case 3:
                printf("Até mais!\n");
                exit(0);
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
}

void exibir_configuracoes(char matriz[][80]) {
    system("clear");
    for (int i = 0; i < 5; i++) {
        printf("%s\n", matriz[i]);
    }
    printf("\nDificuldade atual: %s\n", configuracao.rateDificuldade == 0 ? "Fácil" : (configuracao.rateDificuldade == 1 ? "Médio" : "Difícil"));
    printf("\n1. Nivel facil: mais moedas, vida,  // menos bats (eles dão vida), mapas, preciosidade (valor do gold) stamina\n");
    printf("2. Nivel normal: jogo regular\n");
    printf("3. Nivel dificil: menos moedas, vida,  // mais bats, mapas, stamina, preciosidade e névoa!\n");
    printf("4. Voltar\n");
}

void escolher_configuracao() {
    int opcao;
    while (1) {
        printf("Digite a sua opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                configuracao.rateDificuldade = 0;
                configuracao.rateMoeda = 5;
                configuracao.rateMorcego = 20;
                printf("Fácil selecionado\n");
                sleep(3);
                exibir_menu(splash);
                escolher_menu();
                break;
            case 2:
                configuracao.rateDificuldade = 1;
                configuracao.rateMoeda = 10;
                configuracao.rateMorcego = 15;
                printf("Médio selecionado\n");
                sleep(3);
                exibir_menu(splash);
                escolher_menu();
                break;
            case 3:
                configuracao.rateDificuldade = 2;
                configuracao.rateMoeda = 15;
                configuracao.rateMorcego = 10;
                printf("Difícil selecionado\n");
                sleep(3);
                exibir_menu(splash);
                escolher_menu();
                break;
            case 4:
                exibir_menu(splash);
                escolher_menu();
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
}

void iniciar_jogo() {
    // Implementar o código para iniciar o jogo
}
