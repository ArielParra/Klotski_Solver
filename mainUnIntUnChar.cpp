#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>//pilas std
#include "Nivel.cpp"
#include "compatibilidad.h"


//para evitar using namespace std y controlar el uso de std
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::unordered_map;
using std::stack;


#define PRINT

enum TipoDeSolucion {
  SOLUCION_ENCONTRADA,
  EN_PROGRESO,
};

struct Posicion{
  unsigned int x, y;

  bool operator==(const Posicion& other) const {
    return other.x == x && other.y == y;
  }
};

enum TipoDePieza : char{
  PIEZA_VACIA='&',
  PIEZA_PARED='#',
  PIEZA_SINGULAR='*',
  PIEZA_PUERTA='-',
  PIEZA_OBJETIVO='.',
};

enum Direccion{
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
  unsigned char id; //si no es unsigned char da segmentation faultOrdenDeMovimiento

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

  bool puedeMoverse(char pieza){
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
    struct hash<vector<vector<char>>> {
        unsigned int operator()(const vector<vector<char>>& vec, Bloque* bloques) const {
            std::hash<char> charHasher;
            unsigned int hash = 0;

            for (const auto& fila : vec) {
                for (const char& elemento : fila) {
                    const char& corresponding = bloques[elemento].getID() == 0 ? elemento : bloques[elemento].getReduccion();
                    hash ^= charHasher(corresponding) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
                }
            }

            return hash; 
        }
    };

    template <>
    struct hash<Posicion> {
      unsigned int operator()(const Posicion& pos) const {
        return hash<int>()(pos.x) ^ hash<int>()(pos.y);
      }
    };
}


class Klotski;

class Tabla {

  private:
  Bloque bloques[255]={};//si sobra tiempo sera new y delete
  vector<vector<char>> tableroDeJuego;
  vector<vector<char>> baseDeltablero;
  friend class Klotski;

  public:
  Tabla(){}
  
  Tabla(vector<string>& matriz) : 
    tableroDeJuego(matriz.size(), vector<char>(matriz[0].size(),' ')),
    baseDeltablero(matriz.size(), vector<char>(matriz[0].size(),' ')){
    bool encontrados[255] = {0};

    unordered_map<int, unordered_map<int, unsigned int>> reducciones;
    unsigned int siguienteReduccion = 'a';

    for(unsigned int y = 0; y < matriz.size(); y++){
      for(unsigned int x = 0; x < matriz[0].size(); x++){
        bool esPiezaSingular = false;

        tableroDeJuego[y][x] = (char)matriz[y][x];
        switch(matriz[y][x]){
          case PIEZA_PARED:
          case PIEZA_PUERTA:
          case PIEZA_OBJETIVO:
          case PIEZA_VACIA:
            baseDeltablero[y][x] = (char)matriz[y][x];
          case 0://segun yo no hacia nada pero mejor no le movere por si las moscas
          break;
          case PIEZA_SINGULAR:
            esPiezaSingular = true;
          default:
            baseDeltablero[y][x] = PIEZA_VACIA;
            if(!encontrados[matriz[y][x]]){
              // encontrar altura y ancho del bloque
              unsigned int busquedaY = y;
              unsigned int busquedaX = x;

              while(busquedaY < matriz.size() && matriz[busquedaY][x] == matriz[y][x]){
                busquedaY++;
              }

              while(busquedaX < matriz[0].size() &&  matriz[y][busquedaX] == matriz[y][x]){
                busquedaX++;
              }

              unsigned int anchoDeBloque = busquedaX - x;
              unsigned int altoDeBloque = busquedaY - y;

              if(reducciones[anchoDeBloque].find(altoDeBloque) == reducciones[anchoDeBloque].end()){
                reducciones[anchoDeBloque][altoDeBloque] = siguienteReduccion++;
              }

              this->bloques[matriz[y][x]] = Bloque(matriz[y][x], x, y, anchoDeBloque, altoDeBloque, esPiezaSingular, reducciones[anchoDeBloque][altoDeBloque]);
              encontrados[matriz[y][x]] = true;
            }
        }
      }
    }
  }

Bloque* getBloques(){
    return this->bloques;
  }
  unsigned int getAltoTablero() const{
    return this->tableroDeJuego.size();
  }

  unsigned int getAnchoTablero() const{
    return this->tableroDeJuego[0].size();
  }

  void printTabla() const {
    for(unsigned int y = 0; y < getAltoTablero(); y++){
      for(unsigned int x = 0; x < getAnchoTablero(); x++){
        switch (tableroDeJuego[y][x]){
          case '&': cout <<                             " "; break;
          case '*': cout << BG_RED                   << "♥"; break;
          case '#': cout << FG_BLUE                  << "█"; break;
          case '.': cout << FG_RED                   << "○"; break;
          case '-': cout <<                             "║"; break;
          case 'a': cout << BG_YELLOW                << "a"; break;
          case 'b': cout << BG_MAGENTA               << "b"; break;
          case 'c': cout << BG_CYAN                  << "c"; break;
          case 'd': cout << BG_GREEN                 << "d"; break;
          case 'e': cout << BG_BLACK                 << "e"; break;
          case 'f': cout << BG_WHITE   << FG_BLACK   << "f"; break;
          case 'g': cout << BG_YELLOW  << FG_MAGENTA << "g"; break;
          case 'h': cout << BG_YELLOW  << FG_GREEN   << "h"; break;
          case 'i': cout << BG_YELLOW  << FG_BLACK   << "i"; break;
          case 'j': cout << BG_CYAN    << FG_MAGENTA << "j"; break;
          case 'k': cout << BG_CYAN    << FG_GREEN   << "k"; break;
          case 'l': cout << BG_CYAN    << FG_BLACK   << "l"; break;
          case 'm': cout << BG_CYAN    << FG_YELLOW  << "m"; break;
          case 'n': cout << BG_GREEN   << FG_MAGENTA << "n"; break;
          case 'o': cout << BG_GREEN   << FG_CYAN    << "o"; break;
          case 'p': cout << BG_GREEN   << FG_BLACK   << "p"; break;
          case 'q': cout << BG_GREEN   << FG_YELLOW  << "q"; break;
          case 'r': cout << BG_MAGENTA << FG_YELLOW  << "r"; break;
          case 's': cout << BG_MAGENTA << FG_GREEN   << "s"; break;
          case 't': cout << BG_MAGENTA << FG_CYAN    << "t"; break;
          case 'u': cout << BG_MAGENTA << FG_BLACK   << "u"; break;
          case 'v': cout << BG_BLACK   << FG_MAGENTA << "v"; break;
          case 'w': cout << BG_BLACK   << FG_CYAN    << "w"; break;
          case 'x': cout << BG_BLACK   << FG_MAGENTA << "x"; break;
          case 'y': cout << BG_BLACK   << FG_GREEN   << "y"; break;
          case 'z': cout << BG_BLACK   << FG_YELLOW  << "z"; break;
          default:  cout << tableroDeJuego[y][x];            break; 
        }//switch
        cout<<RESET_COLOR;
      }//x
      cout << endl;
    }//y
  }//printTabla


  bool bloquePuedeMorverse(Direccion dir, char IDdelBloque){
    Bloque& bloqueObjetivo = bloques[IDdelBloque];

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

  void moverBloque(Direccion dir, char IDdelBloque){
    Bloque& bloqueObjetivo = bloques[IDdelBloque];

    switch(dir){
      case ARRIBA:
        for(unsigned int x = bloqueObjetivo.getX(); x < bloqueObjetivo.getX() + bloqueObjetivo.getAncho(); x++){
          tableroDeJuego[bloqueObjetivo.getY()-1][x] = IDdelBloque;
          tableroDeJuego[bloqueObjetivo.getY()+bloqueObjetivo.getAlto()-1][x] = baseDeltablero[bloqueObjetivo.getY()+bloqueObjetivo.getAlto()-1][x];
        }
        break;
      case ABAJO:
        for(unsigned int x = bloqueObjetivo.getX(); x < bloqueObjetivo.getX() + bloqueObjetivo.getAncho(); x++){
          tableroDeJuego[bloqueObjetivo.getY()+bloqueObjetivo.getAlto()][x] = IDdelBloque;
          tableroDeJuego[bloqueObjetivo.getY()][x] = baseDeltablero[bloqueObjetivo.getY()][x];
        }
        break;
      case IZQUIERDA:
        for(unsigned int y = bloqueObjetivo.getY(); y < bloqueObjetivo.getY() + bloqueObjetivo.getAlto(); y++){
            tableroDeJuego[y][bloqueObjetivo.getX()-1] = IDdelBloque;
            tableroDeJuego[y][bloqueObjetivo.getX()+bloqueObjetivo.getAncho()-1] = baseDeltablero[y][bloqueObjetivo.getX()+bloqueObjetivo.getAncho()-1];
        }
        break;
      case DERECHA:
        for(unsigned int y = bloqueObjetivo.getY(); y < bloqueObjetivo.getY() + bloqueObjetivo.getAlto(); y++){
            tableroDeJuego[y][bloqueObjetivo.getX()+bloqueObjetivo.getAncho()] = IDdelBloque;
            tableroDeJuego[y][bloqueObjetivo.getX()] = baseDeltablero[y][bloqueObjetivo.getX()];
        }
        break;
    }
    bloqueObjetivo.mover(dir);
  }

  bool juegoGanado(){
    for(auto& fila : tableroDeJuego){  
      for(auto& pieza : fila){
        if(pieza == PIEZA_OBJETIVO) return false;
      }
    }
    return true;
  }



};


struct Solucion{
  TipoDeSolucion estado;
  unsigned int profundidad;
  unsigned int ultimoHash;
  OrdenDeMovimiento movimiento;
};

class Klotski{

private:
  unordered_map<unsigned int, Solucion> memoria;
  unsigned int profundidad = 0;
  Tabla tablaSolucion;
  const Tabla tablaOriginal;

public:


  Klotski(Tabla tablaSolucion) : tablaSolucion(tablaSolucion), tablaOriginal(tablaSolucion) {}//constructor

void printTablerosSolucion(unsigned int estadoDelHash)  {
    unsigned int profundidadDestino = this->memoria.at(estadoDelHash).profundidad;

    cout << "Imprimiendo estados de la solución:\n";
    Tabla tablaParaPrint(this->tablaOriginal);
    Solucion* solucionActual = &this->memoria.at(estadoDelHash);

    for (unsigned int contadorDeProfundidad = 0; solucionActual->ultimoHash != 0; contadorDeProfundidad++) {
        cout << "\rProfundidad: (" << contadorDeProfundidad << "/" << profundidadDestino << ")" << endl;
        cout << "Tabla en la profundidad " << contadorDeProfundidad << ":\n";
        this->tablaOriginal.printTabla();
        cout << "---------------------\n";

        tablaParaPrint.moverBloque(solucionActual->movimiento.dir, solucionActual->movimiento.id);

        solucionActual = &this->memoria.at(solucionActual->ultimoHash);
    }

    // Imprimir la tabla final después de la solución
    cout << "\rProfundidad: (" << profundidadDestino << "/" << profundidadDestino << ")" << endl;
    cout << "Tabla Final:\n";
    this->tablaSolucion.printTabla();
}



  void printMovimientosSolucion(unsigned int estadoDelHash){
    
    unsigned int profundidadDestino = this->memoria.at(estadoDelHash).profundidad;

    stack<OrdenDeMovimiento*> movimientos;//ocupa estructura LIFO y se usa para imprimir los pasos de la solucion

    unsigned int contadorDeProfundidad = 0;

    Solucion* solucionActual = &this->memoria.at(estadoDelHash);

    while(solucionActual->ultimoHash != 0){

      cout << "\r" << contadorDeProfundidad << "/" << profundidadDestino;

      movimientos.push(&solucionActual->movimiento);
      solucionActual = &this->memoria.at(solucionActual->ultimoHash);
      contadorDeProfundidad++;
    }
    movimientos.push(&solucionActual->movimiento);

    cout << "\n";

    while(movimientos.size()){
      OrdenDeMovimiento* realizar = movimientos.top();
      movimientos.pop();

      cout << "MOVIDO " << (char)realizar->id << " ";

      switch(realizar->dir){
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
 

unsigned int solucionador() {
    // Se obtiene el hash inicial del estado del tablero de la solución
    unsigned int estadoInicial = std::hash<vector<vector<char>>>()(this->tablaSolucion.tableroDeJuego, this->tablaSolucion.bloques);
    
    // Se inicializa la memoria con el estado inicial y se marca como en progreso
    this->memoria[estadoInicial] = Solucion{EN_PROGRESO, 0, 0, {ARRIBA, 0}};
    unsigned int ultimoHash = 0;
    OrdenDeMovimiento ultimoOrden;
    
    // Llama a la función recursiva para buscar la solución
    return buscarSolucion(ultimoHash, ultimoOrden);
}

unsigned int buscarSolucion(unsigned int& ultimoHash, OrdenDeMovimiento& ultimoOrden) {
    profundidad++;

    // Recorre todas las piezas en el tablero
    for (unsigned char i = PIEZA_SINGULAR; i != PIEZA_PARED ; i = (i + 1) % 255) {
        if (this->tablaSolucion.bloques[i].getID() == 0) continue;

        // Selecciona una dirección inicial aleatoria
        unsigned int direccionInicial = rand() % 4;

        // Recorre las direcciones posibles
        for (unsigned int j = 0; j < 4; j++) {
            Direccion dir = static_cast<Direccion>((direccionInicial + j) % 4);

            // Verifica si es posible mover la pieza en la dirección actual
            if (ultimoOrden != OrdenDeMovimiento{direccionOpuesta(dir), i} && this->tablaSolucion.bloquePuedeMorverse(dir, i)) {
                ultimoOrden = {dir, i};
                this->tablaSolucion.moverBloque(dir, i);

                // Calcula el hash del nuevo estado del tablero
                unsigned int hashMovido = std::hash<vector<vector<char>>>()(this->tablaSolucion.tableroDeJuego, this->tablaSolucion.bloques);

                #ifdef PRINT
                cout << "-----------------------------------------------------------------------\n";
                cout << "Profundidad: (" << profundidad << "), " << " moviendo '" << (char)i << "' " << stringDireccion(dir) << ", hashMovido -> " << hashMovido << "\n";
                this->tablaSolucion.printTabla();
                #endif

                // Verifica si se ha alcanzado la solución
                if (i == PIEZA_SINGULAR && this->tablaSolucion.juegoGanado()) {
                    this->memoria[hashMovido] = Solucion{SOLUCION_ENCONTRADA, profundidad, ultimoHash, {dir, i}};
                    return hashMovido;
                }

                // Verifica si ya se ha explorado este estado antes
                if (this->memoria.find(hashMovido) != this->memoria.end()) {
                    profundidad--;
                    this->tablaSolucion.moverBloque(direccionOpuesta(dir), i);
                    continue;
                } else {
                    // Almacena el nuevo estado en la memoria
                    this->memoria[hashMovido] = {EN_PROGRESO, profundidad, ultimoHash, ultimoOrden};
                }
                // Actualiza el último hash con el nuevo estado
                ultimoHash = hashMovido;

                // Actualiza el último hash con el nuevo estado
                return buscarSolucion(ultimoHash, ultimoOrden);
            }
        }
    }
    /*backtracking*/
    // Si no se encuentra una solución desde este estado, se retrocede
    Solucion& revertirEstado = this->memoria.at(ultimoHash);
    Solucion& revertirUltimaAccion = this->memoria.at(this->memoria.at(ultimoHash).ultimoHash);
    profundidad = revertirUltimaAccion.profundidad;

    this->tablaSolucion.moverBloque(direccionOpuesta(revertirEstado.movimiento.dir), revertirEstado.movimiento.id);

    #ifdef PRINT
    cout << "BACKTRACKING: Profundidad: (" << profundidad << "), " << " moviendo '" << (char)revertirUltimaAccion.movimiento.id << "' " << stringDireccion(revertirUltimaAccion.movimiento.dir) << "\n";
    this->tablaSolucion.printTabla();
    #endif

    ultimoHash = revertirEstado.ultimoHash;

    // Llama recursivamente para explorar desde el estado anterior
    return buscarSolucion(ultimoHash, ultimoOrden);
}

};//klotski

int main(){
 //setUTF8();
  vector<string> matriz = {
    "&&&&&&&&&&",
    "&&&&&&&&&&",
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
    /*
    int N;
    cout << "Ingrese el número N para el archivo nivel_N.txt: ";
    cin >> N;

    Nivel nivel(N);
    if(!nivel.cargarNivel()){
        cout << "Error: No se pudo abrir el archivo " << nivel.getNombreArchivo() << endl;
    }else{
        cout<< "Nombre del Nivel: "<< nivel.getNombreNivel() <<endl;
        cout << "Tabla del archivo" << nivel.getNombreArchivo() << endl;
        cout << "getAnchoNivel " << nivel.getAnchoNivel() << endl;
        cout << "getAltoNivel " << nivel.getAltoNivel() << endl;
        
    }
    */

Tabla tablaSolucion = Tabla(matriz);
tablaSolucion.printTabla();
/*
  for(unsigned int i = 0; i < 255; i++){//imprimir bloques de tabla solucion
    if (tablaSolucion.getBloques()[i].getID() != 0){
      cout << "Bloque " << (char)tablaSolucion.getBloques()[i].getID() << "(" << tablaSolucion.getBloques()[i].getX() << " " <<
       tablaSolucion.getBloques()[i].getY() << " " << tablaSolucion.getBloques()[i].getAncho() << " " << tablaSolucion.getBloques()[i].getAlto() << 
       ") " << tablaSolucion.getBloques()[i].puedeMoverse(PIEZA_PUERTA) << endl;
    }
  }
  
  */
/*
  tablaSolucion.printTabla();
  Klotski klotski = (tablaSolucion);
  unsigned int solucion = klotski.solucionador();

  cout << "Solucion Encontrada\n";
  
  klotski.printMovimientosSolucion(solucion);//pasos para la solucion
  //klotski.printTablerosSolucion(solucion); // Llama a la nueva función
  */
  
  return 0;
}
