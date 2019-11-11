/*******************************************/
/* 		    BUSQUEDA.C                     */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bot.h"
#include "nodo.h"
#include "listaia.h"
#include "busquedaAlum.h"
#include "menu.h"

extern tEstado *inicial;

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

    nodoInicial->estado = inicial;
    nodoInicial->padre = NULL;
    nodoInicial->costeCamino = 0;
    nodoInicial->profundidad = 0;
    nodoInicial->valHeuristica = distObjetivo(inicial);//heuristica distancia robot
    return nodoInicial;
}


/* Expande un nodo. */
Lista expandir(tNodo *nodo) {
    unsigned op;
    Lista sucesores = CrearLista(MAXI);
    // printf("\nLista de Sucesores de Actual: \n");
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
            nuevo->valHeuristica = distObjetivo(s);
            nuevo->profundidad = nodo->profundidad + 1;
            if (!ListaLlena(sucesores)) {
                InsertarUltimo((void *) nuevo, sucesores);
            }
        }
    }
    return sucesores;
}


int busquedaACiegas(int selector) {
    int objetivo = 0, contador = 0;
    tNodo *Actual = (tNodo*) malloc(sizeof(tNodo));

    tNodo *Inicial = nodoInicial();

    Lista Abiertos = (Lista) CrearLista(MAXI);
    Lista Cerrados = (Lista) CrearLista(MAXI);
    Lista NoValidos = (Lista) CrearLista(MAXI);
    Lista Sucesores;

    InsertarUltimo((void *) Inicial, Abiertos);

    while (!ListaVacia(Abiertos) && objetivo < 1) {
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
            InsertarUltimo((void *)Actual, Cerrados);
        }
//        system("pause");
    }
    if(ListaVacia(Abiertos) || objetivo == -1) {
        Actual = (void *)ExtraerPrimero(NoValidos);
        dispCamino(Actual);
        printf("--------------------SOLUCION NO ENCONTRADA------------------------------\n");
    } else if(objetivo == 1) {
        dispSolucion(Actual);
        printf("----------------------SOLUCION ENCONTRADA-------------------------------\n");
        printf("Numero de nodos visitados: %d, Abiertos: %d, Cerrados: %d\n", contador, Abiertos->Nelem, Cerrados->Nelem);
    }
    system("pause");
    system("cls");
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

    while (!ListaVacia(Abiertos) && objetivo < 1) {
        enRango = 1;
        contador++;
        Actual = (void *) ExtraerPrimero(Abiertos);

        if(Actual->costeCamino > prof) {
            enRango = 0;
        }

        EliminarPrimero(Abiertos);
        if(!esRepetido(Actual->estado, Cerrados) && enRango) {
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


    if(!enRango) {
        printf("------------SOLUCION NO ENCONTRADA EN LA PROFUNDIDAD LIMITE-------------\n");
    } else if(objetivo == 1) {
        dispSolucion(Actual);
        printf("-------------------------SOLUCION ENCONTRADA----------------------------\n");
        printf("Numero de nodos visitados: %d, Abiertos: %d, Cerrados: %d\n", contador, Abiertos->Nelem, Cerrados->Nelem);
    } else if(objetivo == -1) {
        Actual = (void *)ExtraerPrimero(NoValidos);
        dispCamino(Actual);
        printf("------------------------SOLUCION NO ENCONTRADA--------------------------\n");
    }
    system("pause");
    system("cls");
    return objetivo;
}

int busquedaProfundidaIterativa() {
    return 1;
}

int busquedaHeuristica(int selector) {
    int objetivo = 0, contador = 0;
    tNodo *Actual = (tNodo*) malloc(sizeof(tNodo));

    tNodo *Inicial = nodoInicial();
//    dispCamino(Inicial);
    //tEstado *Final=estadoObjetivo();

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
                int i;
                for(i = 0; i < Abiertos->Nelem; i++) {
                    tNodo *a = (void *)ExtraerElem(Abiertos, i);
                    printf("Coste abiertos: %d\n", a->costeCamino);
                }
            } else if(objetivo == -1) {
                InsertarUltimo((void* )Actual, NoValidos);
            }

            InsertarUltimo((void *)Actual, Cerrados);
        }
        printf("Numero de nodos visitados: %d, Abiertos: %d, Cerrados: %d\n", contador, Abiertos->Nelem, Cerrados->Nelem);
//        system("pause");
    }
    if(ListaVacia(Abiertos) || objetivo == -1) {
        Actual = (void *)ExtraerPrimero(NoValidos);
        dispCamino(Actual);
        printf("--------------------SOLUCION NO ENCONTRADA------------------------------\n");
    } else if(objetivo == 1) {
        dispSolucion(Actual);
        printf("----------------------SOLUCION ENCONTRADA-------------------------------\n");
        printf("Numero de nodos visitados: %d, Abiertos: %d, Cerrados: %d\n", contador, Abiertos->Nelem, Cerrados->Nelem);
    }
    system("pause");
    system("cls");
    return objetivo;

}

int busquedaLocal() {
    return 1;
}

int busquedaHaz(int haz) {
    return 1;
}

int esRepetido(tEstado *actual, Lista C) {
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

int distObjetivo(tEstado *estado) {
    int distX = (N - 1) - estado->robCol;
    int distY = (N - 1) - estado->robRow;
    return distX + distY;
}

int distRaton(tEstado *estado) {
    return estado->mouseCol + estado->mouseRow;
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
                valActual = nodo_i->costeCamino;
                valSig = nodo_next->costeCamino;
            } else if(selector == ASTAR) {
                valActual = nodo_i->costeCamino + nodo_i->valHeuristica;
                valSig = nodo_next->costeCamino + nodo_next->valHeuristica;
            }
            printf("Val i: %d, Val next: %d\n", valActual, valSig);
            if(valActual > valSig) {
                ordenado = 0;
                e = C->elementos[i];
                C->elementos[i] = C->elementos[i + 1];
                C->elementos[i + 1] = e;

            }
//            system("pause");
        }
        printf("\n");
        tam--;
    } while(!ordenado);
}

void OrdenarAStar(Lista C) {
    int i, ordenado, tam = C->Nelem;
    do {
        ordenado = 1;
        for(i = 0; i < tam - 1; i++) {
            tNodo *nodo_i = (void *)ExtraerElem(C, i);
            tNodo *nodo_next = (void *)ExtraerElem(C, i + 1);
            int valor_i = nodo_i->costeCamino + nodo_i->valHeuristica;
            int valor_next = nodo_next->costeCamino + nodo_next->valHeuristica;
            printf("Coste i: %d, Coste next: %d\n", nodo_i->costeCamino, nodo_next->costeCamino);
            if(valor_i > valor_next) {
                ordenado = 0;
                tElemento *a = C->elementos[i];
                tElemento *b = C->elementos[i + 1];
            }
        }
        printf("\n");
        tam--;
    } while(!ordenado);
}


