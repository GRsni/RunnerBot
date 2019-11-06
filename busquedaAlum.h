/*******************************************/
/* 		    BUSQUEDA.H                     */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include "listaia.h"
#include "bot.h"

int busquedaACiegas(int selector);
int busquedaProfundidadLimitada();
int busquedaHeuristica();
void OrdenarGreedy(Lista C);
void OrdenarAStar(Lista C);
int esRepetido(tEstado *estado, Lista C);
int distObjetivo(tEstado *estado);

