#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "utility.h"
#include "busquedaAlum.h"
#include "bot.h"

extern tEstado *inicial;

void menuPrincipal() {
    int continua = 1;
    printf("Bienvenido al programa RunnerBot.\nDesarrollado por Santiago Jesus Mas.\n\n");

    inicial = menuSeleccionEstado();
    dispEstado(inicial);

    do {
    menuBusqueda();
    } while(continua = 1);
}

tEstado *menuSeleccionEstado() {
    int selector = 0;
    printf("Elige como quieres obtener el estado inicial:\n");
    printf("[1]Introduce el estado por teclado.\n[2]Elige un estado aleatorio.\n[3]Elige un estado ya implementado.\n");
    do {
        printf("->");
        scanf("%d", &selector);
        if(compruebaSelectorFueraDeRango(selector, 1, 3)) {
            imprimeSelectorFueraDeRango();
        }
    } while(selector < 1 || selector > 3);
    return eligeModoCrearEstado(selector);
}

tEstado* eligeModoCrearEstado(int selector) {
    if(selector == 1) {
        return introducirEstado();
    } else if(selector == 2) {
        return creaEstadoAleatorio();
    } else {
        return crearEstado(mapa_inicial);
    }
}

void menuBusqueda() {
    int selector = 0, salida;
    printf("Elige el algoritmo de busqueda que quieres emplear:\n");
    printf("[1]Busqueda en anchura\n[2]Busqueda en profundidad.\n[3]Busqueda heuristica\n");
    do {
        printf("->");
        scanf("%d", &selector);
        if(compruebaSelectorFueraDeRango(selector, 1, 3)) {
            imprimeSelectorFueraDeRango();
        }
    } while(selector < 1 || selector > 3);
    eligeTipoDeBusqueda(selector);
}

void eligeTipoDeBusqueda(int selector) {
    switch(selector) {
    case 1:
        printf("Realizando la busqueda a ciegas en anchura.\n");
        busquedaACiegas(0);
        break;
    case 2:
        menuBusquedaProfundidad();
        break;
    case 3:
        menuBusquedaHeuristica();
        break;
    }
}

void menuBusquedaProfundidad() {
    int selector = 0;
    printf("Elige el tipo de busqueda en profundidad a realizar:\n");
    printf("[1]Profundidad a ciegas.\n[2]Profundidad limitada.\n[3]Profundidad iterativa.\n");
    do {
        printf("->");
        scanf("%d", &selector);
        if(compruebaSelectorFueraDeRango(selector, 1, 3)) {
            imprimeSelectorFueraDeRango();
        }
    } while(selector < 1 || selector > 3);

}

void eligeBusquedaProfundidad(int selector) {
    int iter = 0;
    switch(selector) {
    case 1:
        printf("Realizando una busqueda en profundidad a ciegas.\n");
        busquedaACiegas(1);
        break;
    case 2:
        printf("Elige el limite de profundidad a expandir.\n");
        do {
            printf("->");
            scanf("%d", &iter);
            if(compruebaSelectorFueraDeRango(iter, 1, 100000)) {
                imprimeSelectorFueraDeRango();
            }
        } while(iter < 1);
        printf("Realizando una busqueda en profundidad con limite %d.\n", iter);
        busquedaProfundidadLimitada();
        break;
    case 3:
        printf("Realizando busqueda en profundidad iterativa.\n");
        break;
    }
}


void menuBusquedaHeuristica() {

}

void dispEstado(tEstado *estado) {
    int row, col;
    printf("Estado actual:\n");
    imprimeLineaMatriz(N);
    for(row = 0; row < N; row++) {
        printf("|");
        for(col = 0; col < N; col++) {
            char c = ' ';
            if(row == estado->robRow && col == estado->robCol) {
                c = ROBOTC;
            } else if(row == estado->mouseRow && col == estado->mouseCol) {
                c = RATONC;
            } else if (estado->celdas[row][col] == PARED) {
                c = PAREDC;
            }
            imprimeIcono(c);
        }
        printf("\n");
        imprimeLineaMatriz(N);
    }
//    dispEstadoNum(estado);
    dispPosRobotRaton(estado);
}

void dispEstadoNum(tEstado *estado) {
    imprimeMatriz(N, estado->celdas);
}

void dispPosRobotRaton(tEstado *estado) {
    printf("Robot[%d, %d], Raton[%d, %d]\n", estado->robRow, estado->robCol, estado->mouseRow, estado->mouseCol);
}


void dispOperador(unsigned op) {
    printf("\n");
    switch(op) {
    case ARRIBA:
        printf("Movimiento ARRIBA\n");
        break;
    case ABAJO:
        printf("Movimiento ABAJO\n");
        break;
    case IZQUIERDA:
        printf("Movimiento IZQUIERDA\n");
        break;
    case DERECHA:
        printf("Movimiento DERECHA\n");
        break;
    }
}
