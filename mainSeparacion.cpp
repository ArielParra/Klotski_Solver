#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "Nivel.cpp"
//#define DEBUG_LINUX //debug para imprimir en Klotski solucionador

#include "Klotski.cpp"

/* 
// Implicitos dentro de Klotski.cpp
// si se incluyen da el error de: error: redefinition of...
#include "compatibilidad.h"
#include "TiposDeDatos.h"
#include "FuncionesAuxiliares.h"
#include "Bloque.cpp"
#include "Tabla.cpp"
*/

void elegirNivel(){


bool nivelCargado=false;
  do{
  unsigned int N=validarEntradaInt();
  Nivel nivel(N);
  if(!nivel.cargarNivel()){
    const string errorArchivo="Error: No se pudo abrir : '" + nivel.getNombreArchivo() +"'";
    gotoxy(getmaxX()/2 - errorArchivo.size()/2, getmaxY()/2 + 1);
    cout<<FG_RED<<errorArchivo<<RESET_COLOR;fflush(stdout);
    delay(2000);
    clrscr();
  }else{
    nivelCargado=true;
    /*cout<< "Nombre del Nivel: "<< nivel.getNombreNivel() <<endl;
    cout << "Tabla del archivo" << nivel.getNombreArchivo() << endl;
    cout << "getAnchoNivel " << nivel.getAnchoNivel() << endl;
    cout << "getAltoNivel " << nivel.getAltoNivel() << endl;*/
    vector<string> matriz3 = nivel.getTableroNivel();
    Tabla tablaSolucion = Tabla(matriz3);
    
    //tablaSolucion.imprimirBloques();

    Klotski klotski = (tablaSolucion);
    unsigned int solucion = klotski.solucionador();
    string mensajeSolucion;
      clrscr();
      if(solucion==0){
        gotoxy(getmaxX()/2 - 15/2 ,getmaxY()/2 );
        mensajeSolucion="No Existe Solucion!";
        gotoxy(getmaxX()/2 - mensajeSolucion.size()/2, getmaxY()/2 );
        cout<<FG_RED<<mensajeSolucion<<RESET_COLOR;fflush(stdout);
        cout <<FG_RED;recuadro();
        delay(2000);
        clrscr();
      }else{
        mensajeSolucion="Solucion Encontrada!";
        gotoxy(getmaxX()/2 - mensajeSolucion.size()/2, getmaxY()/2 );
        cout<<FG_GREEN<<mensajeSolucion<<RESET_COLOR;fflush(stdout);
        cout <<FG_GREEN;recuadro();
        delay(2000);
        clrscr();
        klotski.printMovimientosSolucion(solucion,nivel.getNombreNivel());//pasos para la solucion
      }
    }//nivel cargado
  }while(!nivelCargado);
}

int main(){
  //setANSI(); //para mostrar colores ANSI en windows  
  //setUTF8();//para mostrar caracteres UTF8 en Windows
  startCompat();//incluidos setANSI() y setUTF8()
  elegirNivel();
  endCompat();
  return 0;
}
