#include <iostream>
#include "funciones.h"
using namespace std;
/*prototipado*/
int main()
{
    int ancho;
    int alto = 16;
    char dato_entrada_menu,tamaño_matriz;
    bool juego_iniciar(true);
    do{
        cout << "elija una de las opciones para continuar \n1) iniciar juego \n2) salir\n";
        dato_entrada_menu = confirmacion_de_menu();
        if (dato_entrada_menu == '1'){
            bool seleccion_tamaño(true);
            bool empezar_partida(false);
            int **matriz;
            do{
            tamaño_matriz = seleccion_tamaño_de_la_matriz();
                if (tamaño_matriz == '1'){
                    ancho = 8;
                    matriz = crear_matriz(ancho,alto);
                    empezar_partida = true;
                    seleccion_tamaño = false;
                }
                else if (tamaño_matriz == '2'){
                    ancho = 16;
                    matriz = crear_matriz(ancho,alto);
                    empezar_partida = true;
                    seleccion_tamaño = false;
                }
                else if (tamaño_matriz == '3'){
                    ancho = 24;
                    matriz = crear_matriz(ancho,alto);
                    empezar_partida = true;
                    seleccion_tamaño = false;
                }
                else if (tamaño_matriz == 'q'){
                    seleccion_tamaño = false;
                    empezar_partida = false;
                }
            }
            while(seleccion_tamaño == true);
            while (empezar_partida == true){
                empezar_partida=juego(matriz,ancho,alto);
                borrar_matriz(matriz,alto);
            }
        }
        else if (dato_entrada_menu == '2'){
            cout << "se cerro el juego";
            break;
        }
    }
    while(juego_iniciar == true);
    return 0;
}

