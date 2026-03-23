#ifndef FUNCIONES_H
#define FUNCIONES_H
/*prototipado*/
char confirmacion_de_menu();
char seleccion_tamaño_de_la_matriz();
char letra_minuscula(char dato);
int **crear_matriz(int ancho,int largo);
void imprimir_matriz(int **matriz,int ancho,int largo);
int numero_random();
int **inicial_pieza(int &fila,int &columna);
bool juego(int **matriz,int ancho, int alto);
char movimiento_de_ficha();
void borrar_matriz(int **matriz, int largo);
void limpiar_matriz(int **matriz, int alto, int ancho);
void limpiar_movimiento( int **matriz,int **pieza, int alto, int ancho, int alto_actual, int ancho_actual);
void imprimir_movimiento(int **matriz,int **pieza, int alto, int ancho, int alto_actual, int ancho_actual);
bool colision(int **matriz,int **pieza, int alto, int ancho, int alto_actual, int ancho_actual, int alto_matriz, int ancho_matriz, char movimiento);
bool condicion_derrota(int **matriz, int altura_matriz, int ancho_matriz);
void eliminacion_de_linea(int **matriz, int altura_matriz, int ancho_matriz);
int **giro_de_pieza(int **pieza,int ancho_pieza,int alto_pieza);
/*prototipado*/
#endif // FUNCIONES_H
