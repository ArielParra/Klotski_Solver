#pragma once //para que no de problemas de compilacion por inclusion multiple
#ifndef Tipos_de_datos_h
#define Tipos_de_datos_h

#define LIMITE_DE_UNSIGNED_CHAR 255 // 8 bits sin signo

enum TipoDeSolucion {
  //Tipo de dato para saber en que estado de la solucion esta 
  SOLUCION_ENCONTRADA,
  EN_PROGRESO,
};

class Posicion{
  public:
  //Tipo de dato para saber en que posicion esta respecto al tablero de la solucion esta 
    unsigned int x, y;
    bool operator==(const Posicion& pos) const {//sobrecarga de asignacion de posicion
      return pos.x == this->x && pos.y == this->y;
    }
};

enum TipoDePieza : unsigned char{
  //los tipos de pieza del tablero del tipo char sin contar letras ASCII aun
  PIEZA_VACIA    = '&',
  PIEZA_PARED    = '#',
  PIEZA_SINGULAR = '*',
  PIEZA_PUERTA   = '-',
  PIEZA_OBJETIVO = '.',
};

enum Direccion{
  //las cuatro direcciones a mover las piezas
  ARRIBA,
  ABAJO,
  IZQUIERDA,
  DERECHA
};


class OrdenDeMovimiento{
  public: 
  
  //usado para guardar una direccion e id de un bloque, usada principalmente para solucion() y printMovimientosSolucion()
  Direccion dir;
  //originalmente id era char, pero se cambio a unsigned char para evitar segmentation fault
  unsigned char id;

  bool operator==(const OrdenDeMovimiento& orden) const {//sobrecarga de operador de igualdad booleana
    return (dir == orden.dir) && (id == orden.id);
  }

  bool operator!=(const OrdenDeMovimiento& orden) const {//sobrecarga de operador de inigualdad booleana
    return !(*this == orden);
  }

};

Direccion direccionOpuesta(Direccion dir){
  //para evitar movimientos innecesarios o redundantes al explorar posibles movimientos
  switch(dir){
    case ARRIBA:    return ABAJO;   break;
    case ABAJO:     return ARRIBA;  break;
    case IZQUIERDA: return DERECHA; break;
    case DERECHA:   return IZQUIERDA; break;
    default: return dir; break; // para evitar el warning: control reaches end of non-void function [-Wreturn-type]
  }
}

class Solucion{ //para klotski
  public:
  TipoDeSolucion estado;
  unsigned int profundidad;
  unsigned int ultimoHash;
  OrdenDeMovimiento movimiento;
};


#endif //Tipos_de_datos_h
