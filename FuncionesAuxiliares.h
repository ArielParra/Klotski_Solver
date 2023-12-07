#pragma once //para que no de problemas de compilacion por inclusion multiple
#ifndef FuncionesAuxiliares_h
#define FuncionesAuxiliares_h

#include "TiposDeDatos.h"
#include "compatibilidad.h"

#include <string>
using std::string; 
using std::getline;
using std::stoul;
using std::to_string;

#include <iostream>
using std::cout; 
using std::cin;
// convierte la direccion a string para imprimir en pantalla
inline string stringDireccion(Direccion dir){
 switch(dir){
    case ARRIBA:    return "↑ ARRIBA   "; break;
    case ABAJO:     return "↓ ABAJO    "; break;
    case IZQUIERDA: return "← IZQUIERDA"; break;
    case DERECHA:   return "→ DERECHA  "; break;
    default:        return "";            break; //para evitar el warning: control reaches end of non-void function [-Wreturn-type]
  }
}

inline void recuadro(){
#if defined(_WIN32)
gotoxy(0,0);cout<<"█";
#endif
unsigned int x=getmaxX(),j=0;
unsigned int y=getmaxY(),i=0;

//lineas verticales
  while(i<=getmaxY()){
    gotoxy(x,y);cout<<"█";
    gotoxy(0,y--);cout<<"█";
    fflush(stdout);
    i++;
  }
//lineas horizontales
  y=getmaxY();
  while(j<=getmaxX()){
    gotoxy(x,y);cout<<"█";
    gotoxy(x--,0);cout<<"█";
    fflush(stdout);
    j++;
  }
fflush(stdout);
cout<<RESET_COLOR;
}

inline void mensajeCentrado(const string mensaje){
  clrscr();
  //centra el texto en la pantalla
  gotoxy(getmaxX()/2 - mensaje.size()/2, getmaxY()/2);
  cout<<mensaje;fflush(stdout);
  recuadro();
  //espera 2.5 segundos para continuar
  delay(2500);
  clrscr();
}

#endif //FuncionesAuxiliares_h