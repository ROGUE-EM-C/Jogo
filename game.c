#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

/*Todos os arquivos devem ser passados para a sua versão .h
(Por exemplo, Splash.c irá virar Splash.h para fazer parte do arquivo main.c)*/

typedef struct {
    int x, y;
} Coordinates;

void imprimir_ponte_flag, imprimir_mapa2_flag; */Não chequei se precisa, mas ai está*/
void imprimir_mapa1(WINDOW *win);
void imprimir_moedas(WINDOW *win, Coordinates *moedas, int num_moedas);
void imprimir_bats(WINDOW *win, Coordinates *bats, int num_bats);
void youDied(int ouro);
void mover_morcegos(Coordinates *bats, int num_bats);
void atacar_morcego(int y, int x, Coordinates *bats, int *num_bats);

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);

    Coordinates moedas[100];  // Ajuste o tamanho conforme necessário
    Coordinates bats[100];    // Ajuste o tamanho conforme necessário
    int num_moedas = 0;
    int num_bats = 0;

    // Restante do código...

    endwin();
    return 0;
}

// Função para imprimir o mapa1
void imprimir_mapa1(WINDOW *win) {
    // Implementação...
}

// Função para imprimir as moedas
void imprimir_moedas(WINDOW *win, Coordinates *moedas, int num_moedas) {
    // Implementação...
}

// Função para imprimir os morcegos
void imprimir_bats(WINDOW *win, Coordinates *bats, int num_bats) {
    // Implementação...
}

// Função chamada em caso de derrota
void youDied(int ouro) {
    die = [
        " #     #  #######  #     #           ######      #     #######  ######",
        " #     #  #     #  #     #           #     #     #     #        #     #",
        " #######  #     #  #     #           #     #     #     ####     #     #",
        "       #  #     #  #     #           #     #     #     #        #     #",
        " #######  #######  #######           ######      #     #######  ######"]
    // Implementação...
}

// Função para mover os morcegos
void mover_morcegos(Coordinates *bats, int num_bats) {
    // Implementação...
}

// Função para atacar um morcego
// Estrutura para armazenar as coordenadas dos morcegos
struct Bat {
    int y;
    int x;
};

// Estrutura para armazenar dados do jogador
struct Player {
    // Outros campos do jogador
    double life;
};

// Estrutura para armazenar dados de configuração
struct Config {
    double rateDificuldade;
    struct Player player;
};

void mover_morcegos(struct Bat bats[], int num_bats, struct Map *mp, struct Config *cf) {
    for (int i = 0; i < num_bats; i++) {
        // Escolhe uma direção aleatória
        const char *direcoes[] = {"esquerda", "cima", "baixo", "direita", "cima", "baixo"};
        const char *direcao = direcoes[rand() % 6]; // Prioriza esquerda e direita

        int novo_y = bats[i].y;
        int novo_x = bats[i].x;

        // Calcula as novas coordenadas baseadas na direção escolhida
        if (strcmp(direcao, "cima") == 0) {
            novo_y = (novo_y - 1 >= 0) ? novo_y - 1 : 0;
        } else if (strcmp(direcao, "baixo") == 0) {
            novo_y = (novo_y + 1 < mp->linhas) ? novo_y + 1 : mp->linhas - 1;
        } else if (strcmp(direcao, "esquerda") == 0) {
            novo_x = (novo_x - 1 >= 0) ? novo_x - 1 : 0;
        } else if (strcmp(direcao, "direita") == 0) {
            novo_x = (novo_x + 1 < mp->colunas) ? novo_x + 1 : mp->colunas - 1;
        }

        // Verifica se a nova posição é válida
        if (mp->mapa[novo_y][novo_x] == '.') {
            bats[i].y = novo_y;
            bats[i].x = novo_x;
        }

        // Ataca morcegos na nova posição
        atacar_morcegos(bats[i].y, bats[i].x, bats, &num_bats, cf);
    }
}

int main() {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Exemplo de uso das estruturas
    struct Bat bats[] = {{2, 3}, {4, 13}, {8, 2}};
    int num_bats = 3;

    struct Map mapa = {
        // Substitua esta matriz de exemplo pela representação real do seu mapa
        .mapa = (char*[]){"#########",
                           "#.......#",
                           "#.......#",
                           "#.......#",
                           "#########"},
        .linhas = 5,
        .colunas = 9
    };

    struct Config config = {0.0, {10.0}}; // Exemplo de configuração com taxa de dificuldade zero e vida inicial 10.0

    // Chama a função para mover os morcegos
    mover_morcegos(bats, num_bats, &mapa, &config);

    printf("Novas coordenadas dos morcegos: ");
    for (int i = 0; i < num_bats; i++) {
        printf("(%d, %d) ", bats[i].y, bats[i].x);
    }
    printf("\n");

    printf("Vida do jogador: %.2f\n", config.player.life);

    return 0;
    
}

int main() {
    struct Bat bats[] = {{1, 2}, {3, 4}, {5, 6}};
    int num_bats = 3;

    struct Config config = {0.0, {10.0}}; // Exemplo de configuração com taxa de dificuldade zero e vida inicial 10.0
    
    struct Bat* new_bats = atacar_morcego(3, 4, bats, &num_bats, &config);

    printf("Novas coordenadas x e y do morcego");
    for (int i = 0; i < num_bats; i++) {
        printf("(%d, %d) ", new_bats[i].y, new_bats[i].x);
    }
    printf("\nVida do jogador: %.2f\n", config.player.life);

    return 0;
}

void nevoa1(WINDOW *win) {
    mvwprintw(win, 2, 3, "MMMMM");
    mvwprintw(win, 4, 13, "MMMM");
    mvwprintw(win, 8, 2, "MMMMMM");
    wrefresh(win);
}

void nevoa2(WINDOW *win) {
    mvwprintw(win, 20, 3, "MMMMM");
    mvwprintw(win, 16, 7, "MMMM");
    mvwprintw(win, 20, 14, "MMMMMM");
    wrefresh(win);
}

int main() {
    initscr();
    noecho();
    curs_set(FALSE);

    WINDOW *win = newwin(25, 40, 0, 0);
    box(win, 0, 0);
    refresh()

    nevoa1(win);
    getch()

    nevoa2(win);
    getch()

    endwin();
    return 0;
