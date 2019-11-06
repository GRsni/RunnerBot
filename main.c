#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bot.h"
#include "utility.h"
#include "listaia.h"
#include "menu.h"

tEstado *inicial;

int main() {
    srand(time(NULL));
    inicial== (tEstado* )malloc(sizeof(tEstado));
    menuPrincipal();
//    busqueda();
//    busquedaHeuristica();
    return 0;
}
