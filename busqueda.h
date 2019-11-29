#define ANCHURA 0
#define PROFUNDIDAD 1
#define PROF_ITER 1
#define PROF_LIM 0
#define GREEDY 0
#define ASTAR 1

#define DISTROB 1
#define DISTROBRAT 2

#include "listaia.h"
#include "bot.h"
#include "nodo.h"

/*Realiza una busqueda a ciegas, en anchura o profundidad*/
int busquedaACiegas(int selector);

/*Realiza una busqueda en profundidad limitada segun el parametro prof*/
int busquedaProfundidadLimitada(int prof);

/*Devuelve 1 si el nodo tiene una profundidad menor o igual a prof*/
int nodoNoSuperaProfundidad(int profNodo, int prof);

/*Realiza una busqueda en profundidad iterativa*/
int busquedaProfundidaIterativa();

/*Realiza una busqueda heuristica, voraz o A* segun el parametro selector*/
int busquedaHeuristica(int selector);

/*Realiza una busqueda local*/
int busquedaLocal();

/*Realiza una busqueda local en haz con numero de nodos abiertos igual a haz*/
int busquedaHaz(int haz);

/*Devuelve C1+C2 segun la condicion de validez de sucesor
-Precondiciones: C1 no vacia*/
Lista ConcatenarValidos(Lista C1, Lista C2, tNodo *actual);

/*Devuelve 1 si el sig es un sucesor valido(decreciente) de actual, 0 en otro caso*/
int sucesorValido(tNodo *actual, tNodo *sig);

/*Calcula el valor de heuristica del nodo segun el tipo elegido*/
int calculaHeuristica(tEstado *estado);

/*Ordena la lista C segun la busqueda heuristica a realizar, voraz o A* */
void Ordenar(Lista C, int tipo);

/*Devuelve 1 si el estado es un estado ya visitado en el arbol de soluciones*/
int esRepetido(tEstado *estado, Lista C);

/*Devuelve la distancia del robot al objetivo*/
int distObjetivo(tEstado *estado);

/*Devuelve la distancia del raton al objetivoç*/
int distRaton(tEstado *estado);

/*Destruye 4 listas(las listas utilizadas en las busquedas)*/
void destruirListasUsadas(Lista L1, Lista L2, Lista L3, Lista L4);
