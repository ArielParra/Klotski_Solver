#ifndef Menus_h
#define Menus_h

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

class Menus{
  private:
    int pantalla=1;
    int seleccion=0;
    int numNivel=-1;
    bool salir = false;
    /*logo y graficos*/
    inline void logouaa();
    inline void ArielParra();
    inline void flecha_derecha();
    inline void flecha_izquierda();
  public:

unsigned int validarEntradaInt();

/*Pantallas del menu*/
void primer_pantalla();
void segunda_pantalla();
void tercer_pantalla();

/*Pantallas incluidas en la tercer pantalla*/
unsigned int elegirNivel();
void pantalla_Tabla(unsigned int numNivel);
void pantalla_Solucion(unsigned int numNivel);

/*funcion principal de menus*/
void principal();

/*getters y setters*/
int getPantalla(){return this->pantalla;}
int getSeleccion(){return this->seleccion;}
};

#endif // Menus_h