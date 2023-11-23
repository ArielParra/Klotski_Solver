#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>//pilas std

//para evitar using namespace std y controlar el uso de std
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::stack;

#define COLORS
#define PRINT

//#define SLEEP 0
#ifdef COLORS
#include "rlutil.h" //revisar esta mamada
#endif

enum TipoDeSolucion {
  SOLUCION_ENCONTRADA,
  EN_PROGRESO,
};

struct Posicion{
  unsigned int x, y;

  bool operator==(const Posicion& other) const {
    return other.x == x && other.y == y;
  }
/**/
     size_t hash() const {
        std::hash<int> hasher;
        return hasher(x) ^ hasher(y);
    }
/**/
};


enum TipoDePieza : unsigned char{
  PIEZA_VACIA='&',
  PIEZA_PARED='#',
  PIEZA_SINGULAR='*',
  PIEZA_PUERTA='-',
  PIEZA_OBJETIVO='.',
};

enum Direccion  {
  ARRIBA,
  ABAJO,
  IZQUIERDA,
  DERECHA
};

string stringDireccion(Direccion dir){
  switch(dir){
    case ARRIBA:
      return "ARRIBA";
    break;
    case ABAJO:
      return "ABAJO";
    break;
    case IZQUIERDA:
      return "IZQUIERDA";
    break;
    case DERECHA:
      return "DERECHA";
    break;
    default:
      return ""; //para evitar el warning: control reaches end of non-void function [-Wreturn-type]
    break;
  }
}



struct OrdenDeMovimiento{
  Direccion dir;
  unsigned char id;

  bool operator==(const OrdenDeMovimiento& orden) const {//sobrecarga de operador de igualdad
      return (dir == orden.dir) && (id == orden.id);
  }

  bool operator!=(const OrdenDeMovimiento& orden) const {//sobrecarga de operador de no igual
      return !(*this == orden);
  }

};

Direccion direccionOpuesta(Direccion dir){
  switch(dir){
    case ARRIBA:
      return ABAJO;
    break;
    case ABAJO:
      return ARRIBA;
    break;
    case IZQUIERDA:
      return DERECHA;
    break;
    case DERECHA:
      return IZQUIERDA;
    break;
    default:
      return dir; // para evitar el warning: control reaches end of non-void function [-Wreturn-type]
    break;
  }
}

class Bloque{

private:
  unsigned int x, y;
  unsigned int ancho, alto;
  bool esPiezaSingular;
  unsigned int id;
  unsigned int reduccion;
  
public:
  Bloque(){this->id=0;} //constructor vacio
  
  Bloque(unsigned int id, unsigned int x, unsigned int y, unsigned int ancho, unsigned int alto, bool esPiezaSingular, unsigned int reduccion) : 
    id(id), x(x), y(y), ancho(ancho), alto(alto), esPiezaSingular(esPiezaSingular), reduccion(reduccion){
  }//constructor

/*funciones get*/
  unsigned int getAncho() const{
    return this->ancho;
  }

  unsigned int getAlto() const{
    return this->alto;
  }

  unsigned int getID() const{
    return this->id;
  }

  unsigned int getReduccion() const {
    return this->reduccion;
  }

  unsigned int getX() const{
    return this->x;
  }

  unsigned int getY() const{
    return this->y;
  }

  bool puedeMoverse(unsigned char pieza){
    if(this->esPiezaSingular && pieza == PIEZA_PUERTA) return true;
    
    return pieza == PIEZA_VACIA || pieza == PIEZA_OBJETIVO;
  }

  void mover(Direccion dir){
    switch(dir){
      case ARRIBA:
        this->y--;
      break;
      case ABAJO:
        this->y++;
      break;
      case IZQUIERDA:
        this->x--;
      break;
      case DERECHA:
        this->x++;
      break;
    }
  }


};

namespace std {//implentacion de la libreria boost Hash para la matriz
    template <>
    struct hash<vector<vector<unsigned char>>> {
        size_t operator()(const vector<vector<unsigned char>>& vec, Bloque* bloques) const {
            std::hash<unsigned char> charHasher;
            size_t hash = 0;

            for (const auto& fila : vec) {
                for (const unsigned char& elemento : fila) {
                    const unsigned char& corresponding = bloques[elemento].getID() == 0 ? elemento : bloques[elemento].getReduccion();
                    hash ^= charHasher(corresponding) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
                }
            }

            return hash; 
        }
    };

    template <>
    struct hash<Posicion> {
      size_t operator()(const Posicion& pos) const {
        return hash<int>()(pos.x) ^ hash<int>()(pos.y);
      }
    };
}


class Klotski;//Solucionador de Klotski

class Tabla {

  private:
  Bloque bloques[255]={};
  vector<vector<unsigned char>> tableroDeJuego;
  vector<vector<unsigned char>> baseDeltablero;
  friend class Klotski;

  public:

  Bloque* getBloques(){
    return this->bloques;
  }


  void printTabla() const {

    for(unsigned int y = 0; y < tableroDeJuego.size(); y++){
      for(unsigned int x = 0; x < tableroDeJuego[0].size(); x++){

        cout << tableroDeJuego[y][x];
      }
      cout << "\n";
    }
    cout << endl;
  }

  Tabla(vector<string>& lineas) : 
    tableroDeJuego(lineas.size(), vector<unsigned char>(lineas[0].size(),' ')),
    baseDeltablero(lineas.size(), vector<unsigned char>(lineas[0].size(),' ')){
    bool encontrados[255] = {0};

    unordered_map<int, unordered_map<int, unsigned int>> reducciones;
    unsigned int siguienteReduccion = 'a';

    for(unsigned int y = 0; y < lineas.size(); y++){
      for(unsigned int x = 0; x < lineas[0].size(); x++){
        bool esPiezaSingular = false;

        tableroDeJuego[y][x] = (unsigned char)lineas[y][x];
        switch(lineas[y][x]){
          case PIEZA_PARED:
          case PIEZA_PUERTA:
          case PIEZA_OBJETIVO:
          case PIEZA_VACIA:
            baseDeltablero[y][x] = lineas[y][x];
          case 0:
          break;
          case PIEZA_SINGULAR:
            esPiezaSingular = true;
          default:
            baseDeltablero[y][x] = PIEZA_VACIA;
            if(!encontrados[lineas[y][x]]){
              // encontrar altura y ancho del bloque
              unsigned int busquedaY = y;
              unsigned int busquedaX = x;

              while(busquedaY < lineas.size() && lineas[busquedaY][x] == lineas[y][x]){
                busquedaY++;
              }

              while(busquedaX < lineas[0].size() &&  lineas[y][busquedaX] == lineas[y][x]){
                busquedaX++;
              }

              unsigned int anchoDeBloque = busquedaX - x;
              unsigned int altoDeBloque = busquedaY - y;

              if(reducciones[anchoDeBloque].find(altoDeBloque) == reducciones[anchoDeBloque].end()){
                reducciones[anchoDeBloque][altoDeBloque] = siguienteReduccion++;
              }

              this->bloques[lineas[y][x]] = Bloque(lineas[y][x], x, y, anchoDeBloque, altoDeBloque, esPiezaSingular, reducciones[anchoDeBloque][altoDeBloque]);
              encontrados[lineas[y][x]] = true;
            }
        }
      }
    }
  }

  bool bloquePuedeMorverse(Direccion dir, unsigned char blockID){
    Bloque& bloqueObjetivo = bloques[blockID];

    switch(dir){
      case ARRIBA:
        if (bloqueObjetivo.getY() == 0) return false;
        for(unsigned int x = bloqueObjetivo.getX(); x < bloqueObjetivo.getX() + bloqueObjetivo.getAncho(); x++){
          if(!(0 <= x && x < tableroDeJuego[0].size())) continue;;
          if(!bloqueObjetivo.puedeMoverse(tableroDeJuego[bloqueObjetivo.getY()-1][x])){
            return false;
          }
        }
        return true;

      case ABAJO:
        if (bloqueObjetivo.getY()+bloqueObjetivo.getAlto() > tableroDeJuego.size()-1) return false;
        for(unsigned int x = bloqueObjetivo.getX(); x < bloqueObjetivo.getX() + bloqueObjetivo.getAncho(); x++){
          if(!(0 <= x && x < tableroDeJuego[0].size())) continue;

          if(!bloqueObjetivo.puedeMoverse(tableroDeJuego[bloqueObjetivo.getY()+bloqueObjetivo.getAlto()][x])){
            return false;
          }
        }
        return true;

      case IZQUIERDA:
        if (bloqueObjetivo.getX() == 0) return false;
        for(unsigned int y = bloqueObjetivo.getY(); y < bloqueObjetivo.getY() + bloqueObjetivo.getAlto(); y++){
          if(!(0 <= y && y < tableroDeJuego.size())) continue;

            if(!bloqueObjetivo.puedeMoverse(tableroDeJuego[y][bloqueObjetivo.getX()-1])){
              return false;
            }
        }
        return true;
      case DERECHA:
        if (bloqueObjetivo.getX() + bloqueObjetivo.getAncho() > tableroDeJuego[0].size()-1) return false;
        for(unsigned int y = bloqueObjetivo.getY(); y < bloqueObjetivo.getY() + bloqueObjetivo.getAlto(); y++){
          if(!(0 <= y && y < tableroDeJuego.size())) continue;

            if(!bloqueObjetivo.puedeMoverse(tableroDeJuego[y][bloqueObjetivo.getX()+bloqueObjetivo.getAncho()])){
              return false;
            }
        }
        return true;
    }
    return false;
  }

  void moveBlock(Direccion dir, unsigned char blockID){
    Bloque& bloqueObjetivo = bloques[blockID];
    switch(dir){
      case ARRIBA:
        for(unsigned int x = bloqueObjetivo.getX(); x < bloqueObjetivo.getX() + bloqueObjetivo.getAncho(); x++){
          tableroDeJuego[bloqueObjetivo.getY()-1][x] = blockID;
          tableroDeJuego[bloqueObjetivo.getY()+bloqueObjetivo.getAlto()-1][x] = baseDeltablero[bloqueObjetivo.getY()+bloqueObjetivo.getAlto()-1][x];
        }
        break;
      case ABAJO:
        for(unsigned int x = bloqueObjetivo.getX(); x < bloqueObjetivo.getX() + bloqueObjetivo.getAncho(); x++){
          tableroDeJuego[bloqueObjetivo.getY()+bloqueObjetivo.getAlto()][x] = blockID;
          tableroDeJuego[bloqueObjetivo.getY()][x] = baseDeltablero[bloqueObjetivo.getY()][x];
        }
        break;
      case IZQUIERDA:
        for(unsigned int y = bloqueObjetivo.getY(); y < bloqueObjetivo.getY() + bloqueObjetivo.getAlto(); y++){
            tableroDeJuego[y][bloqueObjetivo.getX()-1] = blockID;
            tableroDeJuego[y][bloqueObjetivo.getX()+bloqueObjetivo.getAncho()-1] = baseDeltablero[y][bloqueObjetivo.getX()+bloqueObjetivo.getAncho()-1];
        }
        break;
      case DERECHA:
        for(unsigned int y = bloqueObjetivo.getY(); y < bloqueObjetivo.getY() + bloqueObjetivo.getAlto(); y++){
            tableroDeJuego[y][bloqueObjetivo.getX()+bloqueObjetivo.getAncho()] = blockID;
            tableroDeJuego[y][bloqueObjetivo.getX()] = baseDeltablero[y][bloqueObjetivo.getX()];
        }
        break;
    }
    bloqueObjetivo.mover(dir);
  }

  bool juegoGanado(){
    for(auto& row : tableroDeJuego){  
      for(auto& el : row){
        if(el == PIEZA_OBJETIVO) return false;
      }
    }

    return true;
  }



};


struct Solucion{
  TipoDeSolucion estado;
  unsigned int profundidad;
  size_t ultimoHash;
  OrdenDeMovimiento movimiento;
};

class Klotski{

private:
  unordered_map<size_t, Solucion> memoria;
  unsigned int profundidad = 0;
  Tabla tablaSolucion;
  const Tabla tablaOriginal;

public:


  Klotski(Tabla tablaSolucion) : tablaSolucion(tablaSolucion), tablaOriginal(tablaOriginal) {}//constructor


  void printEstado(size_t estadoDelHash){
    unsigned int profundidadDestino = this->memoria.at(estadoDelHash).profundidad;
    
    cout << "imprimiendo estado de la profundidad " << profundidadDestino << endl;
    this->tablaOriginal.printTabla();

    stack<OrdenDeMovimiento*> movimientos;//ocupa estructura LIFO y se usa para imprimir los pasos de la solucion

    unsigned int contador = 0;

    Solucion* solucionActual = &this->memoria.at(estadoDelHash);

    while(solucionActual->ultimoHash != 0){

      cout << "\r" << contador << "/" << profundidadDestino;

      movimientos.push(&solucionActual->movimiento);
      solucionActual = &this->memoria.at(solucionActual->ultimoHash);
      contador++;
    }
    movimientos.push(&solucionActual->movimiento);

    cout << "\n";

    while(movimientos.size()){
      OrdenDeMovimiento* execute = movimientos.top();
      movimientos.pop();
      cout << "MOVIDO " << (char)execute->id << " ";
      switch(execute->dir){
        case ARRIBA:
        cout << "ARRIBA";
        break;
        case ABAJO:
        cout << "ABAJO";
        break;
        case IZQUIERDA:
        cout << "IZQUIERDA";
        break;
        case DERECHA:
        cout << "DERECHA";
        break;
      }
      cout << endl;

    }
  }

  unordered_map<unsigned char, unsigned char> getMapping(Tabla desde, Tabla hasta){
    unordered_map<unsigned char, unsigned char> mapping;
    unordered_map<Posicion, unsigned char> desdePosIDs;
    unordered_map<Posicion, unsigned char> hastaPosIDs;

    for( unsigned int i = 0; i < 255; i++){
      if(desde.bloques[i].getID() != 0){
unordered_map<Posicion, unsigned char> desdePosIDs;
/*        desdePosIDs[{from.blocks[i].getX(), from.blocks[i].getY()}] = i;  */
      }

      if(hasta.bloques[i].getID() != 0){
unordered_map<Posicion, unsigned char> hastaPosIDs;
/*        hastaPosIDs[{to.blocks[i].getX(), to.blocks[i].getY()}] = i;*/
      }
    }

    for(auto& [pos, desdeID] : desdePosIDs){
      mapping[desdeID] = hastaPosIDs.at(pos);
    }

    return mapping;
  }

size_t solucionador() {
    // Se obtiene el estado inicial y se agrega a la memoria
    size_t estadoInicial = std::hash<vector<vector<unsigned char>>>()(this->tablaSolucion.tableroDeJuego, this->tablaSolucion.bloques);
    this->memoria[estadoInicial] = Solucion{EN_PROGRESO, 0, 0, {ARRIBA, 0}};

    size_t ultimoHash = 0; // Variable para mantener el último estado en el que nos encontramos
    OrdenDeMovimiento ultimoOrden; // Variable para mantener el último movimiento realizado

    while (true) {
        profundidad++; // Incrementa la profundidad en cada iteración del bucle

        bool movimientoEncontrado = false; // Flag para indicar si se encontró un movimiento válido

        // Bucle para iterar sobre todos los bloques en el tablero
        for (unsigned char i = PIEZA_SINGULAR; i != PIEZA_SINGULAR - 1; i = (i + 1) % 255) {
            if (this->tablaSolucion.bloques[i].getID() == 0) continue; // Ignora bloques vacíos

            unsigned int direccionInicial = rand() % 4; // Selecciona una dirección inicial de manera aleatoria

            // Bucle para probar movimientos en las cuatro direcciones posibles
            for (unsigned int j = 0; j < 4; j++) {
                unsigned int idir = (direccionInicial + j) % 4;
                Direccion dir = static_cast<Direccion>(idir);

                // Verifica si el movimiento es válido y no es el opuesto al último movimiento realizado
                if (ultimoOrden != OrdenDeMovimiento{direccionOpuesta(dir), i} && this->tablaSolucion.bloquePuedeMorverse(dir, i)) {
                    ultimoOrden = {dir, i};
                    this->tablaSolucion.moveBlock(dir, i);

                    // Calcula el hash del nuevo estado resultante
                    size_t hashMovido = std::hash<vector<vector<unsigned char>>>()(this->tablaSolucion.tableroDeJuego, this->tablaSolucion.bloques);

                    #ifdef PRINT
                    cout << profundidad << ": " << (char)i << " moviendo " << (int)dir << " -> " << hashMovido << "\n";
                    this->tablaSolucion.printTabla();
                    #endif

                    // Verifica si se ha llegado a la solución
                    if (i == PIEZA_SINGULAR && this->tablaSolucion.juegoGanado()) {
                        this->memoria[hashMovido] = Solucion{SOLUCION_ENCONTRADA, profundidad, ultimoHash, {dir, i}};
                        return hashMovido;
                    }

                    // Verifica si el estado resultante ya está en la memoria
                    if (this->memoria.find(hashMovido) == this->memoria.end()) {
                        this->memoria[hashMovido] = {EN_PROGRESO, profundidad, ultimoHash, ultimoOrden};
                        ultimoHash = hashMovido;
                        movimientoEncontrado = true;
                        break;
                    }

                    // Retrocede un nivel en la profundidad (backtracking)
                    profundidad--;
                    this->tablaSolucion.moveBlock(direccionOpuesta(dir), i);

                    #ifdef PRINT
                    cout << "Atorado, revirtiendo 1 de profundidad\n";
                    cout << profundidad << ": " << (char)ultimoOrden.id << " moviendo " << (int)ultimoOrden.dir << "\n";
                    this->tablaSolucion.printTabla();
                    #endif

                    ultimoHash = this->memoria.at(ultimoHash).ultimoHash;
                }
            }

            if (movimientoEncontrado) {
                break; // Si se encontró un movimiento válido, sal del bucle de bloques
            }
        }

        if (profundidad == 0) {
            break; // Si la profundidad es cero, sal del bucle principal
        }
    }

    return -1; // No debería llegar aquí, pero por si acaso
}


/*
//funcion original, con GOTO y search:
  size_t solucionador(){
    {
      size_t estadoInicial = std::hash<vector<vector<unsigned char>>>()(this->tablaSolucion.tableroDeJuego, this->tablaSolucion.bloques);
      //auto estadoInicial = std::hash<vector<vector<unsigned char>>>()(this->tablaSolucion.tableroDeJuego, this->tablaSolucion.bloques);
      this->memoria[estadoInicial] = Solucion{EN_PROGRESO, 0, 0, {ARRIBA, 0}};
    }
    size_t ultimoHash = 0;
    OrdenDeMovimiento ultimoOrden;

    while(true){
      search:
      profundidad++;
      for(unsigned char i = PIEZA_SINGULAR; i != PIEZA_SINGULAR - 1; i = (i + 1)%255){
        if(this->tablaSolucion.bloques[i].getID() == 0) continue;
        unsigned int direccionInicial = rand() % 4;


        for(unsigned int j = 0; j < 4; j++){


          unsigned idir = (direccionInicial + j) % 4;


          Direccion dir = (Direccion)(idir);
          if(ultimoOrden != OrdenDeMovimiento{direccionOpuesta(dir), i} && this->tablaSolucion.bloquePuedeMorverse(dir, i)){
            ultimoOrden = {dir, i};
            this->tablaSolucion.moveBlock(dir, i);

            //auto hashMovido = std::hash<vector<vector<unsigned char>>>()(this->tablaSolucion.tableroDeJuego, this->tablaSolucion.bloques);
            size_t hashMovido = std::hash<vector<vector<unsigned char>>>()(this->tablaSolucion.tableroDeJuego, this->tablaSolucion.bloques);

            #ifdef PRINT
              cout << profundidad << ": " << (char)i << " moviendo " << (int)dir << " -> " << hashMovido << "\n";
              this->tablaSolucion.printTabla();
            #endif

            if(i == PIEZA_SINGULAR){
              if (this->tablaSolucion.juegoGanado()){
                this->memoria[hashMovido] = Solucion{SOLUCION_ENCONTRADA, profundidad, ultimoHash, {dir, i}};
                return hashMovido;
              }
            }

            if (this->memoria.find(hashMovido) != this->memoria.end()) {
              profundidad--;         
              this->tablaSolucion.moveBlock(direccionOpuesta(dir), i);
              continue;
            }else{
              this->memoria[hashMovido] = {EN_PROGRESO, profundidad, ultimoHash, ultimoOrden};
            }

            ultimoHash = hashMovido;
            goto search;
          }

        }
      }

      Solucion& revertirEstado = this->memoria.at(ultimoHash);
      Solucion& revertirUltimaAccion = this->memoria.at(this->memoria.at(ultimoHash).ultimoHash);
      profundidad = revertirUltimaAccion.profundidad;

      this->tablaSolucion.moveBlock(direccionOpuesta(revertirEstado.orden.dir), revertirEstado.orden.id);


      #ifdef PRINT
      cout << "Atorado, revirtiendo 1 de profundidad\n";
      cout << profundidad << ": " << (char)revertirUltimaAccion.orden.id << " moving " << (int)revertirUltimaAccion.orden.dir << "\n";
      this->tablaSolucion.printTabla();
      #endif

      ultimoHash = revertirEstado.ultimoHash;
    }
  }
*/



};

int main(){
  vector<string> matriz = {
    "&&&&&&&&&&",
    "&&&&&&&z&&",
    "&&######&&",
    "&&#a**b#&&",
    "&&#a**b#&&",
    "&&#cdde#&&",
    "&&#cfge#&&",
    "&&#h&&i#&&",
    "&&##--##&&",
    "&&&&&&&&..",
    "&&&&&&&&.."
  }; 


  vector<string> matriz2 = {
    "&&&&&&&&&&&&#",
    "&z&&&&&&&&&&#",
    "&&######&&&&#",
    "&&#a**h#&&&&#",
    "&&#b**g#&&&&#",
    "&&#cdef#&&&&#",
    "&&#ijkl#&&&&#",
    "&&#m&&n#&r&&#",
    "&&##--##&&&&#",
    "&&&&&&&&..&&#",
    "&&&&&&&&..&&#"
};
    

  Tabla tablaSolucion = Tabla(matriz2);

/*
  for(int i = 0; i < 255; i++){//imprimir bloques de tabla solucion
    if (tablaSolucion.getBloques()[i].getID() != 0){
      cout << "Block " << (char)tablaSolucion.getBloques()[i].getID() << "(" << tablaSolucion.getBloques()[i].getX() << " " <<
       tablaSolucion.getBloques()[i].getY() << " " << tablaSolucion.getBloques()[i].getAncho() << " " << tablaSolucion.getBloques()[i].getAlto() << 
       ") " << tablaSolucion.getBloques()[i].puedeMoverse(PIEZA_PUERTA) << endl;
    }
  }
  */

  tablaSolucion.printTabla();
  Klotski klotski = (tablaSolucion);
  size_t solucion = klotski.solucionador();

  cout << "Solucion Encontrada\n";
  
  /*
  klotski.printEstado(solucion);//pasos para la solucion
  */
  return 0;
}
