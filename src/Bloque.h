#pragma once //para que no de problemas de compilacion por inclusion multiple
#ifndef Bloque_h
#define Bloque_h

#include "TiposDeDatos.h"

class Bloque { 

private:
  // la posicion del bloque en el tablero del juego
  unsigned int x, y;
  // el ancho y alto del bloque
  unsigned int ancho, alto;
  // esPiezaSingular es una bandera que indica si el bloque es la pieza singular
  bool esPiezaSingular;
  // id es la identificación única de cada bloque en el tablero del juego
  // por ejemplo letras ASCII y los otros caracteres
  char id; 
  // reduccion asigna un valor unico a cada combinación de ancho y alto de un bloque específico
  unsigned int reduccion;
  
public:

  Bloque(); //constructor vacio
  
  Bloque(unsigned int id, unsigned int x, unsigned int y, unsigned int ancho, unsigned int alto, bool esPiezaSingular, unsigned int reduccion);

/*funciones get*/
  unsigned int getAncho() const;

  unsigned int getAlto() const;

  unsigned int getID() const;

  unsigned int getReduccion() const;

  unsigned int getX() const;

  unsigned int getY() const;

  bool puedeMoverse(char pieza);

  void mover(Direccion dir);
  
};//clase Bloque

#endif //Bloque_h