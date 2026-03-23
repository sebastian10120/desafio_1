#include "funciones.h"
#include <iostream>
#include <random>
using namespace std;
char confirmacion_de_menu(){
    char dato[50], dato_salida = '0';
    cin >> dato;
    for (int i =0;i < (sizeof(dato)/sizeof(dato[0]));i++){
        if ( dato[i] == '1' || dato[i] == '2'){
            dato_salida = dato[i];
            break;
        }
    }
    cin.ignore(50, '\n');

    return dato_salida;
}
char seleccion_tamaño_de_la_matriz(){
    char resultado = '0';
    bool dato_recolectado(false);
    char datos_posibles[4] = {'1','2','3','q'},dato[50];
    cout << "seleccione el tamano del campo de juego\n1) 16x8\n2) 16x16\n3) 16x24\nq) salir\naclaracion el primer numero es el alto el segundo el ancho";
    cin >> dato;
    for (int i =0; i < dato[i]!='\0' && dato_recolectado == false;i++){
        dato[i] = letra_minuscula(dato[i]);
        for (int j = 0;j < (sizeof(datos_posibles)/sizeof(datos_posibles[0]));j++){
            if (dato[i] == datos_posibles[j]){
                resultado = dato[i];
                dato_recolectado = true;
                break;
            }
        }
    }
    return resultado;
}
char letra_minuscula(char dato){
    if (65 <= dato && 90>= dato){
        dato = dato+32;
    }
    return dato;
}
void imprimir_matriz(int **matriz, int ancho, int largo){
    int mask = 1;
    for (int i = 0; i < largo; i++){
        for (int j = 0; j < ancho; j++){
            if (i > 3){
                if ((mask) & matriz[i][j]){
                    cout << "[0]";
                } else {
                    cout << " 0 ";
                }
            }
            else {
                if ((mask) & matriz[i][j]){
                    cout << "[0]";
                } else {
                    cout << "   ";
                }
            }
        }
        cout << endl;
    }
}
int **crear_matriz(int ancho,int largo){
    int **matriz = new int*[largo];
    for(int i = 0; i < largo; i++){
        matriz[i] = new int[ancho]();
    }
    return matriz;
}
bool juego(int **matriz,int ancho, int alto){
    bool juego(true);
    do{
        bool cambio_pieza = true;
        int pieza_fila, pieza_columna, giro_fila;
        int **pieza_en_juego = inicial_pieza(pieza_fila,pieza_columna);
        int columna_actual = (ancho - pieza_columna) / 2;
        int fila_actual = 0;
        char movimiento = '0';
        while(cambio_pieza == true){
            imprimir_movimiento(matriz,pieza_en_juego,pieza_fila,pieza_columna,fila_actual,columna_actual);
            imprimir_matriz(matriz, ancho, alto);
            cout << "movimientos\n (a)izq (s)abj (d)der (w)girar (q)salir \n";
            movimiento = movimiento_de_ficha();
            if (movimiento == 'a'){
                if (columna_actual>0){
                    limpiar_movimiento(matriz,pieza_en_juego,pieza_fila,pieza_columna,fila_actual,columna_actual);
                    columna_actual--;
                    if(colision(matriz,pieza_en_juego,pieza_fila,pieza_columna,fila_actual,columna_actual, alto, ancho, movimiento) == false){
                        columna_actual++;
                        imprimir_movimiento(matriz,pieza_en_juego,pieza_fila,pieza_columna,fila_actual,columna_actual);
                    }
                    if (columna_actual < 0){
                        columna_actual++;
                    }
                }
            }
            else if (movimiento == 's'){
                if (fila_actual+pieza_fila<=alto){
                    limpiar_movimiento(matriz,pieza_en_juego,pieza_fila,pieza_columna,fila_actual,columna_actual);
                    fila_actual++;
                    if(colision(matriz,pieza_en_juego,pieza_fila,pieza_columna,fila_actual,columna_actual, alto, ancho, movimiento) == false){
                        fila_actual--;
                        imprimir_movimiento(matriz,pieza_en_juego,pieza_fila,pieza_columna,fila_actual,columna_actual);
                        cambio_pieza = false;
                    }
                }
            }
            else if (movimiento == 'd'){
                if (columna_actual+pieza_columna<ancho){
                    limpiar_movimiento(matriz,pieza_en_juego,pieza_fila,pieza_columna,fila_actual,columna_actual);
                    columna_actual++;
                    if(colision(matriz,pieza_en_juego,pieza_fila,pieza_columna,fila_actual,columna_actual, alto, ancho, movimiento) == false){
                        columna_actual--;
                        imprimir_movimiento(matriz,pieza_en_juego,pieza_fila,pieza_columna,fila_actual,columna_actual);
                    }
                    if((columna_actual+pieza_columna > ancho)){
                        columna_actual--;
                    }
                }
            }
            else if (movimiento == 'w'){
                limpiar_movimiento(matriz,pieza_en_juego,pieza_fila,pieza_columna,fila_actual,columna_actual);
                pieza_en_juego = giro_de_pieza(pieza_en_juego,pieza_columna,pieza_fila);
                giro_fila = pieza_columna;
                pieza_columna = pieza_fila;
                pieza_fila = giro_fila;
                if (columna_actual + pieza_columna > ancho) {
                    columna_actual = ancho - pieza_columna;
                }
                if (columna_actual < 0) {
                    columna_actual = 0;
                }
                if (fila_actual + pieza_fila > alto) {
                    int exceso = (fila_actual + pieza_fila) - alto;
                    fila_actual -= exceso;
                }
                if(colision(matriz,pieza_en_juego,pieza_fila,pieza_columna,fila_actual,columna_actual, alto, ancho, movimiento) == false){
                    for (int i = 2; i >= 0; i--){
                        pieza_en_juego = giro_de_pieza(pieza_en_juego,pieza_columna,pieza_fila);
                        giro_fila = pieza_columna;
                        pieza_columna = pieza_fila;
                        pieza_fila = giro_fila;
                    }
                }
            }
            else if (movimiento == 'q'){
                juego = false;
                cambio_pieza=false;
            }
        }
        borrar_matriz(pieza_en_juego,pieza_fila);
        eliminacion_de_linea(matriz,alto,ancho);
        if (condicion_derrota(matriz, alto, ancho) == true && movimiento != 'q'){
            juego = false;
            cout << "PERDISTE\n\n\n";
        }
    }
    while(juego == true);

    return juego;
}
int numero_random(){
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dis(0,6);
    int numero = dis(gen);
    return numero;
}
int **inicial_pieza(int &fila,int &columna){
    int pieza = numero_random();
    int **item;
    if (pieza == 0){
        fila =  2;
        columna = 2;
        item = new int* [fila];
        for (int i = 0; i <fila; i++){
            item[i] = new int[columna]();
        }
        item[0][0]=1;
        item[0][1]=1;
        item[1][0]=1;
        item[1][1]=1;
    }
    else if (pieza == 1){
        fila = 4;
        columna = 1;
        item = new int*[fila];
        for (int i = 0; i < fila; i++){
            item[i] = new int[columna]();
        }
        item[0][0]=1;
        item[1][0]=1;
        item[2][0]=1;
        item[3][0]=1;
    }
    else if(pieza == 2){
        fila = 2;
        columna = 3;
        item = new int* [fila];
        for (int i = 0; i < fila; i++){
            item[i] = new int[columna]();
        }
        item[0][0]=1;
        item[0][1]=1;
        item[0][2]=1;
        item[1][1]=1;
    }
    else if(pieza == 3){
        fila = 3;
        columna = 2;
        item = new int* [fila];
        for (int i = 0; i < fila; i++){
            item[i] = new int[columna]();
        }
        item[0][0] = 1;
        item[1][0] = 1;
        item[2][0] = 1;
        item[2][1] = 1;
    }
    else if(pieza == 4){
        fila = 3;
        columna = 2;
        item = new int* [fila];
        for (int i = 0; i < fila; i++){
            item[i] = new int[columna]();
        }
        item[0][1] = 1;
        item[1][1] = 1;
        item[2][0] = 1;
        item[2][1] = 1;
    }
    else if(pieza == 5){
        fila = 2;
        columna = 3;
        item = new int* [fila];
        for (int i = 0; i < fila; i++){
            item[i] = new int[columna]();
        }
        item[0][1] = 1;
        item[0][2] = 1;
        item[1][0] = 1;
        item[1][1] = 1;
    }
    else if(pieza == 6){
        fila = 2;
        columna = 3;
        item = new int* [fila];
        for (int i = 0; i < fila; i++){
            item[i] = new int[columna]();
        }
        item[0][0] = 1;
        item[0][1] = 1;
        item[1][1] = 1;
        item[1][2] = 1;
    }
    return item;
}
char movimiento_de_ficha(){
    char lista_teclas[5] = {'a','s','d','w','q'};
    char movimiento[50], devolucion ='0';
    bool movimiento_dato(false);
    cin >> movimiento;
    for (int i = 0; i < sizeof(movimiento)/sizeof(movimiento[0]);i++){
        movimiento[i]=letra_minuscula(movimiento[i]);
        for (int j = 0; j < sizeof(lista_teclas)/sizeof(lista_teclas[0]) && movimiento_dato == false;j++){
            if (movimiento[i] == lista_teclas[j]){
                devolucion = lista_teclas[j];
                movimiento_dato = true;
            }
        }
    }
    cin.ignore(50, '\n');
    return devolucion;
}
void borrar_matriz(int **matriz, int largo){
    for(int i = 0; i < largo; i++){
        delete[] matriz[i];
    }
    delete[] matriz;
}
void limpiar_movimiento( int **matriz,int **pieza, int alto, int ancho, int alto_actual, int ancho_actual){
    for(int i = 0; i < alto;i++){
        for(int j =0; j < ancho; j++){
            if( pieza[i][j] == 1){
                matriz[i+alto_actual][j+ancho_actual] = 0;
            }
        }
    }
}
void imprimir_movimiento(int **matriz,int **pieza, int alto, int ancho, int alto_actual, int ancho_actual){
    for(int i = 0; i < alto;i++){
        for(int j =0; j < ancho; j++){
            if( pieza[i][j] == 1){
                matriz[i+alto_actual][j+ancho_actual] = 1;
            }
        }
    }
}
void eliminacion_de_linea(int **matriz, int altura_matriz, int ancho_matriz){
    int mask = 1;
    for (int i = altura_matriz-1; i >= 0;i--){
        int  contador = 0;
        for (int j = ancho_matriz-1; j >= 0;j--){
            if (mask & matriz[i][j]){
                contador++;
            }
        }
        if (contador == ancho_matriz){
            for(int filas_arriba = i; filas_arriba>0;filas_arriba--){
                for(int j = 0; j < ancho_matriz; j++){
                    matriz [filas_arriba][j] = matriz[filas_arriba-1][j];
                }
            }
            i++;
            for(int j = 0; j < ancho_matriz; j++){
                matriz[0][j] = 0;
            }
        }

    }
}

bool condicion_derrota(int **matriz, int altura_matriz, int ancho_matriz){
    int contador = 0, mask = 1;
    for(int fila_vacia = 0; fila_vacia <= 3 && contador == 0;fila_vacia++){
        for (int j = ancho_matriz-1; j >= 0;j--){
            if (mask & matriz[fila_vacia][j]){
                contador++;
                break;
            }
        }
    }
    if(contador > 0){
        return true;
    }
    else{
        return false;
    }
}
int **giro_de_pieza(int **pieza,int ancho_pieza,int alto_pieza){
    int **pieza_giro = new int *[ancho_pieza];
    for (int i = 0; i < ancho_pieza;i++){
        pieza_giro[i] = new int[alto_pieza]();
    }
    for (int a = 0; a < alto_pieza;a++){
        for (int b = 0; b < ancho_pieza; b++){
            pieza_giro[b][alto_pieza-1-a] = pieza[a][b];
        }
    }
    borrar_matriz(pieza,alto_pieza);
    return pieza_giro;
}
bool colision(int **matriz,int **pieza, int alto, int ancho, int alto_actual, int ancho_actual, int alto_matriz, int ancho_matriz, char movimiento){
    for(int i = 0; i < alto;i++){
        for(int j =0; j < ancho; j++){
            if( pieza[i][j] == 1){
                if(movimiento == 's'){
                    if( i+alto_actual == alto_matriz|| matriz[alto_actual+i][ancho_actual+j] == 1){
                        return false;
                    }
                }

                if(movimiento == 'a'){
                    if(matriz[alto_actual+i][ancho_actual+j] == 1){
                        return false;
                    }
                }

                if(movimiento == 'd'){
                    if( matriz[alto_actual+i][ancho_actual+j] == 1){
                        return false;
                    }
                }
                if (movimiento == 'w'){
                    if (matriz[alto_actual+i][ancho_actual+j] == 1){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
