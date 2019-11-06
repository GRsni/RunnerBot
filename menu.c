#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "utility.h"

void menuPrincipal() {
    int continua = 1, tipoBusqueda = 0;
    tEstado *inicial = (tEstado* )malloc(sizeof(tEstado));
    printf("Bienvenido al programa RunnerBot.\nDesarrollado por Santiago Jesus Mas.\n\n");

    inicial=menuSeleccionEstado();
    dispEstado(inicial);
//    do {
//
//    } while(continua = 1);
}

tEstado *menuSeleccionEstado() {
    int selector = 0;
    printf("Elige como quieres obtener el estado inicial:\n");
    printf("[1]Introduce el estado por teclado.\n[2]Elige un estado aleatorio.\n[3]Elige un estado ya implementado.\n->");
    scanf("%d", &selector);
    return eligeModoCrearEstado(selector);
}

void menuBusqueda(tEstado *estado) {

}

tEstado* eligeModoCrearEstado(int selector) {
    if(selector == 1) {
        return introducirEstado();
    } else if(selector == 2) {
        return eligeEstadoAleatorio();
    } else {
        return crearEstado(mapa_inicial);
    }
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
        imprimeErrorPosRobot(row, col, celdas);
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

tEstado* eligeEstadoAleatorio() {
    int paredes = N - 1, i, col, row;
    printf("Creando estado aleatorio[%dx%d] con %d pared%s", N, N, N - 1, (N == 2) ? ".\n" : "des.\n");

    int celdas[N][N];
    inicializaMatrizCero(N, celdas);

    eligePosRatonAleatoria(N, celdas);
//    imprimeMatriz(N, celdas);

    eligePosRobotAleatoria(N, celdas);
//    imprimeMatriz(N, celdas);

    colocaParedesAleatorias(N, celdas);
//    imprimeMatriz(N, celdas);

    return crearEstado(celdas);
}

void eligePosRatonAleatoria(int tam, int celdas[tam][tam]) {
    int pos;
    do {
        pos = rand() % N;
    } while(celdas[pos][pos] == PARED || celdas[pos][pos] == ROBOT || pos == N - 1);
    printf("Posicionando el raton en [%d, %d]\n", pos, pos);
    celdas[pos][pos] = RATON;
}

void eligePosRobotAleatoria(int tam, int celdas[tam][tam]) {
    int col, row;
    do {
        row = rand() % N;
        col = rand() % N;
    } while(celdas[row][col] == PARED || celdas[row][col] == RATON || (row == N - 1 && col == N - 1));
    printf("Posicionando el robot en [%d, %d]\n", row, col);
    celdas[row][col] = ROBOT;
}

void colocaParedesAleatorias(int tam, int celdas[tam][tam]) {
    int i, col, row;
    for(i = 0; i < tam - 1; i++) {
        do {
            col = rand() % N;
            row = rand() % N;
        } while((col == N - 1 && row == N - 1) || celdas[row][col] == PARED || celdas[row][col] == ROBOT || celdas[row][col] == RATON);
        printf("Colocando muro en [%d, %d]\n", row, col);
        celdas[row][col] = PARED;
    }
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
