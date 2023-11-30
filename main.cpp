#include <iostream>
using std::cout;
using std::cin;

#include "menus.cpp"
//#define DEBUG_LINUX //debug para imprimir en Klotski solucionador

/* 
// Implicitos dentro de menus.cpp
#include "Nivel.cpp"
#include "Klotski.cpp"
// Implicitos dentro de Klotski.cpp
// si se incluyen da el error de: error: redefinition of...
#include "compatibilidad.h"
#include "TiposDeDatos.h"
#include "FuncionesAuxiliares.h"
#include "Bloque.cpp"
#include "Tabla.cpp"
*/

int main(){
  //srand(time(NULL));//resultados inconsistentes
  //para que el numero seudo aleatorio sea constante y de resultados consistentes
  //srand(0);// se cambio por  rotacion deterministica de 0 a 3
  //setANSI(); //para mostrar colores ANSI en windows  
  //setUTF8();//para mostrar caracteres UTF8 en Windows
  startCompat();//incluidos setANSI() y setUTF8()
  menus();
  elegirNivel();
  endCompat();
  return 0;
}
