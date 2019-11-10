#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bot.h"
#include "Utility.h"
#include "menu.h"

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

tEstado* creaEstadoAleatorio() {
    printf("Creando estado aleatorio[%dx%d] con %d pared%s", N, N, N - 1, (N == 2) ? ".\n" : "es.\n");

    int celdas[N][N];
    inicializaMatrizCero(N, celdas);

    eligePosRatonAleatoria(N, celdas);

    eligePosRobotAleatoria(N, celdas);

    colocaParedesAleatorias(N, celdas);

    return crearEstado(celdas);
}


tEstado *crearEstado(int celdas[N][N]) {
    tEstado *estado = (tEstado *)malloc(sizeof(tEstado));
    int row, col;
    for(row = 0; row < N; row++) {
        for(col = 0; col < N; col++) {
            int valor = celdas[row][col];
            if(celdas[row][col] == ROBOT) {
                estado->robRow = row;
                estado->robCol = col;
                valor = VACIO;
            } else if(celdas[row][col] == RATON) {
                estado->mouseRow = row;
                estado->mouseCol = col;
                valor = VACIO;
            }
            estado->celdas[row][col] = valor;
        }
    }
    return estado;
}

void eligePosRatonAleatoria(int tam, int celdas[tam][tam]) {
    int pos;
    do {
        pos = rand() % N;
    } while(celdas[pos][pos] == PARED || celdas[pos][pos] == ROBOT || pos == N - 1);
//    printf("Posicionando el raton en [%d, %d]\n", pos, pos);
    celdas[pos][pos] = RATON;
}

void eligePosRobotAleatoria(int tam, int celdas[tam][tam]) {
    int col, row;
    do {
        row = rand() % N;
        col = rand() % N;
    } while(celdas[row][col] == PARED || celdas[row][col] == RATON || (row == N - 1 && col == N - 1));
//    printf("Posicionando el robot en [%d, %d]\n", row, col);
    celdas[row][col] = ROBOT;
}

void colocaParedesAleatorias(int tam, int celdas[tam][tam]) {
    int i, col, row;
    for(i = 0; i < tam - 1; i++) {
        do {
            col = rand() % N;
            row = rand() % N;
        } while((col == N - 1 && row == N - 1) || celdas[row][col] == PARED || celdas[row][col] == ROBOT || celdas[row][col] == RATON);
//        printf("Colocando muro en [%d, %d]\n", row, col);
        celdas[row][col] = PARED;
    }
}

int coste(unsigned op, tEstado *estado) {
    return 1;
}

int esValido(unsigned op, tEstado *estado) {
    int valido;
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
    int nextMCol = mCol, nextMRow = mRow;
    if(mRow > 0) {//raton se mueve si no esta en la esquina
        nextMCol = mCol - 1;
        nextMRow = mRow - 1;
    }

    return !(rRow == 0 || estado->celdas[rRow - 1][rCol] == PARED || (rCol == nextMCol && rRow - 1 == nextMRow));
}

int compruebaAbajo(tEstado *estado) {
    int rCol = estado->robCol, rRow = estado->robRow, mCol = estado->mouseCol, mRow = estado->mouseRow;
    int nextMCol = mCol, nextMRow = mRow;
    if(mRow > 0) {//raton se mueve si no esta en la esquina
        nextMCol = mCol - 1;
        nextMRow = mRow - 1;
    }
//    printf("%d, %d, %d\n", rRow == N - 1, estado->celdas[rRow + 1][rCol] == PARED, rCol == mCol - 1 && rRow == mRow - 2);
    return !(rRow == N - 1 || estado->celdas[rRow + 1][rCol] == PARED || (rCol == nextMCol && rRow + 1 == nextMRow));
}

int compruebaIzquierda(tEstado *estado) {
    int rCol = estado->robCol, rRow = estado->robRow, mCol = estado->mouseCol, mRow = estado->mouseRow;
    int nextMCol = mCol, nextMRow = mRow;
    if(mRow < N - 1) {//raton se mueve si no esta en la esquina
        nextMCol = mCol + 1;
        nextMRow = mRow + 1;
    }
//    printf("%d, %d, %d\n", rCol == 0, estado->celdas[rRow][rCol - 1] == PARED, rCol == mCol + 2 && rRow == mRow + 1);
    return !(rCol == 0 || estado->celdas[rRow][rCol - 1] == PARED || (rCol - 1 == nextMCol && rRow == nextMRow));
}

int compruebaDerecha(tEstado *estado) {
    int rCol = estado->robCol, rRow = estado->robRow, mCol = estado->mouseCol, mRow = estado->mouseRow;
    int nextMCol = mCol, nextMRow = mRow;
    if(mRow < N - 1) {//raton se mueve si no esta en la esquina
        nextMCol = mCol + 1;
        nextMRow = mRow + 1;
    }
//    printf("%d, %d, %d\n", rCol == N - 1, estado->celdas[rRow][rCol + 1] == PARED, rCol == mCol && rRow == mRow + 1);
    return !(rCol == N - 1 || estado->celdas[rRow][rCol + 1] == PARED || (rCol + 1 == nextMCol && rRow == nextMRow));
}

tEstado *aplicaOperador(unsigned op, tEstado *estado) {
    tEstado *nuevo = (tEstado *) malloc(sizeof(tEstado));
    memcpy(nuevo, estado, sizeof(tEstado));

    switch(op) {
    case ARRIBA:
        nuevo->robRow--;
        break;
    case ABAJO:
        nuevo->robRow++;
        break;

    case IZQUIERDA:
        nuevo->robCol--;
        break;
    case DERECHA:
        nuevo->robCol++;
        break;
    }
    if(op == ARRIBA || op == ABAJO) {
        mueveRaton(nuevo, ARRIBA);
    } else if(op == IZQUIERDA || op == DERECHA) {
        mueveRaton(nuevo, ABAJO);
    }
    return nuevo;
}

void mueveRaton(tEstado *estado, int direccion) {
    if(estado->mouseCol != N - 1) { //mouse wont move if at lower right corner
        if(direccion == ARRIBA) {
            mueveRatonArribaIzquierda(estado);
        } else if(direccion == ABAJO) {
            mueveRatonAbajoDerecha(estado);
        }
    }
}

void mueveRatonAbajoDerecha(tEstado *estado) {
    if(estado->mouseCol < N - 1) {
        estado->mouseCol++;
        estado->mouseRow++;
    }
}

void mueveRatonArribaIzquierda(tEstado *estado) {
    if(estado->mouseCol > 0) {
        estado->mouseCol--;
        estado->mouseRow--;
    }
}

int testObjetivo(tEstado *estado) {
    int valido = 0;
    if(estado->robCol == N - 1 && estado->robRow == N - 1) {
        valido = 1;
    } else if(estado->mouseCol == N - 1 && estado->mouseRow == N - 1) {
        valido = -1;
    }
    return valido;
}

int iguales(tEstado *a, tEstado *b) {
    int iguales = 1, i, j;
    if (a->mouseCol != b->mouseCol || a->mouseRow != b->mouseRow || a->robCol != b->robCol || a->robRow != b->robRow) {
        iguales = 0;
    } else {
        while(iguales == 1 && i < N) {
            while(iguales == 1 && j < N) {
                if(a->celdas[i][j] != b->celdas[i][j]) {
                    iguales = 0;
                }
                j++;
            }
            j = 0;
            i++;
        }
    }
    return iguales;
}
