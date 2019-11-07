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
        printf("\n\nInicio:\n");
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


/* Crea el nodo ra�z. */
tNodo *nodoInicial() {
    tNodo *nodoInicial = (tNodo *) malloc(sizeof(tNodo));
    tEstado *copia = (tEstado* )malloc(sizeof(tEstado));
    memcpy(copia, inicial, sizeof(tEstado));

    nodoInicial->estado = copia;
    nodoInicial->padre = NULL;
    nodoInicial->costeCamino = 0;
    nodoInicial->profundidad = 0;
    nodoInicial->valHeuristica = distObjetivo(copia);//heuristica distancia robot
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

    dispEstado(Inicial->estado);

    Lista Abiertos = (Lista) CrearLista(MAXI);
    Lista Sucesores, Cerrados = (Lista) CrearLista(MAXI);

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
            }
            InsertarUltimo((void *)Actual, Cerrados);
        }
//        system("pause");
    }
    if(objetivo == 1) {
        dispSolucion(Actual);
        printf("Numero de nodos visitados: %d, Abiertos: %d, Cerrados: %d\n", contador, Abiertos->Nelem, Cerrados->Nelem);
    } else if(objetivo == -1) {
        dispCamino(Actual);
        printf("Soluci�n no encontrada.\n");
    }
    system("pause");
    system("cls");
    return objetivo;
}

int busquedaProfundidadLimitada() {
    return 1;
}

int busquedaHeuristica() {
    int objetivo = 0, contador = 0;
    tNodo *Actual = (tNodo*) malloc(sizeof(tNodo));

    tNodo *Inicial = nodoInicial();
//    dispCamino(Inicial);
    //tEstado *Final=estadoObjetivo();

    Lista Abiertos = (Lista) CrearLista(MAXI);
    Lista Sucesores, Cerrados = (Lista) CrearLista(MAXI);

    InsertarUltimo((void *) Inicial, Abiertos);

    while (!ListaVacia(Abiertos) && !objetivo) {
        contador++;
        Actual = (void *) ExtraerPrimero(Abiertos);

        EliminarPrimero(Abiertos);
        if(!esRepetido(Actual->estado, Cerrados)) {
            objetivo = testObjetivo(Actual->estado);
            if (!objetivo) {
                Sucesores = expandir(Actual);
                Abiertos = Concatenar(Sucesores, Abiertos);

                OrdenarGreedy(Abiertos);
//                OrdenarAStar(Abiertos);
                int i;
                for(i = 0; i < Abiertos->Nelem; i++) {
                    tNodo *a = (void *)ExtraerElem(Abiertos, i);
                    printf("Coste abiertos: %d\n", a->costeCamino);
                }
            }

            InsertarUltimo((void *)Actual, Cerrados);
        }
        printf("Numero de nodos visitados: %d, Abiertos: %d, Cerrados: %d\n", contador, Abiertos->Nelem, Cerrados->Nelem);
//        system("pause");
    }
    dispSolucion(Actual);
    return objetivo;

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

void OrdenarGreedy(Lista C) {
    int i, ordenado, tam = C->Nelem;
    do {
        ordenado = 1;
        for(i = 0; i < tam - 1; i++) {
            tNodo *nodo_i = (void *)ExtraerElem(C, i);
            tNodo *nodo_next = (void *)ExtraerElem(C, i + 1);
            printf("Coste i: %d, Coste next: %d\n", nodo_i->costeCamino, nodo_next->costeCamino);
            if(nodo_i->costeCamino < nodo_next->costeCamino) {
                ordenado = 0;
                tElemento *a = C->elementos[i];
                tElemento *b = C->elementos[i + 1];
                IntercambiaElemento(a, b);
            }
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
                IntercambiaElemento(a, b);
            }
        }
        printf("\n");
        tam--;
    } while(!ordenado);
}


