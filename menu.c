#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "utility.h"
#include "busquedaAlum.h"
#include "bot.h"

extern tEstado *estadoInic;
extern int heuristica;

void menuPrincipal() {
    int continua = 1;
    printf("Bienvenido al programa RunnerBot.\nDesarrollado por Santiago Jesus Mas.\n\n");

    estadoInic = menuSeleccionEstado();
    do {
        continua = menuBusqueda();
    } while(continua == 1);
}

tEstado *menuSeleccionEstado() {
    int selector = 0;
    printf("Elige como quieres obtener el estado inicial:\n");
    printf("[1]Introduce el estado por teclado.\n[2]Elige un estado aleatorio.\n[3]Elige un estado ya implementado.\n");
    do {
        printf("->");
        scanf("%d", &selector);
        if(selectorFueraDeRango(selector, 1, 3)) {
            imprimeSelectorFueraDeRango();
        }
    } while(selectorFueraDeRango(selector, 1, 3));
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

int menuFuncionHeuristica() {
    int selector;
    printf("Elige la funcion heuristica a emplear:\n");
    printf("[1]Distancia del robot al objetivo.\n[2]Distancia del robot+distancia del raton.\n");
    do {
        printf("->");
        scanf("%d", &selector);
        if(selectorFueraDeRango(selector, 1, 2)) {
            imprimeSelectorFueraDeRango();
        }
    } while(selectorFueraDeRango(selector, 1, 2));
    return selector;

}

int menuBusqueda() {
    int selector = 0, salida = 1;
    dispEstado(estadoInic);
    printf("Elige el algoritmo de busqueda que quieres emplear:\n");
    printf("[1]Busqueda en anchura\n[2]Busqueda en profundidad.\n[3]Busqueda en profundidad limitada.\n");
    printf("[4]Busqueda en profundidad iterativa.\n[5]Busqueda heuristica voraz.\n[6]Busqueda heuristica A*.\n");
    printf("[7]Busqueda local.\n[8]Busqueda en haz.\n[9]Elegir un nuevo estado inicial.\n[10]Salir del programa.\n");
    do {
        printf("->");
        scanf("%d", &selector);
        if(selectorFueraDeRango(selector, 1, 10)) {
            imprimeSelectorFueraDeRango();
        }
    } while(selectorFueraDeRango(selector, 1, 10));
    if(selector == 10) {
        salida = 0;
    }
    eligeAccionBusquedaSalir(selector);
    return salida;
}

void eligeAccionBusquedaSalir(int selector) {
    int item = 0;
    switch(selector) {
    case 1:
        printf("Realizando la busqueda a ciegas en anchura.\n");
        busquedaACiegas(ANCHURA);
        break;
    case 2:
        printf("Realizando la busqueda a ciegas en profundidad.\n");
        busquedaACiegas(PROFUNDIDAD);
        break;
    case 3:
        item = introduceProfMaxima();
        printf("Realizando la busqueda a ciegas en profundidad limitada hasta profundidad %d.\n", item);
        busquedaProfundidadLimitada(item);
        break;
    case 4:
        printf("Realizando la busqueda a ciegas en profundidad iterativa.\n");
        busquedaProfundidaIterativa();
        break;
    case 5:
        printf("Realizando la busqueda heuristica voraz.\n");
        busquedaHeuristica(GREEDY);
        break;
    case 6:
        heuristica = menuFuncionHeuristica();
        printf("Realizando la busqueda heuristica A*.\n");
        busquedaHeuristica(ASTAR);
        break;
    case 7:
        printf("Realizando la busqueda local.\n");
        busquedaLocal();
        break;
    case 8:
        item = introduceTamanoHaz();
        printf("Realizando la busqueda local en haz con %d nodos.\n", item);
        busquedaHaz(item);
        break;
    case 9:
        estadoInic = menuSeleccionEstado();
        break;
    case 10:
        printf("------SALIENDO DEL PROGRAMA------\n\n");
        break;
    }
    if(selector < 10) {
        system("pause");
    }
}

int introduceProfMaxima() {
    int prof;
    printf("Elige la profundida maxima de busqueda:\n");
    do {
        printf("->");
        scanf("%d", &prof);
        if(prof < 1) {
            printf("La profundidad debe ser mayor de 0\n");
        }
    } while(prof < 1);
    return prof;
}

int introduceTamanoHaz() {
    int item=0;
    printf("Elige el numero de nodos del haz[2-4]:\n");
    do {
        printf("->");
        scanf("%d", &item);
        if(selectorFueraDeRango(item, 2, 4)) {
            imprimeSelectorFueraDeRango();
        }
    } while(selectorFueraDeRango(item, 2, 4));
    return item;
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
