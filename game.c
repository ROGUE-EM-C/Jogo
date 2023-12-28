#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

/*Todos os arquivos devem ser passados para a sua versão .h
(Por exemplo, Splash.c irá virar Splash.h para fazer parte do arquivo main.c)*/

typedef struct {
    int y, x; // Em NCurses, o uso das coordenadas é diferente e dado por (y,x) ao invés de (x,y). //
} Coordinates;

void imprimir_ponte_flag, imprimir_mapa2_flag; // Não chequei se precisa, mas aí está //
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

    Coordinates moedas[100]; // Ajustar isso aqui // 
    Coordinates bats[100]; // Ajustar isso também //
    int num_moedas = 0;
    int num_bats = 0;

    endwin();
    return 0;
}

int posicao_valida(char mapa1[], int y, int x) {
    return mapa1[y * 31 + x] == '.'; // Retorna 1 se a posição for válida (ponto), 0 se não for
}

struct Map {
    char* mapa1;
};

void desenhar_mapa1(WINDOW *win, struct Map *mp) {
    char *mapa1 = mp->mapa1;

    // Imprime o mapa1 na janela fornecida
    for (int i = 0; i < 10; i++) { // Pode-se ajustar o tamanho do mapa //
        for (int j = 0; j < 30; j++) { // Mesma coisa aqui //
            if (mapa1[i * 31 + j] == '#') {
                mvwaddch(win, i, j, '#');  // Parede
            } else {
                mvwaddch(win, i, j, mapa1[i * 31 + j]); // Aqui também, naturalmente //
            }
        }
    }

    wrefresh(win);
}

int main() {
    initscr();

    WINDOW *win = newwin(10, 30, 0, 0);

    struct Map mapa = {
        .mapa1 = "#########################\n"
                "#.........#.............#\n"
                "#.#######.#.#######.###.#\n"
                "#.#.......#.......#.#...#\n"
                "#.#######.#.#######.#.#.#\n"
                "#.#.......#.......#...#.#\n"
                "#.#######.#.###########.#\n"
                "#...........#...........#\n"
                "#########################\n"
    };

    desenhar_mapa1(win, &mapa);

    getch();

    endwin();

    return 0;
}

void imprimir_mapa1(WINDOW *win, int personagem_y, int personagem_x) {
    char *mapa1 =
        "#########################\n"
        "#.........#.............#\n"
        "#.#######.#.#######.###.#\n"
        "#.#.......#.......#.#...#\n"
        "#.#######.#.#######.#.#.#\n"
        "#.#.......#.......#...#.#\n"
        "#.#######.#.###########.#\n"
        "#...........#...........#\n"
        "#########################\n";

    for (int i = 0; i < 10; i++) { // Pode alterar aqui, se precisar //
        for (int j = 0; j < 30; j++) { // Aqui também //
            if (i == personagem_y && j == personagem_x) {
                mvwaddch(win, i, j, 'P'); // Personagem
            } else if (posicao_valida(mapa1, i, j)) {
                mvwaddch(win, i, j, '.'); // Ponto
            } else {
                mvwaddch(win, i, j, '#');
            }
        }
    }

    wrefresh(win);
}

int main() {
    initscr();

    WINDOW *win = newwin(12, 30, 0, 0); // EXEMPLO DE COORDENADAS //

    imprimir_mapa1(win, 3, 3); // EXEMPLO DE COORDENADAS //

    getch();

    endwin();

    return 0;
}

struct Map {
    char* mapa1;
};

// Estrutura para armazenar configurações do jogador
struct PlayerConfig {
    int player[6];
    int rateMoeda;
    int rateDificuldade;
};

// Função para adicionar moeda aleatória
int* adicionar_moeda_aleatoria(char mapa1[]) {
    int* posicao_moeda = malloc(sizeof(int) * 2);
    int pos_valida = 0;

    while (!pos_valida) {
        posicao_moeda[0] = rand() % 10;  // Linha aleatória
        posicao_moeda[1] = rand() % 30;  // Coluna aleatória

        // Verifica se a posição é válida (não é uma parede)
        pos_valida = (mapa1[posicao_moeda[0] * 31 + posicao_moeda[1]] == '.');
    }

    return posicao_moeda;
}

void imprimir_moedas(WINDOW *win, int moedas[][2], int num_moedas) {
    for (int i = 0; i < num_moedas; i++) {
        mvwaddch(win, moedas[i][0], moedas[i][1], 'C');  // Caractere para representar moeda
    }

    wrefresh(win);  // Atualiza a tela
}

int main() {
    // Inicializa o modo curses
    initscr();
    
    WINDOW *win = newwin(10, 30, 0, 0); // Podemos alterar aqui //

    struct Map mapa = {
        .mapa1 = "#########################\n"
                "#.........#.............#\n"
                "#.#######.#.#######.###.#\n"
                "#.#.......#.......#.#...#\n"
                "#.#######.#.#######.#.#.#\n"
                "#.#.......#.......#...#.#\n"
                "#.#######.#.###########.#\n"
                "#...........#...........#\n"
                "#########################\n"
    };

    struct PlayerConfig cf = {
        // Substitua esses valores por configurações reais
        .player = {0, 0, 0, 0, 0, 0},
        .rateMoeda = 3,
        .rateDificuldade = 1
    };

    int moedas[10][2];  // Supondo que haja, no máximo, 10 moedas simultaneamente
    int num_moedas = 0;

    srand(time(NULL));

    if (cf.player[3] % cf.rateMoeda == 0 && cf.player[3] != 0) {
        int* posicao_moeda = adicionar_moeda_aleatoria(mapa.mapa1);
        if (posicao_moeda) {
            moedas[num_moedas][0] = posicao_moeda[0];
            moedas[num_moedas][1] = posicao_moeda[1];
            num_moedas++;
            free(posicao_moeda);
        }
    }

    imprimir_moedas(win, moedas, num_moedas);

    getch();

    endwin();

    return 0;
}

struct Map {
    char* mapa1;
};

// Estrutura para armazenar configurações do jogador
struct PlayerConfig {
    int player[6];
    int rateMoeda;
    int rateDificuldade;
};

// Função para adicionar morcego aleatório
int* adicionar_morcego_aleatorio(char mapa1[]) {
    int* posicao_morcego = malloc(sizeof(int) * 2);
    int pos_valida = 0;

    while (!pos_valida) {
        posicao_morcego[0] = rand() % 10;  // Linha aleatória
        posicao_morcego[1] = rand() % 30;  // Coluna aleatória

        // Verifica se a posição é válida (não é uma parede ou outra entidade)
        pos_valida = (mapa1[posicao_morcego[0] * 31 + posicao_morcego[1]] == '.');
    }

    return posicao_morcego;
}

// Função para imprimir morcegos
void imprimir_morcegos(WINDOW *win, int morcegos[][2], int num_morcegos) {
    for (int i = 0; i < num_morcegos; i++) {
        mvwaddch(win, morcegos[i][0], morcegos[i][1], 'B');  // Caractere para representar morcego
    }

    wrefresh(win); 
}

int main() {
   
    initscr();

    WINDOW *win = newwin(10, 30, 0, 0);

    struct Map mapa = {
        // Substitua esta string de exemplo pela representação real do seu mapa1
        .mapa1 = "#########################\n"
                "#.........#.............#\n"
                "#.#######.#.#######.###.#\n"
                "#.#.......#.......#.#...#\n"
                "#.#######.#.#######.#.#.#\n"
                "#.#.......#.......#...#.#\n"
                "#.#######.#.###########.#\n"
                "#...........#...........#\n"
                "#########################\n"
    };

    struct PlayerConfig cf = {
        // Podemos mudar todos os valores que estão aqui abaixo.
        .player = {0, 0, 0, 0, 0, 0},
        .rateMoeda = 3,
        .rateDificuldade = 1
    };

    int morcegos[10][2];  // Supondo que haja, no máximo, 10 morcegos simultaneamente
    int num_morcegos = 0;

    srand(time(NULL));

    if (cf.player[3] % 5 == 0 && cf.player[3] != 0) {
        int* posicao_morcego = adicionar_morcego_aleatorio(mapa.mapa1);
        if (posicao_morcego) {
            morcegos[num_morcegos][0] = posicao_morcego[0];
            morcegos[num_morcegos][1] = posicao_morcego[1];
            num_morcegos++;
            free(posicao_morcego);
        }
    }

    imprimir_morcegos(win, morcegos, num_morcegos);

    getch();

    endwin();

    return 0;
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

    void imprimir_mapa2(struct Map *mp, int* moedas, int* bats) {
    char* mapa2 = mp->mapa2;
    printf("Não tem sáida. Você morre aqui. \n");

    int i, j;
    for (i = 0; mapa2[i] != '\0'; i++) {
        for (j = 0; mapa2[i] != '\n'; j++) {
            char ch = mapa2[i];
            printf("%c", ch);
        }
        printf("\n");
    }

    imprimir_moedas(moedas);
    imprimir_bats(bats);
}

int main() {
    // Exemplo de uso da estrutura Map e chamada da função imprimir_mapa2
    struct Map mapa = {
        // Substitua esta string de exemplo pela representação real do seu mapa2
        .mapa2 = ("###############.#########\n"
                  "#.........#.............#\n"
                  "#.#####.####.######.###.#\n"
                  "#.#...............###...#\n"
                  "#.#######.#.#######.#.#.#\n"
                  "#.#.......#.......#...#.#\n"
                  "#.#######.#.##.########.#\n"
                  "#...........#...........#\n"
                  "#########################\n";
    };

    int moedas[] = {};
    int bats[] = {};

    // Chama a função para imprimir o mapa2
    imprimir_mapa2(&mapa, moedas, bats);

    return 0;
}

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
