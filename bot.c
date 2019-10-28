#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bot.h"
#include "Utility.h"

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

tEstado* eligeEstado(int opcion) {
    tEstado* estado;
    switch(opcion) {
    case 2:
        estado = estadoInicial2();
        break;
    case 3:
        estado = estadoInicial3();
        break;
    case 4:
        estado = estadoInicial4();
        break;
    case 5:
        estado = estadoInicial5();
        break;
    default:
        estado = introducirEstado();
        break;
    }
    return estado;
}

tEstado* estadoInicial2() {
    return crearEstado(mapa_inicial2);
}

tEstado* estadoInicial3() {
    return crearEstado(mapa_inicial3);
}

tEstado* estadoInicial4() {
    return crearEstado(mapa_inicial4);
}

tEstado* estadoInicial5() {
    return crearEstado(mapa_inicial5);
}

tEstado *crearEstado(int celdas[N][N]) {
    tEstado *estado = (tEstado *)malloc(sizeof(tEstado));
    int row, col;
    for(row = 0; row < N; row++) {
        for(col = 0; col < N; col++) {
            int valor = celdas[row][col];
            if(celdas[row][col] == ROBOT) {
                printf("Robot\n");
                estado->robRow = row;
                estado->robCol = col;
                valor = VACIO;
            } else if(celdas[row][col] == RATON) {
                printf("raton\n");
                estado->mouseRow = row;
                estado->mouseCol = col;
                valor = VACIO;
            }
            estado->celdas[row][col] = valor;
        }
    }
    return estado;
}

tEstado* introducirEstado() {
    int i, j, rX, rY;
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
        printf("Introduce la fila del raton: ");
        scanf("%d", &rY);
        printf("Introduce la columna del raton: ");
        scanf("%d", &rX);
    } while(rX < 0 || rX > N - 1 || rY < 0 || rY > N - 1);
    celdas[rY][rX] = RATON;

    do {
        printf("Introduce la fila del robot: ");
        scanf("%d", &rY);
        printf("Introduce la columna del robot: ");
        scanf("%d", &rX);
    } while(rX < 0 || rX > N - 1 || rY < 0 || rY > N - 1);
    celdas[rY][rX] = ROBOT;

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            printf("%d", celdas[i][j]);
        }
        printf("\n");
    }
    return crearEstado(celdas);

}

int coste(unsigned op, tEstado *estado) {
    return 1;
}

int esValido(unsigned op, tEstado *estado) {
    int valido;
    //TODO: Solve problem with this shit
    switch(op) {
    case ARRIBA:
        valido = compruebaArriba(estado);
        break;
    case ABAJO:
        valido = compruebaAbajo(estado);
        break;
    case IZQUIERDA:
        valido = compruebaIzquierda(estado);
        break;
    case DERECHA:
        valido = compruebaDerecha(estado);
        break;
    }
    return valido;
}

int compruebaArriba(tEstado *estado) {
    int rCol = estado->robCol, rRow = estado->robRow, mCol = estado->mouseCol, mRow = estado->mouseRow;
    printf("%d, %d, %d\n", rRow == 0, estado->celdas[rRow - 1][rCol] == PARED, rCol == mCol - 1 && rRow == mRow);
    return !(rRow == 0 || estado->celdas[rRow - 1][rCol] == PARED || (rCol == mCol - 1 && rRow == mRow));
}

int compruebaAbajo(tEstado *estado) {
    int rCol = estado->robCol, rRow = estado->robRow, mCol = estado->mouseCol, mRow = estado->mouseRow;
    printf("%d, %d, %d\n", rRow == N - 1, estado->celdas[rRow + 1][rCol] == PARED, rCol == mCol - 1 && rRow == mRow - 2);
    return !(rRow == N - 1 || estado->celdas[rRow + 1][rCol] == PARED || (rCol == mCol - 1 && rRow == mRow - 2));
}

int compruebaIzquierda(tEstado *estado) {
    int rCol = estado->robCol, rRow = estado->robRow, mCol = estado->mouseCol, mRow = estado->mouseRow;
    printf("%d, %d, %d\n", rCol == 0, estado->celdas[rRow][rCol - 1] == PARED, rCol == mCol + 2 && rRow == mRow + 1);
    return !(rCol == 0 || estado->celdas[rRow][rCol - 1] == PARED || (rCol == mCol + 2 && rRow == mRow + 1));
}

int compruebaDerecha(tEstado *estado) {
    int rCol = estado->robCol, rRow = estado->robRow, mCol = estado->mouseCol, mRow = estado->mouseRow;
    printf("%d, %d, %d\n", rCol == N - 1, estado->celdas[rRow][rCol + 1] == PARED, rCol == mCol && rRow == mRow + 1);
    return !(rCol == N - 1 || estado->celdas[rRow][rCol + 1] == PARED || (rCol == mCol && rRow == mRow + 1));
}

tEstado *aplicaOperador(unsigned op, tEstado *estado) {
    tEstado *nuevo = (tEstado *) malloc(sizeof(tEstado));
    memcpy(nuevo, estado, sizeof(tEstado));

    switch(op) {
    case ARRIBA:
        nuevo->robRow--;
        if(nuevo->mouseCol != N - 1) { //if mouse is in lower right corner, it wont move again
            if(nuevo->mouseCol > 0) {//check if mouse would go out of the grid
                mueveRatonArribaIzquierda(nuevo);
            }
        }
        break;
    case ABAJO:
        nuevo->robRow++;
        if(nuevo->mouseCol != N - 1) { //if mouse is in lower right corner, it wont move again
            if(nuevo->mouseCol > 0) {//check if mouse goes out of the grid
                mueveRatonArribaIzquierda(nuevo);
            }
        }
        break;

    case IZQUIERDA:
        nuevo->robCol--;
        if(nuevo->mouseCol != N - 1) { //if mouse is in lower right corner, it wont move again
            if(nuevo->mouseCol > 0) { //check if mouse would go out of the grid
                nuevo->mouseCol--;
                nuevo->mouseRow--;
            }
        }
        break;
    case DERECHA:
        nuevo->robCol++;
        if(nuevo->mouseCol != N - 1) { //if mouse is in lower right corner, it wont move again
            if(nuevo->mouseCol > 0) {
                nuevo->mouseCol--;
                nuevo->mouseRow--;
            }
        }
        break;
    }
}

void mueveRaton(tEstado *estado, int direccion) {
    if(estado->mouseCol != N - 1) {
        if(direccion == ARRIBA) {

        }
    }
}

void mueveRatonAbajoDerecha(tEstado *estado) {
    estado->mouseCol--;
    estado->mouseRow--;
}

void mueveRatonArribaIzquierda(tEstado *estado) {
    estado->mouseCol++;
    estado->mouseRow++;
}

void dispEstado(tEstado *estado) {
    int row, col;
    printf("Estado actual:\n");
    printGridLine(N);
    for(row = 0; row < N; row++) {
        printf("|");
        for(col = 0; col < N; col++) {
            char c = ' ';
            if(row == estado->robRow & col == estado->robCol) {
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
    dispEstadoNum(estado);
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
