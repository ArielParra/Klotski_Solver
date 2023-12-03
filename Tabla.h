#pragma once //para que no de problemas de compilacion por inclusion multiple
#ifndef Tabla_h
#define Tabla_h

#include "compatibilidad.h"

#include "TiposDeDatos.h"
#include "Bloque.cpp"

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <unordered_map> //hash map std
using std::unordered_map; 

#include <iostream>
using std::cout;
using std::cin;


class Klotski; //para friend

class Tabla {

  private:
  Bloque bloques[LIMITE_DE_UNSIGNED_CHAR]={};//si sobra tiempo buscare una mejor alternativa
  // tableroDeJuego es la representación actualizada del estado del juego, y se utiliza para realizar operaciones
  // y comprobaciones durante el juego
  // y no se ocupa string ya que no se ocupa modificar el tablero en sus dimensiones
  vector<vector<char>> tableroDeJuego;

  // baseDeltablero es una copia de seguridad que almacena el estado original del tablero antes de 
  // realizar movimientos para que pueda ser restaurado en caso de que se necesite realizar un retroceso 
  // durante la búsqueda de soluciones
  vector<vector<char>> baseDeltablero;

  // esta clase es amiga de la clase Klotski para que pueda acceder a los miembros de datos privados de la clase
  friend class Klotski;

  public:

    Tabla();
    Tabla(vector<string>& matriz);
    void imprimirBloques();
    Bloque* getBloques();
    unsigned int getAltoTablero() const;
    unsigned int getAnchoTablero() const;
    void printTabla() const;
    bool bloquePuedeMorverse(Direccion dir, char IDdelBloque);
    void moverBloque(Direccion dir, char IDdelBloque);
    bool juegoGanado();

};// Clase Tabla


#endif //Tabla_h