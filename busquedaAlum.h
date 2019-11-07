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
#define LOCAL 0
#define HAZ 1

#include "listaia.h"
#include "bot.h"

int busquedaACiegas(int selector);
int busquedaProfundidadLimitadaIterativa(int selector);
int busquedaHeuristica();
int busquedaLocal(int selector);
void OrdenarGreedy(Lista C);
void OrdenarAStar(Lista C);
int esRepetido(tEstado *estado, Lista C);
int distObjetivo(tEstado *estado);

