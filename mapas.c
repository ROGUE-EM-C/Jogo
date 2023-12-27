#include <stdio.h>

// Definições de cores ANSI
#define RED "\x1b[31m"
#define DIM "\x1b[2m"
#define RESET "\x1b[0m"

/*Todos os arquivos devem ser passados para a sua versão .h
(Por exemplo, Splash.c irá virar Splash.h para fazer parte do arquivo main.c)*/

void printMap(char *mapa) {
    // Inicia o colorama (simulado com sequências de escape ANSI)
    printf("\x1b[0m");

    for (int i = 0; mapa[i] != '\0'; i++) {
        if (mapa[i] == '#') {
            printf(RED DIM "#");
        } else {
            printf("%c", mapa[i]);
        }

        if (mapa[i] == '\n') {
            // Troca de linha, redefine a formatação para a próxima linha
            printf(RESET);
        }
    }
}

int mapa1() {
    // Exemplo de chamada da função com um dos mapas
    printMap("#########################\n"
             "#.........#.............#\n"
             "#.#######.#.#######.###.#\n"
             "#.#.......#.......#.#...#\n"
             "#.#######.#.#######.#.#.#\n"
             "#.#.......#.......#...#.#\n"
             "#.#######.#.###########.#\n"
             "#...........#...........#\n"
             "#########################\n");

    return 0;

int mapa2() {
    // Exemplo de chamada da função com um dos mapas
    printMap ("###############.#########\n"
              "#.........#.............#\n"
              "#.#####.####.######.###.#\n"
              "#.#...............###...#\n"
              "#.#######.#.#######.#.#.#\n"
              "#.#.......#.......#...#.#\n"
              "#.#######.#.##.########.#\n"
              "#...........#...........#\n"
              "#########################\n";

    return 0;

int mapa3() {
    // Exemplo de chamada da função com um dos mapas
    printMap("#########################\n"
             "#.......................#\n"
             "#.#######.#.#######.###.#\n"
             "#.#.......#.......#.#...#\n"
             "#............###........#\n"
             "#............###........#\n"
             "#.#######.#.###########.#\n"
             "#...........#...........#\n"
             "#########################\n");

    return 0;
}
