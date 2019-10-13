
#define ARRIBA 1
#define ABAJO 2
#define IZQUIERDA 3
#define DERECHA 4
#define NUM_OPERADORES 4
#define N 4
#define VACIO 0
#define PARED 1
#define ROBOT 2
#define RATON 3



#ifndef _tEstado_
#define _tEstado_
typedef struct {
    int celdas[N][N];
    int robotX, robotY, mouseX, mouseY;
    int tam;
} tEstado;

#endif

static int mapa_inicial2[2][2]= {
    {RATON, ROBOT},
    {PARED, VACIO}
};

static int mapa_inicial3[3][3]= {
    {RATON,VACIO,PARED},
    {PARED,VACIO,VACIO},
    {ROBOT,VACIO,VACIO}
};

static int mapa_inicial4[4][4]= {
    {VACIO, VACIO, VACIO, ROBOT},
    {VACIO, RATON, PARED, PARED},
    {PARED, VACIO, VACIO, VACIO},
    {VACIO, VACIO, PARED, PARED}
};

/* A partir de una configuración de fichas construye un estado válido para el problema
  de acuerdo al tipo de datos tEstado. */
tEstado* crearEstado(int celdas[N][N], int tam);

/*Crea el estado inicial a partir de entrada por teclado. Pide los datos de las paredes, y posicion del raton y robot*/
tEstado* introducirEstado();

/* Genera el estado inicial a partir de crearEstado y puzle_inicial. */
tEstado* estadoInicial2();

tEstado* estadoInicial3();

tEstado* estadoInicial4();

/* Devuelve el coste de aplicar el operador. */
int coste(unsigned op, tEstado *estado);

/* Muestra el contenido del puzle. */
void dispEstado(tEstado *estado);

/* Muestra el nombre de cada operador: Arriba, Abajo, Izquierda, Derecha. */
void dispOperador(unsigned op);

/*Selecciona el caracter a mostrar en pantalla segun el valor numerico */
char getCaracter(int num);

/* Genera el estado final a partir de crearEstado y el estado actual */
tEstado *estadoObjetivo();

/* Comprueba si es posible aplicar un operador a una configuración determinada para el puzle.
  Devuelve 1 si el movimiento es válido y 0 en otro caso. */
int esValido(unsigned op, tEstado* estado);

/* Aplica un operador a una configuración concreta del puzle.
  Devuelve la nueva configuración del tablero tras el movimiento. */
tEstado *aplicaOperador(unsigned op, tEstado *estado);

/* Devuelve 1 si dos estados son iguales y 0 en caso contrario. */
int iguales(tEstado *s, tEstado *t);

/* Devuelve 1 si un estado es igual al estado objetivo. */
int testObjetivo(tEstado *estado);
