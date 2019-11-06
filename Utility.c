#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Utility.h"
#include "bot.h"
#include "listaia.h"

void imprimeLineaMatriz(int cols) {
    int i;
    printf("+");
    for(i = 0; i < cols; i++) {
        printf("---+");
    }
    printf("\n");
}

void imprimeIcono(char c) {
    if(c == PAREDC) {
        printf("%c%c%c|", c, c, c);
    } else {
        printf(" %c |", c);
    }
}

void imprimeErrorPosRobot(int row, int col, int celdas[N][N]) {
    if(row < 0 || row > N - 1 || col < 0 || col > N - 1) {
        ERROR("Posicion del robot fuera del mapa")
    }
}

void inicializaMatrizCero(int tam, int celdas[tam][tam]) {
    int i, j;
    for(i = 0; i < tam; i++) {
        for(j = 0; j < tam; j++) {
            celdas[i][j] = 0;
        }
    }
}

void imprimeMatriz(int tam, int celdas[tam][tam]) {
    int i, j;
    for(i = 0; i < tam; i++) {
        for(j = 0; j < tam; j++) {
            printf("%d", celdas[i][j]);
        }
        printf("\n");
    }
}

int compruebaSelectorFueraDeRango(int selec, int inf, int sup) {
    return selec < inf || selec > sup;
}

void imprimeSelectorFueraDeRango() {
    printf("Selector no valido. Introduce otro valor.\n");
}
