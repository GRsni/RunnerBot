#include "bot.h"

/*Pregunta al usuario si desea introducir un estado, o usar una ya creado*/
tEstado* eligeOpcionCrearEstado();

/*Crea el estado inicial a partir de entrada por teclado. Pide los datos de las paredes, y posicion del raton y robot*/
tEstado* introducirEstado();

/*Crea el estado con el tamaño correcto segun en valor de la constante N*/
tEstado* eligeEstado();

/* Muestra el contenido del puzle. */
void dispEstado(tEstado *estado);

/*Muestra la matriz de estado de forma numerica*/
void dispEstadoNum(tEstado *estado);

/*Muestra la posicion del raton y del robot*/
void dispPosRobotRaton(tEstado *estado);

/* Muestra el nombre de cada operador: Arriba, Abajo, Izquierda, Derecha. */
void dispOperador(unsigned op);
