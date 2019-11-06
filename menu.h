#include "bot.h"

/*Crea el estado con el tamaño correcto segun en valor de la constante N*/
tEstado* eligeModoCrearEstado(int manual);

/*Crea el estado inicial a partir de entrada por teclado. Pide los datos de las paredes, y posicion del raton y robot*/
tEstado* introducirEstado();

/*Crea el estado te tamaño correcto de manera aleatoria*/
tEstado* eligeEstadoAleatorio();

/*Situa el robot en una posicion aleatorioa del mapa*/
void eligePosRobotAleatoria(int tam, int celdas[tam][tam]);

/*Situa al raton en una posicion aleatoria del mapa*/
void eligePosRatonAleatoria(int tam, int celdas[tam][tam]);

/*Coloca las paredes de manera aleatoria en el mapa*/
void colocaParedesAleatorias(int tam, int celdas[tam][tam]);

/*Menu principal de programa*/
void menuPrincipal();

/*Menu para la seleccion del estado inicial*/
tEstado* menuSeleccionEstado();

/*Menu para la seleccion del algoritmo de busqueda*/
void menuBusqueda();

/* Muestra el contenido del puzle. */
void dispEstado(tEstado *estado);

/*Muestra la matriz de estado de forma numerica*/
void dispEstadoNum(tEstado *estado);

/*Muestra la posicion del raton y del robot*/
void dispPosRobotRaton(tEstado *estado);

/* Muestra el nombre de cada operador: Arriba, Abajo, Izquierda, Derecha. */
void dispOperador(unsigned op);
