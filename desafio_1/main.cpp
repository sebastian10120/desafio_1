#include <iostream>
using namespace std;

char confirmacion_de_menu();
char seleccion_tamaño_de_la_matriz();
char letra_minuscula(char dato);
int main()
{
    short int tamaño;
    char dato_entrada_menu,tamaño_matriz;
    bool juego_iniciar = true;
    bool tamaño_iniciar = true;
    do{
        cout << "elija una de las opciones para continuar\n1) iniciar juego/n2) salir\n";
        dato_entrada_menu = confirmacion_de_menu();
        if (dato_entrada_menu == '1'){
            bool seleccion_tamaño(true);
            do{
            tamaño_matriz = seleccion_tamaño_de_la_matriz();
                if (tamaño_matriz == '1'){
                    tamaño = 8;
                }
                else if (tamaño_matriz == '2'){
                    tamaño = 16;
                }
                else if (tamaño_matriz == '3'){
                    tamaño = 24;
                }
                else if (tamaño_matriz == 'q'){
                    seleccion_tamaño = false;
                }
            }
            while(seleccion_tamaño == true);
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
int imprimir_matriz(int tamaño){
}
