#define ROBOTC 254
#define RATONC -108
#define PAREDC -78

#include "bot.h"

/*Imprime una linea separatoria de la cuadricula*/
void imprimeLineaMatriz(int cols);

/*Imprime la celda bonita*/
void imprimeIcono(char c);

/*Imprime mensaje de error al introducir la posicion del robot*/
void imprimeErrorPosRobot(int col, int row, int celdas[N][N]);

/*Rellena la matriz pasada por parametro con 0*/
void inicializaMatrizCero(int tam, int celdas[tam][tam]);

/*Imprime una matriz de enteros por pantalla*/
void imprimeMatriz(int tam, int celdas[tam][tam]);

/*Devuelve 1 si el selector de haya fuera de rango, 0 en otro caso*/
int compruebaSelectorFueraDeRango(int selec, int inf, int sup);

/*Imprime un mensaje de error de selector fuera de rango*/
void imprimeSelectorFueraDeRango();
