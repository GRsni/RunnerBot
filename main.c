#include <stdio.h>
#include <stdlib.h>
#include "bot.h"
#include "utility.h"

int main() {
    int i;
    tEstado *inicial = eligeOpcionCrearEstado();
    dispEstado(inicial);
    for(i = ARRIBA; i <= DERECHA; i++) {
        dispOperador(i);
        printf("Es valido: %d\n", esValido(i, inicial));
        if(esValido(i, inicial)) {
            tEstado *siguiente = aplicaOperador(i, inicial);
            printf("Es un estado final: %d\n", testObjetivo(siguiente));
        }
    }
    return 0;
}
