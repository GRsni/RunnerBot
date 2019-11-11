#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bot.h"
#include "utility.h"
#include "listaia.h"
#include "menu.h"

tEstado *inicial;
int heuristica;

void inicializaPrograma() {
    srand(time(NULL));
    inicial = (tEstado* )malloc(sizeof(tEstado));
}

int main() {
    inicializaPrograma();
    menuPrincipal();
    return 0;
}


