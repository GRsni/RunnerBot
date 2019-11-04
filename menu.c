#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "utility.h"

tEstado* eligeOpcionCrearEstado() {
    char eleccion;
    int opcion = N;
    printf("Quieres crear un estado desde cero o elegir uno de los existentes?[s]i/[n]o: ");
    scanf("%c", &eleccion);
    if(eleccion == 's') {
        opcion = 0;
    }
    return eligeEstado(opcion);
}

tEstado* introducirEstado() {
    int i, j, row, col;
    int celdas[N][N];

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            do {
                printf("Elige que hay en la celda[%d, %d]:\nVACIO[0]|PARED[1]: ", i, j);
                scanf("%d", &celdas[i][j]);
            } while(celdas[i][j] < VACIO || celdas[i][j] > PARED);
        }
    }
    do {
        printf("Introduce la casilla del raton(en la diagonal principal)[0-%d]: ", N - 1);
        scanf("%d", &row);
    } while(row < 0 || row > N - 1);
    celdas[row][row] = RATON;

    do {
        printf("Introduce la fila del robot[0-%d]: ", N - 1);
        scanf("%d", &row);
        printf("Introduce la columna del robot[0-%d]: ", N - 1);
        scanf("%d", &col);
        printf("\n");
    } while(row < 0 || row > N - 1 || col < 0 || col > N - 1 || celdas[row][col] != VACIO);
    celdas[row][col] = ROBOT;

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            printf("%d", celdas[i][j]);
        }
        printf("\n");
    }
    return crearEstado(celdas);

}

tEstado* eligeEstado(int opcion) {
    tEstado* estado;
    switch(opcion) {
    case 2:
        estado = crearEstado(mapa_inicial2);
        break;
    case 3:
        estado = crearEstado(mapa_inicial3);
        break;
    case 4:
        estado = crearEstado(mapa_inicial4);
        break;
    case 5:
        estado = crearEstado(mapa_inicial5);
        break;
    default:
        estado = introducirEstado();
        break;
    }
    return estado;
}

void dispEstado(tEstado *estado) {
    int row, col;
    printf("Estado actual:\n");
    printGridLine(N);
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
            printIcon(c);
        }
        printf("\n");
        printGridLine(N);
    }
//    dispEstadoNum(estado);
    dispPosRobotRaton(estado);
}

void dispEstadoNum(tEstado *estado) {
    int row, col;
    for(row = 0; row < N; row++) {
        for(col = 0; col < N; col++) {
            printf("%d", estado->celdas[row][col]);
        }
        printf("\n");
    }
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
