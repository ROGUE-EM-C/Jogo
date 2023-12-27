#include <stdio.h>
#include <string.h>

/*Todos os arquivos devem ser passados para a sua versão .h
(Por exemplo, Splash.c irá virar Splash.h para fazer parte do arquivo main.c)*/

#define MENU_H

// Declaração de variáveis globais
extern char player[7];
extern int rateDificuldade;
extern int rateMoeda;
extern int rateMorcego;
extern int espolio;

// Funções
void acessar_atributos();
void inicializar_dados_globais();

#endif

# Primeira parte do código (Menu.h)

#include "menu.h"
#include "game.h"
#include "config.h"

// Implementação das funções
void acessar_atributos() {
    // Acessando os atributos
    char icone = player[0];
    int gold = player[1];
    // ...
}

void inicializar_dados_globais() {
    // Inicializando as variáveis globais
    // ...
}

# Segunda parte do código (Menu.c)

#ifndef GAME_H
#define GAME_H

// Inclui o arquivo de cabeçalho menu.h
#include "menu.h"

// Funções específicas do jogo
void funcao_do_jogo();

#endif

# Terceira parte do código (Game.h)

#include "game.h"

// Implementação de funções específicas do jogo
void funcao_do_jogo() {
    // Uso das variáveis e funções globais
    acessar_atributos();
    // ...
}

# Quarta parte do código (Game.c)

#ifndef CONFIG_H
#define CONFIG_H

// Inclui o arquivo de cabeçalho menu.h
#include "menu.h"

// Funções relacionadas à configuração
void funcao_de_configuracao();

#endif

# Quinta parte do código (Config.h)

#include "config.h"

// Implementação de funções relacionadas à configuração
void funcao_de_configuracao() {
    // Uso das variáveis e funções globais
    acessar_atributos();
    // ...
}

# Sexta parte do código (Config.c)

#include "menu.h"
#include "game.h"
#include "config.h"

int main() {
    // Uso das funções e variáveis globais
    inicializar_dados_globais();
    funcao_do_jogo();
    funcao_de_configuracao();

    return 0;
}

# Sétima parte do código (main.c)


