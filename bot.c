#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bot.h"

tEstado *crearEstado(int celdas[N][N]) {
    tEstado *estado=(tEstado *)malloc(sizeof(tEstado));
    int i, j;

    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            estado->celdas[i][j]=celdas[i][j];
            if(celdas[i][j]==ROBOT) {
                estado->robotX=i;
                estado->robotY=j;
            } else if(celdas[i][j]==RATON) {
                estado->mouseX=i;
                estado->mouseY=j;
            }
        }
    }
    return estado;
}






void dispEstado(tEstado *estado) {
    int i, j;
    printf("Estado actual:\n_____\n|");
    for(i=0; i<N; i++) {
        printf("|");
        for(j=0; j<N; j++) {
            char valor=getCaracter(estado->celdas[i][j]);
            printf("%c |", valor);
        }
        printf("\n");
    }
    printf("Robot[%d, %d], Raton[%d, %d]\n", estado->robotX, estado->robotY, estado->mouseX, estado->mouseY);
}


char getCaracter(int num) {
    char caracter;
    switch(num) {
    case PARED:
        caracter=178;
        break;
    case ROBOT:
        caracter=219;
        break;
    case RATON:
        caracter=153;
        break;
    default:
        caracter=' ';
        break;
    }
    return caracter;
}

