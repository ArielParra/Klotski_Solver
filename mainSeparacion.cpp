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

  cout << "Ingrese el número N para el archivo nivel_N.txt: ";
  unsigned int N=validarEntradaInt();
  Nivel nivel(N);
  if(!nivel.cargarNivel()){
      cout << "Error: No se pudo abrir el archivo " << nivel.getNombreArchivo() << endl;
  }else{
    cout<< "Nombre del Nivel: "<< nivel.getNombreNivel() <<endl;
    cout << "Tabla del archivo" << nivel.getNombreArchivo() << endl;
    cout << "getAnchoNivel " << nivel.getAnchoNivel() << endl;
    cout << "getAltoNivel " << nivel.getAltoNivel() << endl;
    vector<string> matriz3 = nivel.getTableroNivel();
    Tabla tablaSolucion = Tabla(matriz3);
    
    //tablaSolucion.printTabla(); // debug

    //tablaSolucion.imprimirBloques(); // debug
      
    Klotski klotski = (tablaSolucion);

    unsigned int solucion = klotski.solucionador();

      if(solucion==0){
        cout<<"no hay solucion";
      }else{
        cout << "Solucion Encontrada\n";
        klotski.printMovimientosSolucion(solucion);//pasos para la solucion
      }//if solucion
  }//nivel cargado
}

int main(){
  setANSI(); //para mostrar colores ANSI en windows  
  setUTF8();//para mostrar caracteres UTF8 en Windows
  elegirNivel();
  return 0;
}
