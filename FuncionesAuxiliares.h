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

string stringDireccion(Direccion dir){
  //convierte la direccion a string para imprimir en pantalla
 switch(dir){
    case ARRIBA:    return "↑ ARRIBA   "; break;
    case ABAJO:     return "↓ ABAJO    "; break;
    case IZQUIERDA: return "← IZQUIERDA"; break;
    case DERECHA:   return "→ DERECHA  "; break;
    default:        return "";            break; //para evitar el warning: control reaches end of non-void function [-Wreturn-type]
  }
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

void mensajeCentrado(const string mensaje){
  clrscr();
  gotoxy(getmaxX()/2 - mensaje.size()/2, getmaxY()/2);
  cout<<mensaje;fflush(stdout);
  recuadro();
  delay(2000);
  clrscr();
}

unsigned int validarEntradaInt(){
//funcion auxiliar para validar entrada de numeros
bool esValido = true; //bandera para validar entrada en el do while
string entrada; //entrada del usuario
  do {
    const string mensaje = "Ingrese el número N para el archivo nivel_N.txt: ";
    const string lineaDeCaptura = "-----";
    gotoxy(getmaxX()/2 - mensaje.size()/2, getmaxY()/2);
    cout<<FG_MAGENTA<<mensaje<<RESET_COLOR;
    gotoxy(getmaxX()/2 + mensaje.size()/2 , getmaxY()/2 + 1);
    cout<<lineaDeCaptura;
    esValido = true;
    fflush(stdin);
    entrada.clear(); //se limpia la entrada
      //para capturar incluso espacios
      gotoxy(getmaxX()/2 + mensaje.size()/2 , getmaxY()/2);
      reset_shell_mode();//salirse de ncurses para usar getline
        cout<<CURSOR_ON;
        getline(cin,entrada);
        cout<<CURSOR_OFF;
      reset_prog_mode();//regresar a ncurses
      string error; 
      //solo se dio enter = error
      if(entrada.length()<1){
        esValido=false;
        error="Error: Ingrese algún número";
      }
      for (char c : entrada) {
        if (!isdigit(c)) {//si no es un numero
          esValido = false;
          error="Error: Ingrese unicamente números";
          break; // Si se encuentra un carácter no numérico, salir del bucle
        }
      }
      if (esValido && entrada.size()>lineaDeCaptura.size()) {//si no es un numero
        esValido = false;
        error="Error: Ingrese maximo "+ to_string(lineaDeCaptura.size()) + " digitos";
      }
      if(error.size()>0){ // debido al stoul
      cout<<FG_RED;
      mensajeCentrado(error);
      }
      
    }while (!esValido);//mientras no sea valido se pide por mas numeros
    
return stoul(entrada);//se convierte de string a numero
}



#endif //FuncionesAuxiliares_h