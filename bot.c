#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bot.h"
#include "Utility.h"

tEstado *crearEstado(int celdas[N][N]) {
    tEstado *estado=(tEstado *)malloc(sizeof(tEstado));
    int i, j;
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            int valor=celdas[i][j];
            if(celdas[i][j]==ROBOT) {
                estado->robotX=i;
                estado->robotY=j;
                valor=VACIO;
            } else if(celdas[i][j]==RATON) {
                estado->mouseX=i;
                estado->mouseY=j;
                valor=VACIO;
            }
            estado->celdas[i][j]=valor;
        }
    }
    return estado;
}

tEstado* introducirEstado() {
    int i, j, valido=1, robotIn=0, ratonIn=0;
    int celdas[N][N];

    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
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
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            printf("%d", celdas[i][j]);
        }
        printf("\n");
    }
    return crearEstado(celdas);

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

tEstado* eligeOpcionCrearEstado() {
    char eleccion;
    int opcion=N;
    printf("Quieres crear un estado desde cero o elegir uno de los existentes?[s]i/[n]o: ");
    scanf("%c", &eleccion);
    if(eleccion=='s') {
        opcion=0;
    }
    return eligeEstado(opcion);
}

tEstado* eligeEstado(int n) {
    tEstado* estado;
    switch(n) {
    case 2:
        estado=estadoInicial2();
        break;
    case 3:
        estado=estadoInicial3();
        break;
    case 4:
        estado= estadoInicial4();
        break;
    case 5:
        estado= estadoInicial5();
        break;
    default:
        estado= introducirEstado();
        break;
    }
    return estado;
}

tEstado* estadoObjetivo() {
    tEstado *objetivo = eligeEstado(N);

    objetivo->celdas[objetivo->robotX][objetivo->robotY]==VACIO;
    objetivo->robotX=N-1;
    objetivo->robotY=N-1;
    objetivo->celdas[N-1][N-1]==ROBOT;

    dispEstado(objetivo);

    return eligeEstado(N);
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
    return valido;
}

void dispEstado(tEstado *estado) {
    int i, j;
    printf("Estado actual:\n");
    printGridLine(N);
    for(i=0; i<N; i++) {
        printf("|");
        for(j=0; j<N; j++) {
            char valor=' ';
//            printf("Valor: %d", estado->celdas[i][j]);
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
        printGridLine(N);
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
