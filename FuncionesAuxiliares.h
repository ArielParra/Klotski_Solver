#pragma once //para que no de problemas de compilacion por inclusion multiple
#ifndef FuncionesAuxiliares_h
#define FuncionesAuxiliares_h

#include "TiposDeDatos.h"
#include "compatibilidad.h"

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
      reset_shell_mode();cout<<CURSOR_ON;
      getline(cin,entrada);
      reset_prog_mode();cout<<CURSOR_OFF; 
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
    
return std::stoi(entrada);//se convierte a int
}

void recuadro(){
#if defined(_WIN32)
gotoxy(0,0);cout<<"█";
#endif
unsigned int x=getmaxX(),j=0;
unsigned int y=getmaxY(),i=0;

//lineas verticales
  while(i<=getmaxY()){
    gotoxy(x,y);cout<<"█";
    gotoxy(0,y--);cout<<"█";
    i++;
  }
//lineas horizontales
  y=getmaxY();
  while(j<=getmaxX()){
    gotoxy(x,y);cout<<"█";
    gotoxy(x--,0);cout<<"█";
    j++;
  }

cout<<RESET_COLOR;fflush(stdout);
}

#endif //FuncionesAuxiliares_h