#include "Bloque.h"
//public:
  Bloque::Bloque(){this->id=0;} //constructor vacio
  
  Bloque::Bloque(unsigned int id, unsigned int x, unsigned int y, unsigned int ancho, unsigned int alto, bool esPiezaSingular, unsigned int reduccion) : 
    id(id), x(x), y(y), ancho(ancho), alto(alto), esPiezaSingular(esPiezaSingular), reduccion(reduccion){
  }//constructor

/*funciones get*/
  unsigned int Bloque::getAncho() const{
    return this->ancho;
  }

  unsigned int Bloque::getAlto() const{
    return this->alto;
  }

  unsigned int Bloque::getID() const{
    return this->id;
  }

  unsigned int Bloque::getReduccion() const {
    return this->reduccion;
  }

  unsigned int Bloque::getX() const{
    return this->x;
  }

  unsigned int Bloque::getY() const{
    return this->y;
  }

  bool Bloque::puedeMoverse(char pieza){

    //verifica si la pieza singular puede moverse por la puerta
    if(this->esPiezaSingular && pieza == PIEZA_PUERTA) {return true; }

    //si se puede mover sobre la pieza objetivo
    if(pieza == PIEZA_OBJETIVO){return true;}

    //por defecto solo puede moverse a una pieza vacia
    return pieza == PIEZA_VACIA;
  }

  void Bloque::mover(Direccion dir){
  //mueve el bloque en la direccion especificada modificando sus posiciones privadas x e y
    switch(dir){
      case ARRIBA:    this->y--; break;  
      case ABAJO:     this->y++; break;
      case IZQUIERDA: this->x--; break;
      case DERECHA:   this->x++; break;
    }
  }
  
