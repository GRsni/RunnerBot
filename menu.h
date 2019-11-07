#include "bot.h"

/*Selecciona el modo de creacion del estado inicial segun el selector
    Devuelve el estado creado*/
tEstado* eligeModoCrearEstado(int selector);

/*Menu principal de programa*/
void menuPrincipal();

/*Menu para la seleccion del estado inicial*/
tEstado* menuSeleccionEstado();

/*Menu para la seleccion del algoritmo de busqueda*/
int menuBusqueda();

/*Selecciona el tipo de busqueda a realizar segun el selector*/
void eligeAccionBusquedaSalir();

/*Menu para elegir las diferentes opciones de busqueda en profundidad*/
void menuBusquedaProfundidad();

/*Selecciona el tipo de busqueda en profundidad segun el selector*/
void eligeBusquedaProfundidad(int selector);

/*Menu para elegir las diferentes busquedas heuristicas*/
void menuBusquedaHeuristica();

/*Selecciona el tipo de busqueda heuristica segun el selector*/
void eligeBusquedaHeuristica(int selector);

/* Muestra el contenido del puzle. */
void dispEstado(tEstado *estado);

/*Muestra la matriz de estado de forma numerica*/
void dispEstadoNum(tEstado *estado);

/*Muestra la posicion del raton y del robot*/
void dispPosRobotRaton(tEstado *estado);

/* Muestra el nombre de cada operador: Arriba, Abajo, Izquierda, Derecha. */
void dispOperador(unsigned op);
