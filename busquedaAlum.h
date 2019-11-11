/*******************************************/
/* 		    BUSQUEDA.H                     */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#define ANCHURA 0
#define PROFUNDIDAD 1
#define PROF_ITER 1
#define PROF_LIM 0
#define GREEDY 0
#define ASTAR 1

#include "listaia.h"
#include "bot.h"

int busquedaACiegas(int selector);
int busquedaProfundidadLimitada(int prof);

int busquedaProfundidaIterativa();
int busquedaHeuristica(int selector);
int busquedaLocal();
int busquedaHaz(int haz);

void Ordenar(Lista C, int tipo);
void OrdenarGreedy(Lista C);
void OrdenarAStar(Lista C);
int esRepetido(tEstado *estado, Lista C);
int distObjetivo(tEstado *estado);

