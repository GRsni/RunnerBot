#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bot.h"
#include "nodo.h"
#include "listaia.h"
#include "busquedaAlum.h"
#include "menu.h"

extern tEstado *estadoInic;
extern int heuristica;

void dispCamino(tNodo *nodo) {
    if (nodo->padre == NULL) {
        printf("\n\nINICIO DE SOLUCION:\n");
        dispEstado(nodo->estado);
    } else {
        dispCamino(nodo->padre);
        dispOperador(nodo->operador);
        dispEstado(nodo->estado);
        printf("\n");
    }
}


void dispSolucion(tNodo *nodo) {
    dispCamino(nodo);
    printf("Profundidad=%d\n", nodo->profundidad);
    printf("Coste=%d\n", nodo->costeCamino);
}


/* Crea el nodo raíz. */
tNodo *nodoInicial() {
    tNodo *nodoInicial = (tNodo *) malloc(sizeof(tNodo));

    nodoInicial->estado = estadoInic;
    nodoInicial->padre = NULL;
    nodoInicial->costeCamino = 0;
    nodoInicial->profundidad = 0;
    nodoInicial->valHeuristica = calculaHeuristica(estadoInic);//heuristica distancia robot
    return nodoInicial;
}


/* Expande un nodo. */
Lista expandir(tNodo *nodo) {
    unsigned op;
    Lista sucesores = CrearLista(MAXI);
    for (op = 1; op <= NUM_OPERADORES; op++) {
        if (esValido(op, nodo->estado)) {
            tNodo *nuevo = (tNodo *) malloc(sizeof(tNodo));
            tEstado *s = (tEstado *) malloc(sizeof(tEstado));
            s = aplicaOperador(op, nodo->estado);
            nuevo = (tNodo *) malloc(sizeof(tNodo));
            nuevo->estado = s;
            nuevo->padre = nodo;
            nuevo->operador = op;
            nuevo->costeCamino = nodo->costeCamino + coste(op, nodo->estado);
            nuevo->valHeuristica = calculaHeuristica(s);
            nuevo->profundidad = nodo->profundidad + 1;
            if (!ListaLlena(sucesores)) {
                InsertarUltimo((void *) nuevo, sucesores);
            }
        }
    }
    return sucesores;
}


int busquedaACiegas(int selector) {
    int objetivo = 0, contador = 0, continua = 1;

    tNodo *Actual = (tNodo*) malloc(sizeof(tNodo));
    tNodo *Inicial = nodoInicial();

    Lista Abiertos = (Lista) CrearLista(MAXI);
    Lista Cerrados = (Lista) CrearLista(MAXI);
    Lista NoValidos = (Lista) CrearLista(MAXI);
    Lista Sucesores;

    InsertarUltimo((void *) Inicial, Abiertos);

    while (!ListaVacia(Abiertos) && objetivo < 1 && continua) {
        contador++;

        Actual = (void *) ExtraerPrimero(Abiertos);
        EliminarPrimero(Abiertos);

        if(!esRepetido(Actual->estado, Cerrados)) {
            objetivo = testObjetivo(Actual->estado);
            if (objetivo == 0) {
                Sucesores = expandir(Actual);
                if(selector == PROFUNDIDAD) {
                    Abiertos = Concatenar(Sucesores, Abiertos);
                } else if(selector == ANCHURA) {
                    Abiertos = Concatenar(Abiertos, Sucesores);
                }
            } else if(objetivo == -1) {
                InsertarUltimo((void* )Actual, NoValidos);
            }
        }
        InsertarUltimo((void *)Actual, Cerrados);
    }
    if(ListaVacia(Abiertos) || objetivo == -1) {
        if(!ListaVacia(NoValidos)) {
            Actual = (void *)ExtraerPrimero(NoValidos);
            dispCamino(Actual);
        }
        printf("--------------------SOLUCION NO ENCONTRADA------------------------------\n");
    } else if(objetivo == 1) {
        dispSolucion(Actual);
        printf("----------------------SOLUCION ENCONTRADA-------------------------------\n");
        printf("Numero de nodos visitados: %d, Abiertos: %d, Cerrados: %d\n", contador, Abiertos->Nelem, Cerrados->Nelem);
    }
    destruirListasUsadas(Abiertos, Cerrados, Sucesores, NoValidos);
    return objetivo;
}

int busquedaProfundidadLimitada(int prof) {
    int objetivo = 0, contador = 0, enRango = 1;

    tNodo *Actual = (tNodo*) malloc(sizeof(tNodo));
    tNodo *Inicial = nodoInicial();

    Lista Abiertos = (Lista) CrearLista(MAXI);
    Lista Cerrados = (Lista) CrearLista(MAXI);
    Lista NoValidos = (Lista) CrearLista(MAXI);
    Lista Sucesores;

    InsertarUltimo((void *) Inicial, Abiertos);

    while (!ListaVacia(Abiertos) && objetivo < 1 ) {
        contador++;

        Actual = (void *) ExtraerPrimero(Abiertos);
        EliminarPrimero(Abiertos);
//        dispCamino(Actual);

        enRango = nodoNoSuperaProfundidad(Actual->profundidad, prof);
        if(enRango) {
            objetivo = testObjetivo(Actual->estado);
            if (objetivo == 0) {
                Sucesores = expandir(Actual);
                Abiertos = Concatenar(Sucesores, Abiertos);
            } else if(objetivo == -1) {
                InsertarUltimo((void* )Actual, NoValidos);
            }
            InsertarUltimo((void *)Actual, Cerrados);
        }

//        system("pause");
    }

    if(objetivo == 1) {
        dispSolucion(Actual);
        printf("----------------------SOLUCION ENCONTRADA-------------------------------\n");
        printf("Numero de nodos visitados: %d, Abiertos: %d, Cerrados: %d\n", contador, Abiertos->Nelem, Cerrados->Nelem);
    } else if(ListaVacia(Abiertos) || objetivo == -1) {
        if(!ListaVacia(NoValidos)) {
            Actual = (void *)ExtraerPrimero(NoValidos);
            dispCamino(Actual);
        }
        printf("--------------------SOLUCION NO ENCONTRADA------------------------------\n");
    }
    destruirListasUsadas(Abiertos, Cerrados, Sucesores, NoValidos);
    return objetivo;
}

int nodoNoSuperaProfundidad(int profNodo, int prof) {
    return profNodo <= prof;
}

int busquedaProfundidaIterativa() {
    int prof = 1, objetivo;
    do {
        objetivo = busquedaProfundidadLimitada(prof);
        prof++;
    } while(objetivo != 1 && prof < 100);
    if(prof < 100) {
        printf("-----------------SOLUCION ENCONTRADA EN %d ITERACIONES-----------------\n", prof);
    } else {
        printf("---------------SOLUCION NO ENCONTRADA EN 100 ITERACIONES---------------\n");
    }
    return objetivo;
}

int busquedaHeuristica(int selector) {
    int objetivo = 0, contador = 0;

    tNodo *Actual = (tNodo*) malloc(sizeof(tNodo));
    tNodo *Inicial = nodoInicial();

    Lista Abiertos = (Lista) CrearLista(MAXI);
    Lista Sucesores, Cerrados = (Lista) CrearLista(MAXI);
    Lista NoValidos = (Lista) CrearLista(MAXI);

    InsertarUltimo((void *) Inicial, Abiertos);

    while (!ListaVacia(Abiertos) && !objetivo) {
        contador++;
        Actual = (void *) ExtraerPrimero(Abiertos);

        EliminarPrimero(Abiertos);
        if(!esRepetido(Actual->estado, Cerrados)) {
            objetivo = testObjetivo(Actual->estado);
            if (objetivo == 0) {
                Sucesores = expandir(Actual);
                Abiertos = Concatenar(Sucesores, Abiertos);
                Ordenar(Abiertos, selector);
            } else if(objetivo == -1) {
                InsertarUltimo((void* )Actual, NoValidos);
            }

            InsertarUltimo((void *)Actual, Cerrados);
        }
    }

    if(objetivo == 1) {
        dispSolucion(Actual);
        printf("----------------------SOLUCION ENCONTRADA-------------------------------\n");
        printf("Numero de nodos visitados: %d, Abiertos: %d, Cerrados: %d\n", contador, Abiertos->Nelem, Cerrados->Nelem);
    } else if(ListaVacia(Abiertos) || objetivo == -1) {
        if(!ListaVacia(NoValidos)) {
            Actual = (void *)ExtraerPrimero(NoValidos);
            dispCamino(Actual);
        }
        printf("--------------------SOLUCION NO ENCONTRADA------------------------------\n");
    }
    destruirListasUsadas(Abiertos, Cerrados, Sucesores, NoValidos);
    return objetivo;

}

int busquedaLocal() {
    return busquedaHaz(1);
}

int busquedaHaz(int haz) {
    int objetivo = 0, contador = 0,  i = 0;
    heuristica = DISTROB;

    tNodo *Actual = (tNodo*) malloc(sizeof(tNodo));
    tNodo *Inicial = nodoInicial();

    Lista Abiertos = (Lista) CrearLista(MAXI);
    Lista Cerrados = (Lista) CrearLista(MAXI);
    Lista NoValidos = (Lista) CrearLista(MAXI);
    Lista Sucesores;
    Lista Siguientes = (Lista) CrearLista(MAXI);

    //EXPANDIR LOS PRIMEROS NODOS SUCESORES Y SELECCIONAR LOS 'HAZ' MEJORES//
    InsertarUltimo((void *)Inicial, Cerrados);
    Sucesores = expandir(Inicial);
    Ordenar(Sucesores, GREEDY);

    i = 0;
    while(!ListaLlena(Abiertos) && !ListaVacia(Sucesores)) {
        Actual = (void *)ExtraerPrimero(Sucesores);
        if(i < haz) {
            InsertarUltimo((void *)Actual, Abiertos);
        } else {
            InsertarUltimo((void *)Actual, Cerrados);
        }
        EliminarPrimero(Sucesores);
        i++;
    }


    //N MEJORES SUCESORES ELEGIDOS//
    while(objetivo < 1 && !ListaVacia(Abiertos)) { //ITERAR HASTA OBJETIVO O NO MAS SUCESORES


        while(!ListaVacia(Abiertos)) {    //PARA CADA ABIERTO
            Actual = (void *)ExtraerPrimero(Abiertos);
            contador++;
            EliminarPrimero(Abiertos);
            if(!esRepetido(Actual->estado, Cerrados)) { //COMPROBAR SI OBJETIVO
                objetivo = testObjetivo(Actual->estado);
                if(objetivo == -1) {
                    InsertarUltimo((void *)Actual, NoValidos);
                } else if(objetivo == 0) { //SI OBJETIVO == 0, SACAR LOS SUCESORES
                    Sucesores = expandir(Actual);
                    //AGRUPARLOS TODOS LOS SUCESORES
                    Siguientes = ConcatenarValidos(Siguientes, Sucesores, Actual);
                }
                InsertarUltimo((void *)Actual, Cerrados);
            }
        }
        if(objetivo != 1) { //ORDENAR TODOS LOS NODOS SUCESORES
            Ordenar(Siguientes, GREEDY);
            //OBTENER LOS N SIGUIENTES
            i = 0;
            while(!ListaVacia(Siguientes)) {
                Actual = (void *)ExtraerPrimero(Siguientes);
                if(i < haz) {
                    InsertarUltimo((void *)Actual, Abiertos);
                    dispEstado(Actual->estado);
                } else {
                    InsertarUltimo((void *)Actual, Cerrados);
                }
                EliminarPrimero(Siguientes);
                i++;
            }
        }
    }

    if(objetivo == 1) {
        dispSolucion(Actual);
        printf("----------------------SOLUCION ENCONTRADA-------------------------------\n");
        printf("Numero de nodos visitados: %d, Abiertos: %d, Cerrados: %d\n", contador, Abiertos->Nelem, Cerrados->Nelem);
    } else if(ListaVacia(Abiertos) || objetivo == -1) {
        if(!ListaVacia(NoValidos)) {
            Actual = (void *)ExtraerPrimero(NoValidos);
            dispCamino(Actual);
        }
        printf("--------------------SOLUCION NO ENCONTRADA------------------------------\n");
    }
    destruirListasUsadas(Abiertos, Cerrados, Sucesores, NoValidos);
    DestruirLista(Siguientes);
    return objetivo;
}

Lista ConcatenarValidos(Lista L1, Lista L2, tNodo *Actual) {
    tNodo *e = (void *) malloc(sizeof(tNodo));

    while (!ListaVacia(L2) && (!ListaLlena(L1))) {
        e = (void*) ExtraerPrimero(L2);
        if(sucesorValido(Actual, e)) {
            InsertarUltimo((void *)e, L1);
        }
        EliminarPrimero(L2);
    }
    return L1;

}


int sucesorValido(tNodo * actual, tNodo * sig) {
    return sig->valHeuristica < actual->valHeuristica;
}


int esRepetido(tEstado * actual, Lista C) {
    int i = 0, repetido = 0;

    while(i < C->Nelem && !repetido) {
        tNodo *nodo_cerrado = (void *)ExtraerElem(C, i);
        if(iguales(nodo_cerrado->estado, actual)) {
            repetido = 1;
        }
        i++;
    }
    return repetido;
}

int calculaHeuristica(tEstado * estado) {
    int val = 0;
    switch (heuristica) {
    case DISTROB:
        val = distObjetivo(estado);
        break;
    case DISTROBRAT:
        val = (distObjetivo(estado) + distRaton(estado));
        break;
    default:
        val = distObjetivo(estado);
    }
    return val;
}

int distObjetivo(tEstado * estado) {
    int distX = (N - 1) - estado->robCol;
    int distY = (N - 1) - estado->robRow;
    return distX + distY;
}

int distRaton(tEstado * estado) {
    return (estado->mouseCol + estado->mouseRow) / 2;
}

void Ordenar(Lista C, int selector) {
    int i, ordenado, tam = C->Nelem;
    int valActual, valSig;
    tElemento *e = (tElemento* )malloc(sizeof(tElemento));
    do {
        ordenado = 1;
        for(i = 0; i < tam - 1; i++) {
            tNodo *nodo_i = (void *)ExtraerElem(C, i);
            tNodo *nodo_next = (void *)ExtraerElem(C, i + 1);
            if(selector == GREEDY) {
                valActual = nodo_i->valHeuristica;
                valSig = nodo_next->valHeuristica;
            } else if(selector == ASTAR) {
                valActual = nodo_i->costeCamino + nodo_i->valHeuristica;
                valSig = nodo_next->costeCamino + nodo_next->valHeuristica;
            }
            if(valActual > valSig) {
                ordenado = 0;
                e = C->elementos[i];
                C->elementos[i] = C->elementos[i + 1];
                C->elementos[i + 1] = e;

            }
        }
        tam--;
    } while(!ordenado);
}

void destruirListasUsadas(Lista L1, Lista L2, Lista L3, Lista L4) {
    DestruirLista(L1);
    DestruirLista(L2);
    DestruirLista(L3);
    DestruirLista(L4);
}


