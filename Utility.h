#include "bot.h"

/*Imprime una linea separatoria de la cuadricula*/
void printGridLine(int cols);

/*Imprime la celda bonita*/
void printIcon(char c);

/*Imprime mensaje de error al introducir la posicion del robot*/
void imprimeErrorPosRobot(int col, int row, int celdas[N][N]);

/*Rellena la matriz pasada por parametro con 0*/
void inicializaMatrizCero(int tam, int celdas[tam][tam]);

/*Imprime una matriz de enteros por pantalla*/
void imprimeMatriz(int tam, int celdas[tam][tam]);
