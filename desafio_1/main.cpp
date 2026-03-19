#include <iostream>
#include <random>
using namespace std;
/*prototipado*/
char confirmacion_de_menu();
char seleccion_tamaño_de_la_matriz();
char letra_minuscula(char dato);
int **crear_matriz(int ancho,int largo);
void imprimir_matriz(int **matriz,int ancho,int largo);
int numero_ramdom();
int **inicial_pieza(int &fila,int &columna);
bool juego(int **matriz,int ancho, int alto);
char movimiento_de_ficha();
void borrar_matriz(int **matriz, int largo);
bool colision();
void limpiar_matriz(int **matriz, int alto, int ancho);
void limpiar_movimiento( int **matriz,int **pieza, int alto, int ancho, int alto_actual, int ancho_actual);
/*prototipado*/
int main()
{
    unsigned short int ancho, numero_pieza;
    char dato_entrada_menu,tamaño_matriz;
    bool juego_iniciar(true), empezar_partida;
    do{
        cout << "elija una de las opciones para continuar\n1) iniciar juego\n2) salir\n";
        dato_entrada_menu = confirmacion_de_menu();
        if (dato_entrada_menu == '1'){
            bool seleccion_tamaño(true);
            bool empezar_partida(false);
            int **matriz;
            do{
            tamaño_matriz = seleccion_tamaño_de_la_matriz();
                if (tamaño_matriz == '1'){
                    ancho = 8;
                    matriz = crear_matriz(ancho,(ancho+4));
                    empezar_partida = true;
                    seleccion_tamaño = false;
                }
                else if (tamaño_matriz == '2'){
                    ancho = 16;
                    matriz = crear_matriz(ancho,(ancho+4));
                    empezar_partida = true;
                    seleccion_tamaño = false;
                }
                else if (tamaño_matriz == '3'){
                    ancho = 24;
                    matriz = crear_matriz(ancho,(ancho+4));
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
                empezar_partida=juego(matriz,ancho,ancho+4);
                borrar_matriz(matriz,ancho+4);
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

char confirmacion_de_menu(){
    char dato[150], dato_salida;
    cin >> dato;
    for (int i =0;i < (sizeof(dato)/sizeof(dato[0]));i++){
        if ( dato[i] == '1' || dato[i] == '2'){
            dato_salida = dato[i];
            break;
        }
    }
    cin.ignore(150, '\n');

    return dato_salida;
}
char seleccion_tamaño_de_la_matriz(){
    char resultado;
    bool dato_recolectado(false);
    char datos_posibles[4] = {'1','2','3','q'},dato[150];
    cout << "seleccione el tamaño del campo de juego\n1) 12x8\n2) 12x16\n3) 12x32\nq) salir\naclaracion el primer numero es el alto el segundo el ancho";
    cin >> dato;
    for (int i =0; i < (sizeof(dato)/sizeof(dato[0])) && dato_recolectado == false;i++){
        dato[i] = letra_minuscula(dato[i]);
        for (int j = 0;j < (sizeof(datos_posibles)/sizeof(datos_posibles[0]));j++){
            if (dato[i] == datos_posibles[j]){
                resultado = dato[i];
                dato_recolectado = true;
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
                // Filas normales: si el bit no coincide con 0, imprimimos bloque
                if ((mask) & matriz[i][j]){
                    cout << "0";
                } else {
                    cout << "#";
                }
            } else {
                // Primeras 4 filas: imprimimos solo si el bit está activo
                if ((mask) & matriz[i][j]){
                    cout << "0";
                } else {
                    cout << " ";
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
int numero_ramdom(){
    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dis(0,5);
    int numero = dis(gen);
    return numero;
}
bool juego(int **matriz,int ancho, int alto){
    bool juego(true);
    int pieza_fila;
    int pieza_columna;
    char movimiento;
    int **pieza_en_juego = inicial_pieza(pieza_fila,pieza_columna);
    int columna_actual = (ancho-pieza_columna)/2;
    int fila_actual(0);
    do{
        for(int i = 0; i < pieza_fila;i++){
            for(int j =0; j < pieza_columna; j++){
                if( pieza_en_juego[i][j] == 1){
                    matriz[i+fila_actual][j+columna_actual] = 1;
                }
            }
        }
        imprimir_matriz(matriz, ancho, alto);
        cout << "movimientos\n (a)izq (s)abj (d)der (w)girar (q)salir \n";
        movimiento = movimiento_de_ficha();
        if (movimiento == 'a'){
            if (columna_actual>0){
                limpiar_movimiento(matriz,pieza_en_juego,pieza_fila,pieza_columna,fila_actual,columna_actual);
                columna_actual--;
            }
        }
        else if (movimiento == 's'){
            if (fila_actual+pieza_fila<alto){
                limpiar_movimiento(matriz,pieza_en_juego,pieza_fila,pieza_columna,fila_actual,columna_actual);
                fila_actual++;
            }
        }
        else if (movimiento == 'd'){
            if (columna_actual+pieza_columna<ancho){
                limpiar_movimiento(matriz,pieza_en_juego,pieza_fila,pieza_columna,fila_actual,columna_actual);
                if (){

                }
                columna_actual++;
            }
        }
        else if (movimiento == 'w'){
            cout << "nada por el momento";
            limpiar_movimiento(matriz,pieza_en_juego,pieza_fila,pieza_columna,fila_actual,columna_actual);
        }
        else if (movimiento == 'q'){
            juego = false;
        }

    }
    while(juego == true);
    borrar_matriz(pieza_en_juego,pieza_fila);
    return juego;
}
int **inicial_pieza(int &fila,int &columna){
    int pieza = numero_ramdom();
    int **item;
    /*cuadrado*/
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
    /*palo*/
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
    /*T*/
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
    /*l*/
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
    /*J*/
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
    /*s*/
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
    return item;
}
char movimiento_de_ficha(){
    char lista_teclas[5] = {'a','s','d','w','q'};
    char movimiento[150], devolucion;
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
    cin.ignore(150, '\n');
    return devolucion;
}
bool colision(){
    bool colisor;
    return colisor;
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
