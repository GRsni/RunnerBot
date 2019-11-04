#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bot.h"
#include "Utility.h"


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
//    printf("%d, %d, %d\n", rRow == 0, estado->celdas[rRow - 1][rCol] == PARED, rCol == mCol - 1 && rRow == mRow);
    return !(rRow == 0 || estado->celdas[rRow - 1][rCol] == PARED || (rCol == mCol - 1 && rRow == mRow));
}

int compruebaAbajo(tEstado *estado) {
    int rCol = estado->robCol, rRow = estado->robRow, mCol = estado->mouseCol, mRow = estado->mouseRow;
//    printf("%d, %d, %d\n", rRow == N - 1, estado->celdas[rRow + 1][rCol] == PARED, rCol == mCol - 1 && rRow == mRow - 2);
    return !(rRow == N - 1 || estado->celdas[rRow + 1][rCol] == PARED || (rCol == mCol - 1 && rRow == mRow - 2));
}

int compruebaIzquierda(tEstado *estado) {
    int rCol = estado->robCol, rRow = estado->robRow, mCol = estado->mouseCol, mRow = estado->mouseRow;
//    printf("%d, %d, %d\n", rCol == 0, estado->celdas[rRow][rCol - 1] == PARED, rCol == mCol + 2 && rRow == mRow + 1);
    return !(rCol == 0 || estado->celdas[rRow][rCol - 1] == PARED || (rCol == mCol + 2 && rRow == mRow + 1));
}

int compruebaDerecha(tEstado *estado) {
    int rCol = estado->robCol, rRow = estado->robRow, mCol = estado->mouseCol, mRow = estado->mouseRow;
//    printf("%d, %d, %d\n", rCol == N - 1, estado->celdas[rRow][rCol + 1] == PARED, rCol == mCol && rRow == mRow + 1);
    return !(rCol == N - 1 || estado->celdas[rRow][rCol + 1] == PARED || (rCol == mCol && rRow == mRow + 1));
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
    dispEstado(nuevo);
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
