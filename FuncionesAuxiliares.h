#pragma once //para que no de problemas de compilacion por inclusion multiple
#ifndef FuncionesAuxiliares_h
#define FuncionesAuxiliares_h

#include "TiposDeDatos.h"

#include <string>
using std::string; 
using std::getline;
using std::stoul;

#include <iostream>
using std::cout; 
using std::cin;
using std::endl;

string stringDireccion(Direccion dir){
  // funcion auxiliar que convierte la direccion a string para imprimir en pantalla
 switch(dir){
    case ARRIBA:    return "ARRIBA";    break;
    case ABAJO:     return "ABAJO";     break;
    case IZQUIERDA: return "IZQUIERDA"; break;
    case DERECHA:   return "DERECHA";   break;
    default:        return "";          break; //para evitar el warning: control reaches end of non-void function [-Wreturn-type]
  }
}


unsigned int validarEntradaInt(){
    //funcion auxiliar para validar entrada de numeros
    bool esValido = true; //bandera para validar entrada en el do while
    string entrada; //entrada del usuario
    do {
        esValido = true;
        entrada.clear(); //se limpia la entrada
        //para capturar incluso espacios
        getline(cin,entrada);
        //solo se dio enter = error
        if(entrada.length()<1){
            esValido=false;
            cout<<"Error: Ingrese un número"<<endl;
        }
        for (char c : entrada) {
            if (!isdigit(c)) {//si no es un numero
            esValido = false;
            cout << "Error: Ingresa solo números" << endl;
            break; // Si se encuentra un carácter no numérico, salir del bucle
            }
        }
        }while (!esValido);//mientras no sea valido se pide por mas numeros
    return stoul(entrada);//se convierte a unsigned long, es lo mismo que unsigned int
}


#endif //FuncionesAuxiliares_h