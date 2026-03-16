#include <iostream>
#include <random>
using namespace std;

char confirmacion_de_menu();
char seleccion_tamaño_de_la_matriz();
char letra_minuscula(char dato);
int **crear_matriz(int ancho,int largo);
void imprimir_matriz(int **matriz,int ancho,int largo);
int numero_ramdom();
int main()
{
    unsigned short int ancho, numero_pieza;
    char dato_entrada_menu,tamaño_matriz;
    bool juego_iniciar(true), empezar_partida;
    do{
        cout << "elija una de las opciones para continuar\n1) iniciar juego/n2) salir\n";
        dato_entrada_menu = confirmacion_de_menu();
        if (dato_entrada_menu == '1'){
            bool seleccion_tamaño(true);
            int **matriz;
            do{
            tamaño_matriz = seleccion_tamaño_de_la_matriz();
                if (tamaño_matriz == '1'){
                    ancho = 8;
                    int **matriz = crear_matriz(ancho,(ancho+4));
                    empezar_partida = true;
                }
                else if (tamaño_matriz == '2'){
                    ancho = 16;
                    int **matriz = crear_matriz(ancho,(ancho+4));
                    empezar_partida = true;
                }
                else if (tamaño_matriz == '3'){
                    ancho = 24;
                    int **matriz = crear_matriz(ancho,(ancho+4));
                    empezar_partida = true;
                }
                else if (tamaño_matriz == 'q'){
                    seleccion_tamaño = false;
                    empezar_partida = false;
                }
            }
            while(seleccion_tamaño == true);
            while (empezar_partida == true){
                imprimir_matriz(matriz, ancho, ancho+4);
                numero_pieza = numero_ramdom();
            }
        }
        else if (dato_entrada_menu == '2'){
            cout << "se cerro el juego";
            break;
        }
    }
    while(juego_iniciar == true);
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
    return dato_salida;
}
char seleccion_tamaño_de_la_matriz(){
    char resultado = '0';
    bool seleccion_tamaño(true),dato_recolectado(false);
    char datos_posibles[4] = {'1','2','3','q'},dato[150];
    cout << "seleccione el tamaño del campo de juego\n1) 12x8\n2) 12x16\n3)12x32\naclaracion el el primer numero es el alto el segundo el ancho\n";
    cin >> dato;
    for (int i =0;i < (sizeof(dato)/sizeof(dato[0])) && dato_recolectado == false;i++){
        dato[i] = letra_minuscula(dato[i]);
        for (int j = 0;i < (sizeof(datos_posibles)/sizeof(datos_posibles[0]));j++){
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
void imprimir_matriz(int **matriz,int ancho,int largo){
    int mask = 1;
    for (int i = 0;i < largo; i++ ){
        for (int j = 0; j < ancho; j ++){
            if (i > 3){
                if (((mask << j)) ^ matriz[i][j]){
                    cout << "#";
                }
                else {
                    cout << "[]";
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
    uniform_int_distribution<int> dis(1,5);
    int numero = dis(gen);
    return numero;
}
int pieza
char manipulacion_pieza
int colisiones
