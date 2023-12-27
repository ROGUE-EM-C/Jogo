#include <stdio.h>
#include <unistd.h>

/*Todos os arquivos devem ser passados para a sua versão .h
(Por exemplo, Splash.c irá virar Splash.h para fazer parte do arquivo main.c)*/

int height, width, colunas, x, y;

void clear() {
    // Implemente a função clear() conforme necessário
}

void splash_animation(char matriz[5][88]) {
    for (colunas = 1; colunas <= width; colunas++) {
        for (x = 0; x < height; x++) {
            for (y = 0; y < colunas; y++) {
                printf("%c", matriz[x][y]);
            }
            printf("\n");
        }
        sleep(1);
        clear();
    }
}

void splash_estatica(char matriz[5][88]) {
    for (x = 0; x < height; x++) {
        for (y = 0; y < width; y++) {
            printf("%c", matriz[x][y]);
        }
        printf("\n");
    }
}

int splash() {
    // Exemplo de matriz (ajuste conforme necessário)
    char matriz[5][88] = {
    "    ##     ##  #    #####       #####   #     #  #     #   #####  ######  #####   #     #",
    "    ##     ##  #   #            #     # #     #  ##    #  #       #      #     #  ##    #",
    "    ##     ##     ######        #     # #     #  # #   #  #  #### #####  #     #  # #   #",
    "#   ## #   ##          #        #     # #     #  #  #  #  #     # #      #     #  #  #  #",
    " ####   ####     ######         #####    #####   #    ##   #####  ######  #####   #    ##"

    };

    height = 5;
    width = 88;

    splash_animation(matriz);
    // clear();  // Comente ou remova essa linha se a função clear() não estiver implementada
    splash_estatica(matriz);

    return 0;
}

