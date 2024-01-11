//#define DEBUG_LINUX //debug para imprimir en Klotski solucionador

#include "Menus.cpp"

/* 
// Implicitos dentro de menus.cpp
#include "maestro.cpp"
#include "alumno.cpp"
#include "persona.cpp"
#include "id.cpp"
#include "Nivel.cpp"
#include "Klotski.cpp"
// Implicitos dentro de Klotski.cpp
// si se incluyen da el error: redefinition of ...
#include "compatibilidad.h"
#include "TiposDeDatos.h"
#include "FuncionesAuxiliares.h"
#include "Bloque.cpp"
#include "Tabla.cpp"
*/

int main(){
  //srand(time(NULL));// resultados inconsistentes
  //para que el numero seudo aleatorio sea constante y de resultados consistentes
  //srand(0);// se cambio por  rotacion deterministica de 0 a 3
  //setANSI(); //para mostrar colores ANSI en windows  
  //setUTF8();//para mostrar caracteres UTF8 en Windows
  startCompat();//incluidos setANSI() y setUTF8(), inicializa el modo de ncurses en *NIX
  Menus menu;
  menu.principal();
  endCompat(); // termina el modo ncurses en *NIX
  return 0;
}
