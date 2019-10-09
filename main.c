#include <stdio.h>
#include <stdlib.h>
#include "bot.h"

int main() {
    tEstado *inicial=crearEstado(mapa_inicial);
    dispEstado(inicial);
    return 0;
}
