#include "bot.h"

/*Selecciona el modo de creacion del estado inicial segun el selector
    Devuelve el estado creado*/
tEstado* eligeModoCrearEstado(int selector);

/*Menu principal de programa*/
void menuPrincipal();

/*Menu para la seleccion del estado inicial*/
tEstado* menuSeleccionEstado();

/*Muestra el menu de seleccion del funcion heuristica*/
int menuFuncionHeuristica();

/*Menu para la seleccion del algoritmo de busqueda*/
int menuBusqueda();

/*Selecciona el tipo de busqueda a realizar segun el selector*/
void eligeAccionBusquedaSalir();

/*Pide por teclado la profundidad maxima para la busqueda en profundidad limitada*/
int introduceProfMaxima();

/*Pide por teclado el tamaño del haz de busqueda*/
int introduceTamanoHaz();

/* Muestra el contenido del puzle. */
void dispEstado(tEstado *estado);

/*Muestra la matriz de estado de forma numerica*/
void dispEstadoNum(tEstado *estado);

/*Muestra la posicion del raton y del robot*/
void dispPosRobotRaton(tEstado *estado);

/* Muestra el nombre de cada operador: Arriba, Abajo, Izquierda, Derecha. */
void dispOperador(unsigned op);
