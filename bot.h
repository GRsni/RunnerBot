#ifndef CONSTANTES
#define CONSTANTES

#define ARRIBA 1
#define ABAJO 2
#define IZQUIERDA 3
#define DERECHA 4
#define NUM_OPERADORES 4
#define N 5
#define VACIO 0
#define PARED 1
#define ROBOT 2
#define RATON 3
#define ROBOTC 254
#define RATONC -108
#define PAREDC -78

#if N==2
static int mapa_inicial[N][N] = {
    {RATON, ROBOT},
    {VACIO, VACIO}
};
#elif N==3
static int mapa_inicial[N][N] = {
    {VACIO, ROBOT, PARED},
    {VACIO, RATON, VACIO},
    {VACIO, VACIO, VACIO}
};
#elif N==4
static int mapa_inicial[N][N] = {
    {VACIO, VACIO, VACIO, VACIO},
    {VACIO, RATON, VACIO, VACIO},
    {PARED, VACIO, VACIO, ROBOT},
    {VACIO, VACIO, VACIO, VACIO}
};
#elif N==5
static int mapa_inicial[N][N] = {
    {VACIO, PARED, VACIO, VACIO, PARED},
    {VACIO, VACIO, PARED, PARED, VACIO},
    {PARED, VACIO, RATON, VACIO, VACIO},
    {VACIO, ROBOT, PARED, PARED, VACIO},
    {VACIO, VACIO, VACIO, VACIO, VACIO}
};

#endif // N

#endif // CONSTANTES

#ifndef _tEstado_
#define _tEstado_
typedef struct {
    int celdas[N][N];
    int robCol, robRow, mouseCol, mouseRow;
} tEstado;

#endif //_tEstado_

/* A partir de una configuración de fichas construye un estado válido para el problema
  de acuerdo al tipo de datos tEstado. */
tEstado* crearEstado(int celdas[N][N]);

/* Devuelve el coste de aplicar el operador. */
int coste(unsigned op, tEstado *estado);

/* Comprueba si es posible aplicar un operador a una configuración determinada para el puzle.
  Devuelve 1 si el movimiento es válido y 0 en otro caso. */
int esValido(unsigned op, tEstado* estado);

/*Comprueba las codiciones del operador ARRIBA*/
int compruebaArriba(tEstado *estado);

/*Comprueba las codiciones del operador ABAJO*/
int compruebaAbajo(tEstado *estado);

/*Comprueba las codiciones del operador IZQUIERDA*/
int compruebaIzquierda(tEstado *estado);

/*Comprueba las codiciones del operador DERECHA*/
int compruebaDerecha(tEstado *estado);

/* Aplica un operador a una configuración concreta del puzle.
  Devuelve la nueva configuración del tablero tras el movimiento. */
tEstado *aplicaOperador(unsigned op, tEstado *estado);

/*Modifica la posicion del raton segun el operador escogido*/
void mueveRaton(tEstado *estado, int direccion);

/*Funcion auxiliar, desplaza el raton hacia abajo derecha*/
void mueveRatonAbajoDerecha(tEstado *estado);

/*Funcion auxiliar, desplaza el raton hacia arriba izquierda*/
void mueveRatonArribaIzquierda(tEstado *estado);

/* Devuelve 1 si el robot ha llegado, -1 si el raton ha llegado, y  0 en otro caso */
int testObjetivo(tEstado *estado);

/*Devuelve 1 si el estado a es igual al estado b, devuelve 0 en otro caso*/
int iguales(tEstado *a, tEstado *b);
