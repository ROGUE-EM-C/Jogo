#include <stdio.h>
#include <stdlib.h>

/*Todos os arquivos devem ser passados para a sua versão .h
(Por exemplo, Splash.c irá virar Splash.h para fazer parte do arquivo main.c)*/

// Função para limpar a tela
void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Função para posicionar o cursor na tela
void gotoxy(int x, int y) {
    #ifdef _WIN32
        printf("\x1b[%d;%df", y, x);
    #else
        printf("\x1b[%d;%df", y, x);
    #endif
}

// Função para inicializar a tela
void init(int lines) {
    clear_screen();
    for (int i = 0; i < lines; i++) {
        printf("\n");
    }
    fflush(stdout);
}

// Função para obter o tamanho do terminal
void get_terminal_size(int *lines, int *columns) {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        *lines = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        *columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    #else
        struct winsize ws;
        ioctl(0, TIOCGWINSZ, &ws);
        *lines = ws.ws_row;
        *columns = ws.ws_col;
    #endif
}

// Função para inicializar tudo
void init_all() {
    int lines, columns;
    get_terminal_size(&lines, &columns);
    init(lines);
    printf("%d %d\n", lines, columns);
}

// Função para resetar uma área da tela
void reset(int x, int y, int lines, int columns) {
    gotoxy(x, y);
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            printf(" ");
        }
        printf("\n");
    }
}

int main() {
    // Exemplo de chamadas
    init_all();
    reset(5, 5, 3, 10);

    return 0;
