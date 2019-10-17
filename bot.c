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
    int i, j, rX, rY;
    int celdas[N][N];

    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            do {
                printf("Elige que hay en la celda[%d, %d]:\nVACIO[0]|PARED[1]: ", i, j);
                scanf("%d", &celdas[i][j]);
            } while(celdas[i][j]<VACIO||celdas[i][j]>PARED);
        }
    }
    do {
        printf("Introduce la fila del raton: ");
        scanf("%d", &rY);
        printf("Introduce la columna del raton: ");
        scanf("%d", &rX);
    } while(rX<0||rX>N-1||rY<0||rY>N-1);
    celdas[rX][rY]=RATON;

    do {
        printf("Introduce la fila del robot: ");
        scanf("%d", &rY);
        printf("Introduce la columna del robot: ");
        scanf("%d", &rX);
    } while(rX<0||rX>N-1||rY<0||rY>N-1);
    celdas[rX][rY]=ROBOT;

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

tEstado* eligeEstado(int opcion) {
    tEstado* estado;
    switch(opcion) {
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

int coste(unsigned op, tEstado *estado) {
    return 1;
}

int esValido(unsigned op, tEstado *estado) {
    int valido;
    //TODO: Solve problem with this shit
    switch(op) {
    case ARRIBA:
        valido=compruebaArriba(estado);
        break;
    case ABAJO:
        valido=compruebaAbajo(estado);
        break;
    case IZQUIERDA:
        valido=compruebaIzquierda(estado);
        break;
    case DERECHA:
        valido=compruebaIzquierda(estado);
        break;
    }
    return valido;
}

int compruebaArriba(tEstado *estado) {
    int rX=estado->robotX, rY=estado->robotY, mX=estado->mouseX, mY=estado->mouseY;
    return !(rY==0 ||estado->celdas[rX][rY-1]==PARED||(rX==mX-1&&rY==mY));
}

int compruebaAbajo(tEstado *estado) {
    int rX=estado->robotX, rY=estado->robotY, mX=estado->mouseX, mY=estado->mouseY;
    return !(rY==N-1||estado->celdas[rX][rY+1]==PARED||(rX==mX-1&&rY==mY-2));
}

int compruebaIzquierda(tEstado *estado) {
    int rX=estado->robotX, rY=estado->robotY, mX=estado->mouseX, mY=estado->mouseY;
    return !(rX==0||estado->celdas[rX][rY-1]==PARED||(rX==mX+2&&rY==mY+1));
}

int compruebaDerecha(tEstado *estado) {
    int rX=estado->robotX, rY=estado->robotY, mX=estado->mouseX, mY=estado->mouseY;
    return !(rY==N-1||estado->celdas[rX][rY+1]==PARED||(rX==mX&&rY==mY+1));
}

void dispEstado(tEstado *estado) {
    int i, j;
    printf("Estado actual:\n");
    printGridLine(N);
    for(i=0; i<N; i++) {
        printf("|");
        for(j=0; j<N; j++) {
            char c=' ';
            if(i==estado->robotX&&j==estado->robotY) {
                c=64;
            } else if(i==estado->mouseX&&j==estado->mouseY) {
                c=-103;
            } else if (estado->celdas[i][j]==PARED) {
                c=-78;
            }
            printBlock(c);
        }
        printf("\n");
        printGridLine(N);
    }
    dispEstadoNum(estado);
    dispPosRobotRaton(estado->robotX, estado->robotY, estado->mouseX, estado->mouseY);
}

void dispEstadoNum(tEstado *estado) {
    int i, j;
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            printf("%d", estado->celdas[i][j]);
        }
        printf("\n");
    }
}

void dispPosRobotRaton(int rX, int rY, int mX, int mY) {
    printf("Robot[%d, %d], Raton[%d, %d]\n", rX, rY, mX, mY);
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
