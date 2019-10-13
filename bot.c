#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bot.h"
#include "Utility.h"

tEstado *crearEstado(int celdas[N][N], int tam) {
    tEstado *estado=(tEstado *)malloc(sizeof(tEstado));
    int i, j;
    estado->tam=tam;
    for(i=0; i<tam; i++) {
        for(j=0; j<tam; j++) {
            int valor=celdas[i][j];
            if(celdas[i][j]==ROBOT) {
                estado->robotX=i;
                estado->robotY=j;
                valor=1;
            } else if(celdas[i][j]==RATON) {
                estado->mouseX=i;
                estado->mouseY=j;
                valor=1;
            }
            estado->celdas[i][j]=valor;
        }
    }
    return estado;
}

tEstado* introducirEstado() {
    int casillas, i, j, valido=1, robotIn=0, ratonIn=0;
    printf("Introduce el numero de casillas: ");
    scanf("%d", &casillas);
    int celdas[casillas][casillas];

    for(i=0; i<casillas; i++) {
        for(j=0; j<casillas; j++) {
            do {
                printf("Elige que hay en la celda[%d, %d]:\nVACIO[0]|PARED[1]", i, j);
                if(!robotIn) {
                    printf("|ROBOT[2]");
                }
                if(!ratonIn) {
                    printf("|RATON[3]");
                }
                printf("\nRecuerda que solo puedes poner un robot y un raton.->\n");
                scanf("%d", &celdas[i][j]);
                if(celdas[i][j]==RATON) {
                    if(i==j) {
                        ratonIn=1;
                    } else {
                        printf("Error en la posicion del raton.\n");
                        valido=0;
                    }
                } else if(celdas[i][j]==ROBOT) {
                    robotIn=1;
                }
            } while(celdas[i][j]<VACIO||celdas[i][j]>RATON||!valido);
        }
    }
    for(i=0; i<casillas; i++) {
        for(j=0; j<casillas; j++) {
            printf("%d", celdas[i][j]);
        }
        printf("\n");
    }
    return crearEstado(celdas, casillas);

}

tEstado* estadoInicial2() {
    return crearEstado(&mapa_inicial2, 2);
}

tEstado* estadoInicial3() {
    return crearEstado(&mapa_inicial3, 3);
}

tEstado* estadoInicial4() {
    return crearEstado(&mapa_inicial4, 4);
}

tEstado* estadoObjetivo() {
//    tEstado objetivo=crearEstado()
}

int coste(unsigned op, tEstado *estado) {
    return 1;
}

int esValido(unsigned op, tEstado *estado) {
    int valido=1;
    switch(op) {
    case ARRIBA:
        if(estado->robotY==0||estado->celdas[estado->robotX][estado->robotY-1]==PARED)

            break;
    case ABAJO:

        break;
    case IZQUIERDA:

        break;
    case DERECHA:

        break;
    }
    return 1;
}

void dispEstado(tEstado *estado) {
    int i, j;
    printf("Estado actual:\n");
    printGridLine(estado->tam);
    for(i=0; i<estado->tam; i++) {
        printf("|");
        for(j=0; j<estado->tam; j++) {
            char valor=' ';
            printf("Valor: %d", estado->celdas[i][j]);
            if(i==estado->robotX&&j==estado->robotY) {
                valor=64;
            } else if(i==estado->mouseX&&j==estado->mouseY) {
                valor=153;
            } else if (estado->celdas[i][j]==PARED) {
                valor=178;
            }
            printf(" %c |", valor);
        }
        printf("\n");
        printGridLine(estado->tam);
    }

    printf("\nRobot[%d, %d], Raton[%d, %d]\n", estado->robotX, estado->robotY, estado->mouseX, estado->mouseY);
}

char getCaracter(int num) {
    char caracter;
    switch(num) {
    case PARED:
        caracter=178;
        break;
    default:
        caracter=' ';
        break;
    }
    return caracter;
}

void dispOperador(unsigned op) {
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
