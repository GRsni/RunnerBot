#include <stdio.h>
#include <stdlib.h>
#include "bot.h"
#include "utility.h"

int main() {
    tEstado *inicial=eligeOpcionCrearEstado();
    dispEstado(inicial);
    return 0;
}
