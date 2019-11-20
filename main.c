#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bot.h"
#include "utility.h"
#include "listaia.h"
#include "menu.h"
#include "busquedaAlum.h"

tEstado *estadoInic;
//int heuristica=DISTROB;
int heuristica;

void inicializaPrograma() {
    srand(time(NULL));
    estadoInic = (tEstado* )malloc(sizeof(tEstado));
}

int main() {
    inicializaPrograma();
    menuPrincipal();
    return 0;
}


