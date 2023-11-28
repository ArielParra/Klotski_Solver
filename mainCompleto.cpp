#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <vector>
using std::vector; 

#include <unordered_map> //hash map std
using std::unordered_map; 

#include <stack>//pilas std
using std::stack;

#include "Nivel.cpp"
#include "compatibilidad.h"

#define LIMITE_DE_UNSIGNED_CHAR 255 // 8 bits sin signo
#define LIMITE_DE_PROFUNDIDAD 100000 // limite de profundidad para evitar segmentation fault

//#define DEBUG_LINUX //debug para imprimir en Klotski solucionador

enum TipoDeSolucion {
  //Tipo de dato para saber en que estado de la solucion esta 
  SOLUCION_ENCONTRADA,
  EN_PROGRESO,
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

string stringDireccion(Direccion dir){
  //convierte la direccion a string para imprimir en pantalla
 switch(dir){
    case ARRIBA:    return "↑ ARRIBA";    break;
    case ABAJO:     return "↓ ABAJO";     break;
    case IZQUIERDA: return "← IZQUIERDA"; break;
    case DERECHA:   return "→ DERECHA";   break;
    default:        return "";          break; //para evitar el warning: control reaches end of non-void function [-Wreturn-type]
  }
}


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

/*clases*/

class Posicion {
  //Tipo de dato para saber en que posicion esta respecto al tablero de la solucion esta 
  public:
    unsigned int x, y;
    bool operator==(const Posicion& pos) const {//sobrecarga de asignacion de posicion
      return pos.x == this->x && pos.y == this->y;
    }
};
class Bloque{

private:
  // la posicion del bloque en el tablero del juego
  unsigned int x, y;
  // el ancho y alto del bloque
  unsigned int ancho, alto;
  // esPiezaSingular es una bandera que indica si el bloque es la pieza singular
  bool esPiezaSingular;
  // id es la identificación única de cada bloque en el tablero del juego
  // por ejemplo letras ASCII y los otros caracteres
  unsigned int id; 
  // reduccion asigna un valor unico a cada combinación de ancho y alto de un bloque específico
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

    //verifica si la pieza singular puede moverse por la puerta
    if(this->esPiezaSingular && pieza == PIEZA_PUERTA) {return true; }

    //si se puede mover sobre la pieza objetivo
    if(pieza == PIEZA_OBJETIVO){return true;}
    
    if(pieza == PIEZA_PARED){return false;}


    //por defecto solo puede moverse a una pieza vacia
    return pieza == PIEZA_VACIA;
  }

  void mover(Direccion dir){
  //mueve el bloque en la direccion especificada modificando sus posiciones privadas x e y
    switch(dir){
      case ARRIBA:    this->y--; break;  
      case ABAJO:     this->y++; break;
      case IZQUIERDA: this->x--; break;
      case DERECHA:   this->x++; break;
    }
  }
  
};//clase Bloque

namespace std {//implentacion de la libreria boost Hash para la matriz

/*Esta operación de hash es una manera de condensar la información 
del tablero de juego en un valor entero que se puede utilizar para comparar configuraciones de tablero y verificar
si dos configuraciones son iguales o diferentes. 
*/
    template <>
    struct hash<vector<vector<char>>> { //vector<vector<char>> es lo mismo que vector<string> pero sin las funciones de string
        unsigned int operator()(const vector<vector<char>>& matriz, Bloque* bloques) const {
          std::hash<char> charHasher;
          unsigned int hash = 0;

          for (const auto& fila : matriz) {
              for (const char& elemento : fila) {
                //Para cada elemento en la matriz, se verifica si el bloque asociado a ese elemento tiene un id igual a cero. 
                //Si es cero, se utiliza el propio elemento; de lo contrario, se utiliza el resultado de llamar a getReduccion() en ese bloque. 
                //Esto permite manejar diferentes tipos de elementos en el tablero de juego.
                  const char& valor = bloques[elemento].getID() == 0 ? elemento : bloques[elemento].getReduccion();
                  //se realiza un hash de cada elemento de la matriz y se agrega al hash general
                  hash ^= charHasher(valor) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
              }
          }
          return hash; 
        }
    };

    template <>
    struct hash<Posicion> {
      //sobrecarga de operacion de hash para la posicion
      unsigned int operator()(const Posicion& pos) const {
        //se realiza un hash de cada elemento de la posicion y se agrega al hash general
        return hash<int>()(pos.x) ^ hash<int>()(pos.y);
      }
    };
}


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
  Tabla(){}///constructor vacio
  
 Tabla(vector<string>& matriz) :
    // Inicialización de las matrices tableroDeJuego y baseDeltablero con espacios en blanco
    tableroDeJuego(matriz.size(), vector<char>(matriz[0].size(),' ')),
    baseDeltablero(matriz.size(), vector<char>(matriz[0].size(),' ')) {

    // vector booleano para rastrear elementos encontrados en la matriz
    vector <bool> encontrados(LIMITE_DE_UNSIGNED_CHAR, false); 
    //aparte que si no lo defino da este error: expression must be a pointer to a complete object type
    
    /*
      el doble mapa hash de reducciones se utiliza para almacenar información sobre las reducciones de bloques basadas en su ancho y alto.
      Cada ancho de bloque tiene asociado un unordered_map que mapea alturas de bloque a valores de reducción.
      Si una cierta combinación de ancho y alto de bloque no se encuentra en el mapa reducciones, se le asigna un nuevo valor de reducción. 
      se asignan valores únicos de reducción a cada combinación única de ancho y alto de bloque.
    */
    unordered_map<int, unordered_map<int, unsigned int>> reducciones; // Almacena reducciones de bloques para crear el vector de bloques

    unsigned int siguienteReduccion = 'a'; // Valor de reducción inicial

    // Recorrido de la matriz
    for(unsigned int y = 0; y < matriz.size(); y++){
      for(unsigned int x = 0; x < matriz[0].size(); x++){
        bool esPiezaSingular = false; // Bandera para identificar si el elemento es la PIEZA_SINGULAR '*'

        tableroDeJuego[y][x] = (char)matriz[y][x]; // Asigna el valor de la matriz a tableroDeJuego

        // Switch para manejar diferentes tipos de elementos en la matriz
        switch(matriz[y][x]){
          // Casos para PIEZA_PARED, PIEZA_PUERTA, PIEZA_OBJETIVO, y PIEZA_VACIA
          case PIEZA_PARED:
          case PIEZA_PUERTA:
          case PIEZA_OBJETIVO:
          case PIEZA_VACIA:
            this->baseDeltablero[y][x] = (char)matriz[y][x]; // Asigna el valor correspondiente en baseDeltablero
            break;

          // Caso para PIEZA_SINGULAR
          case PIEZA_SINGULAR:
            esPiezaSingular = true;
            // No hay un "break" aquí para que fluya hacia el caso "default"

          // Caso por defecto para manejar otros tipos de elementos
          default:
            this->baseDeltablero[y][x] = PIEZA_VACIA; // Asigna PIEZA_VACIA en baseDeltablero por defecto

            if(!encontrados[matriz[y][x]]){
              // Encontrar altura y ancho del bloque asociado al elemento actual
              unsigned int busquedaY = y;
              unsigned int busquedaX = x;

              // Encuentra la altura del bloque
              while(busquedaY < matriz.size() && matriz[busquedaY][x] == matriz[y][x]){
                  busquedaY++;
              }

              // Encuentra el ancho del bloque
              while(busquedaX < matriz[0].size() &&  matriz[y][busquedaX] == matriz[y][x]){
                  busquedaX++;
              }

              // El ancho del bloque es la diferencia (Delta) entre la posicion de busqueda y la posicion actual
              unsigned int anchoDeBloque = busquedaX - x;
              unsigned int altoDeBloque  = busquedaY - y;

              // Lógica para manejar reducciones y crear bloques
              if(reducciones[anchoDeBloque].find(altoDeBloque) == reducciones[anchoDeBloque].end()){
                  reducciones[anchoDeBloque][altoDeBloque] = siguienteReduccion++;
              }

              // Creación del bloque y asignación al miembro de datos "bloques" de la clase
              this->bloques[matriz[y][x]] = Bloque(matriz[y][x], x, y, anchoDeBloque, altoDeBloque, esPiezaSingular, reducciones[anchoDeBloque][altoDeBloque]);
              
              // Marca el elemento actual como encontrado
              encontrados[matriz[y][x]] = true;
            }// if encontrados
            break;// break del default
        }//switch 
      }//x
    }//y
  }


void imprimirBloques() {
    for (unsigned int i = 0; i < LIMITE_DE_UNSIGNED_CHAR; i++) {
      if (this->bloques[i].getID() != 0) {
        //se castea para poder imprimir el caracter del ID del bloque
        cout << "Bloque " << (char)this->bloques[i].getID() << "(" << this->bloques[i].getX() << " "
             << this->bloques[i].getY() << " " << this->bloques[i].getAncho() << " " << this->bloques[i].getAlto()
             << ") " << this->bloques[i].puedeMoverse(PIEZA_PUERTA) << endl;
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
    clrscr();
    for(unsigned int i = 0; i < getAltoTablero(); i++){
      for(unsigned int j = 0; j < getAnchoTablero(); j++){
        gotoxy(getmaxX()/2 - getAnchoTablero()/2 + j, getmaxY()/2 -  getAltoTablero()/2 + i);

        switch (this->tableroDeJuego[i][j]){
          case '&': cout <<                             "░"; break;//vacio
          case '-': cout <<                             "║"; break;//puerta
          case '*': cout << BG_RED                   << "⋆"; break;//pieza singular
          case '#': cout << FG_BLUE                  << "█"; break;//pared
          case '.': cout << FG_RED                   << "▓"; break;//objetivo
          case 'a': cout << BG_YELLOW  << FG_BLACK   << "a"; break;
          case 'b': cout << BG_MAGENTA << FG_BLACK   << "b"; break;
          case 'c': cout << BG_CYAN    << FG_BLACK   << "c"; break;
          case 'd': cout << BG_GREEN   << FG_BLACK   << "d"; break;
          case 'e': cout << BG_BLACK   << FG_WHITE   << "e"; break;
          case 'f': cout << BG_WHITE   << FG_BLACK   << "f"; break;
          case 'g': cout << BG_YELLOW  << FG_RED     << "g"; break;
          case 'h': cout << BG_MAGENTA << FG_CYAN    << "h"; break;
          case 'i': cout << BG_CYAN    << FG_YELLOW  << "i"; break;
          case 'j': cout << BG_GREEN   << FG_MAGENTA << "j"; break;
          case 'k': cout << BG_BLACK   << FG_GREEN   << "k"; break;
          case 'l': cout << BG_WHITE   << FG_YELLOW  << "l"; break;
          case 'm': cout << BG_YELLOW  << FG_WHITE   << "m"; break;
          case 'n': cout << BG_MAGENTA << FG_RED     << "n"; break;
          case 'o': cout << BG_CYAN    << FG_MAGENTA << "o"; break;
          case 'p': cout << BG_GREEN   << FG_WHITE   << "p"; break;
          case 'q': cout << BG_BLACK   << FG_YELLOW  << "q"; break;
          case 'r': cout << BG_WHITE   << FG_MAGENTA << "r"; break;
          case 's': cout << BG_YELLOW  << FG_GREEN   << "s"; break;
          case 't': cout << BG_MAGENTA << FG_CYAN    << "t"; break;
          case 'u': cout << BG_CYAN    << FG_RED     << "u"; break;
          case 'v': cout << BG_GREEN   << FG_CYAN    << "v"; break;
          case 'w': cout << BG_BLACK   << FG_GREEN   << "w"; break;
          case 'x': cout << BG_WHITE   << FG_MAGENTA << "x"; break;
          case 'y': cout << BG_YELLOW  << FG_GREEN   << "y"; break;
          case 'z': cout << BG_MAGENTA << FG_YELLOW  << "z"; break;
          default:  cout << this->tableroDeJuego[i][j];      break; 
        }//switch
        cout<<RESET_COLOR;
        fflush(stdout);
      }//x
      //cout << endl;
    }//y
  }//printTabla



bool bloquePuedeMorverse(Direccion dir, char IDdelBloque) {
// Función que verifica si un bloque puede moverse en una dirección específica
// Retorna true si el bloque puede moverse en la dirección especificada, false en caso contrario

  // Obtener una referencia al objeto Bloque correspondiente al ID proporcionado
  Bloque& bloqueObjetivo = bloques[IDdelBloque];

  // Evaluar la dirección y verificar si el bloque puede moverse en esa dirección
  switch (dir) {
    case ARRIBA:
      // Verificar si el bloque está en la fila superior del tablero
      if (bloqueObjetivo.getY() == 0){ return false; }

      // Verificar si el bloque puede moverse en cada celda de la fila superior
      for (unsigned int x = bloqueObjetivo.getX(); x < bloqueObjetivo.getX() + bloqueObjetivo.getAncho(); x++) {
        // Ignorar celdas fuera de los límites del tablero
        if (!(0 <= x && x < getAnchoTablero())){
          continue; //aqui continue es para que no se salga del for y continue con el siguiente bloque
        }

        // Verificar si el bloque puede moverse en la celda actual
        if (!bloqueObjetivo.puedeMoverse(this->tableroDeJuego[bloqueObjetivo.getY() - 1][x])) {
          return false;
        }
      }
      // Si el bloque puede moverse en todas las celdas de la fila superior, entonces puede moverse en la dirección especificada
      return true;
      break;//implicito por el return

    case ABAJO:
      // Verificar si el bloque está en la última fila del tablero
      if (bloqueObjetivo.getY() + bloqueObjetivo.getAlto() > getAltoTablero() - 1){ return false; }

      // Verificar si el bloque puede moverse en cada celda de la fila inferior
      for (unsigned int x = bloqueObjetivo.getX(); x < bloqueObjetivo.getX() + bloqueObjetivo.getAncho(); x++) {
        // Ignorar celdas fuera de los límites del tablero
        if (!(0 <= x && x < getAnchoTablero())){
          continue; //aqui continue es para que no se salga del for y continue con el siguiente bloque
        }

        // Verificar si el bloque puede moverse en la celda actual
        if (!bloqueObjetivo.puedeMoverse(this->tableroDeJuego[bloqueObjetivo.getY() + bloqueObjetivo.getAlto()][x])) {
          return false;
        }
      }
      return true;
      break;//implicito por el return

    case IZQUIERDA:
      // Verificar si el bloque está en la primera columna del tablero
      if (bloqueObjetivo.getX() == 0){ return false;}

      // Verificar si el bloque puede moverse en cada celda de la columna izquierda
      for (unsigned int y = bloqueObjetivo.getY(); y < bloqueObjetivo.getY() + bloqueObjetivo.getAlto(); y++) {
        // Ignorar celdas fuera de los límites del tablero
        if (!(0 <= y && y < getAltoTablero())){
          continue; //aqui continue es para que no se salga del for y continue con el siguiente bloque
        }

        // Verificar si el bloque puede moverse en la celda actual
        if (!bloqueObjetivo.puedeMoverse(this->tableroDeJuego[y][bloqueObjetivo.getX() - 1])) {
          return false;
        }
      }
      return true;
      break;//implicito por el return

    case DERECHA:
      // Verificar si el bloque está en la última columna del tablero
      if (bloqueObjetivo.getX() + bloqueObjetivo.getAncho() > getAnchoTablero() - 1){ return false;}

      // Verificar si el bloque puede moverse en cada celda de la columna derecha
      for (unsigned int y = bloqueObjetivo.getY(); y < bloqueObjetivo.getY() + bloqueObjetivo.getAlto(); y++) {
        // Ignorar celdas fuera de los límites del tablero
        if (!(0 <= y && y < getAltoTablero())){
          continue; //aqui continue es para que no se salga del for y continue con el siguiente bloque
        }

        // Verificar si el bloque puede moverse en la celda actual
        if (!bloqueObjetivo.puedeMoverse(this->tableroDeJuego[y][bloqueObjetivo.getX() + bloqueObjetivo.getAncho()])) {
          return false;
        }
      }
      return true;
      break;//implicito por el return
  }

  // Valor por defecto si la dirección no es válida
  return false;
}

  void moverBloque(Direccion dir, char IDdelBloque){
    Bloque& bloqueObjetivo = bloques[IDdelBloque];

    switch(dir){
      case ARRIBA:
        for(unsigned int x = bloqueObjetivo.getX(); x < bloqueObjetivo.getX() + bloqueObjetivo.getAncho(); x++){
          // con cada ciclo se mueve el bloque en la direccion ARRIBA
          // se mueve el bloque en el tablero de juego
          this->tableroDeJuego[bloqueObjetivo.getY() - 1][x] = IDdelBloque; 
          // se restaura conforme al tablero base 
          this->tableroDeJuego[bloqueObjetivo.getY() + bloqueObjetivo.getAlto() - 1][x] = this->baseDeltablero[bloqueObjetivo.getY()+bloqueObjetivo.getAlto()-1][x];
        }
        break;
      case ABAJO:
        for(unsigned int x = bloqueObjetivo.getX(); x < bloqueObjetivo.getX() + bloqueObjetivo.getAncho(); x++){
          // con cada ciclo se mueve el bloque en la direccion ABAJO
          // se mueve el bloque en el tablero de juego
          this->tableroDeJuego[bloqueObjetivo.getY() + bloqueObjetivo.getAlto()][x] = IDdelBloque;          
          // se restaura conforme al tablero base 
          this->tableroDeJuego[bloqueObjetivo.getY()][x] = this->baseDeltablero[bloqueObjetivo.getY()][x];
        }
        break;
      case IZQUIERDA:
        for(unsigned int y = bloqueObjetivo.getY(); y < bloqueObjetivo.getY() + bloqueObjetivo.getAlto(); y++){
          // con cada ciclo se mueve el bloque en la direccion IZQUIERDA
          // se mueve el bloque en el tablero de juego
          this->tableroDeJuego[y][bloqueObjetivo.getX() - 1] = IDdelBloque;
          // se restaura conforme al tablero base 
          this->tableroDeJuego[y][bloqueObjetivo.getX() + bloqueObjetivo.getAncho() - 1] = this->baseDeltablero[y][bloqueObjetivo.getX()+bloqueObjetivo.getAncho()-1];
        }
        break;
      case DERECHA:
        for(unsigned int y = bloqueObjetivo.getY(); y < bloqueObjetivo.getY() + bloqueObjetivo.getAlto(); y++){
          // con cada ciclo se mueve el bloque en la direccion DERECHA
          // se mueve el bloque en el tablero de juego
          this->tableroDeJuego[y][bloqueObjetivo.getX() + bloqueObjetivo.getAncho()] = IDdelBloque;
          // se restaura conforme al tablero base 
          this->tableroDeJuego[y][bloqueObjetivo.getX()] = this->baseDeltablero[y][bloqueObjetivo.getX()];
        }
        break;
    }
    // se mueve el bloque en el tablero de juego
    bloqueObjetivo.mover(dir);
  }

  bool juegoGanado(){
    // logica para saber si se ha ganado el juego
    for(auto& fila : this->tableroDeJuego){  
      for(auto& pieza : fila){
        // recorrido de la matriz
        // si hay una pieza que no sea la pieza objetivo, entonces no se ha ganado
        if(pieza == PIEZA_OBJETIVO) return false;
      }
    }
    // si no se encontro ninguna pieza que no sea la pieza objetivo, entonces es la pieza objetivo
    return true;
  }

};// Clase Tabla

class Solucion{
  public:
  TipoDeSolucion estado;
  unsigned int profundidad;
  unsigned int ultimoHash;
  OrdenDeMovimiento movimiento;
};

class Klotski{
  // clase principal para la solucion del tablero, amigo de clase Tabla

private:

  // memoria es una tabla de hash para almacenar información relacionada con cada estado del juego.
  // evitar la exploración repetida de los mismos estados durante la búsqueda de la solución
  unordered_map<unsigned int, Solucion> memoria;
  unsigned int profundidad = 0; // profundidad de la solucion
  Tabla tablaSolucion; // tabla del juego modificada en la ejecucion del programa
  const Tabla tablaOriginal; // tabla original del juego (copia de seguridad)

public:


  Klotski(Tabla tablaSolucion) : tablaSolucion(tablaSolucion), tablaOriginal(tablaSolucion) {}//constructor

 
  void printMovimientosSolucion(unsigned int estadoDelHash){
    
    // se obtiene la profundidad de la solucion
    unsigned int profundidadDestino = this->memoria.at(estadoDelHash).profundidad;

    // para imprimir las tablas de la solucion 
    Tabla tablaSolucionFinal = this->tablaOriginal;

    // se crea una pila (stack) para almacenar los movimientos de la solucion
    stack<OrdenDeMovimiento*> movimientosSolucion;//ocupa estructura LIFO 

    unsigned int contadorDeProfundidad = 0;

    // se obtiene el ultimo hash de la solucion
    Solucion* solucionActual = &this->memoria.at(estadoDelHash);

    // se recorre la memoria desde el ultimo hash hasta el hash inicial
    while(solucionActual->ultimoHash != 0){
      contadorDeProfundidad++;

      //cout << "\r" << contadorDeProfundidad << "/" << profundidadDestino;//para debuguear

      // se agrega el movimiento actual a la pila (stack)
      movimientosSolucion.push(&solucionActual->movimiento);
      // se obtiene el hash anterior
      solucionActual = &this->memoria.at(solucionActual->ultimoHash);
    }

    // se agrega el ultimo movimiento a la pila (stack)
    movimientosSolucion.push(&solucionActual->movimiento);

    unsigned int contadorDePasos = 0;// similar a contadorDeProfundidad pero para los pasos de la  pila (stack)

    while(movimientosSolucion.size()){// imprime la pila (stack) de movimientos
      // se obtiene el movimiento a realizar
      OrdenDeMovimiento* movimientoArealizar = movimientosSolucion.top();
      // se elimina el movimiento de la pila (stack)
      movimientosSolucion.pop();

      //if(tablaSolucionFinal.bloquePuedeMorverse((Direccion)movimientoArealizar->dir,(char)movimientoArealizar->id)){
      
      // se imprime la tabla con respecto al movimiento del stack 
      tablaSolucionFinal.moverBloque((Direccion)movimientoArealizar->dir,(char)movimientoArealizar->id);
      
      tablaSolucionFinal.printTabla();/*podria tener polimorfismo*/
      
      //para gotoxy
      unsigned int y=1;
      // se imprime el movimiento

      gotoxy(getmaxX()/2 - tablaSolucionFinal.getAnchoTablero()/2 , getmaxY()/2 + tablaSolucionFinal.getAltoTablero()/2 + y++);
      cout << "Movida la pieza: " << (char)movimientoArealizar->id << " ";//se castea a char para imprimir el caracter
      gotoxy(getmaxX()/2 - tablaSolucionFinal.getAnchoTablero()/2 , getmaxY()/2 + tablaSolucionFinal.getAltoTablero()/2 + y++);
      cout << "Hacia la direccion:" << stringDireccion((Direccion)movimientoArealizar->dir) ; //se castea a Direccion para imprimir la Direccion
      gotoxy(getmaxX()/2 - tablaSolucionFinal.getAnchoTablero()/2 , getmaxY()/2 + tablaSolucionFinal.getAltoTablero()/2 + y++);
      cout << "Paso numero: " <<contadorDePasos++;
      gotoxy(0,0);
      delay(contadorDePasos/100);//gradualmente desaselera
      //}//bloque si se puede mover porque es la solucion, implicito
    }
  }


unsigned int solucionador() { //funcion principal para encontrar la solucion

    // Se obtiene el hash inicial del estado del tablero de la solución
    unsigned int estadoInicial = std::hash<vector<vector<char>>>()(this->tablaSolucion.tableroDeJuego, this->tablaSolucion.bloques);
    
    // Se inicializa la memoria con el estado inicial y se marca como en progreso
    this->memoria[estadoInicial] = Solucion{EN_PROGRESO, 0, 0, {ARRIBA, 0}};

    // Se inicializa el último hash con el estado inicial
    unsigned int ultimoHash = 0;

    // Se inicializa el último orden con un movimiento nulo
    OrdenDeMovimiento ultimoOrden;
    
    // Llama a la función recursiva para buscar la solución
    return buscarSolucion(ultimoHash, ultimoOrden);
}

unsigned int buscarSolucion(unsigned int& ultimoHash, OrdenDeMovimiento& ultimoOrden) {//funcion recursiva usando DFS y Backtracking para encontrar la solucion
   recursion: //directiva de recursion para evitar segmentation fault
   if(this->profundidad>=LIMITE_DE_PROFUNDIDAD){
    return 0;// no hay solucion
   }
    this->profundidad++; // Aumenta la profundidad por cada llamada recursiva (inicia en 1)

    // Recorre todas las piezas en el tablero
    for (unsigned char i = PIEZA_SINGULAR; i != PIEZA_PARED ; i = (i + 1) % LIMITE_DE_UNSIGNED_CHAR) {//se usa unsigned char para evitar overflow
        
        // Verifica si la pieza actual existe
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

                #ifdef DEBUG_LINUX
                cout << "Profundidad: (" << this->profundidad << "), " << " movido '" << (char)i << "' " << stringDireccion(dir) << ", hashMovido -> " << hashMovido << "\n";
                this->tablaSolucion.printTabla();
                cout << "-----------------------------------------------------------------------\n";
                #endif

                // Verifica si se ha alcanzado la solución
                if (i == PIEZA_SINGULAR && this->tablaSolucion.juegoGanado()) {
                    this->memoria[hashMovido] = Solucion{SOLUCION_ENCONTRADA, this->profundidad, ultimoHash, {dir, i}};
                    return hashMovido;
                }

                // Verifica si ya se ha explorado este estado antes
                if (this->memoria.find(hashMovido) != this->memoria.end()) {
                    this->profundidad--;
                    this->tablaSolucion.moverBloque(direccionOpuesta(dir), i);
                    continue;
                } else {
                    // Almacena el nuevo estado en la memoria
                    this->memoria[hashMovido] = {EN_PROGRESO, this->profundidad, ultimoHash, ultimoOrden};
                }
                // Actualiza el último hash con el nuevo estado
                ultimoHash = hashMovido;

                // Actualiza el último hash con el nuevo estado
                //return buscarSolucion(ultimoHash, ultimoOrden);
                goto recursion;
            }
        }
    }

    /*Backtracking*/
    // Si no se encuentra una solución desde este estado, se retrocede

    // Verifica si existe el estado
    if (this->memoria.find(ultimoHash) != this->memoria.end()) {
      /*esto evita el error: terminate called after throwing an instance of 'std::out_of_range'
        what():  unordered_map::at
        Aborted (core dumped)*/

    // Si no es el estado inicial, se retrocede al estado anterior
    Solucion& revertirEstado = this->memoria.at(ultimoHash);

    // Se actualiza la profundidad
    //Solucion& revertirUltimaAccion = this->memoria.at(this->memoria.at(ultimoHash).ultimoHash);
    Solucion& revertirUltimaAccion = this->memoria.at(ultimoHash);
    
    this->profundidad = revertirUltimaAccion.profundidad;

    // Se revierte el último movimiento
    this->tablaSolucion.moverBloque(direccionOpuesta(revertirEstado.movimiento.dir), revertirEstado.movimiento.id);

    // Se imprime el Backtracking
    #ifdef DEBUG_LINUX
    cout << "BACKTRACKING: Profundidad: (" << this->profundidad << "), " << " moviendo '" << (char)revertirUltimaAccion.movimiento.id << "' " << stringDireccion(revertirUltimaAccion.movimiento.dir) << "\n";
    this->tablaSolucion.printTabla();
    #endif

    ultimoHash = revertirEstado.ultimoHash;

    // Llama recursivamente para explorar desde el estado anterior
    //return buscarSolucion(ultimoHash, ultimoOrden);
    goto recursion;
    }
  //si no se encuentra el estado no hay solucion
  return 0;
}

};//klotski


unsigned int validarEntradaInt(){
//funcion auxiliar para validar entrada de numeros
bool esValido = true; //bandera para validar entrada en el do while
string entrada; //entrada del usuario
  do {
    esValido = true;
    entrada.clear(); //se limpia la entrada
      //para capturar incluso espacios
      reset_shell_mode();cout<<CURSOR_ON;
      getline(cin,entrada);
      reset_prog_mode();cout<<CURSOR_OFF; 
      //solo se dio enter = error
      if(entrada.length()<1){
        esValido=false;
        cout<<"Error: Ingrese un número"<<endl;
      }
      for (char c : entrada) {
        if (!isdigit(c)) {//si no es un numero
          esValido = false;
          cout << "Error: Ingresa solo números" << endl;
          break; // Si se encuentra un carácter no numérico, salir del bucle
        }
      }
    }while (!esValido);//mientras no sea valido se pide por mas numeros
return std::stoi(entrada);//se convierte a int
}

void recuadro(){
#if defined(_WIN32)
gotoxy(0,0);cout<<"█";
#endif
unsigned int x=getmaxX(),j=0;
unsigned int y=getmaxY(),i=0;

  while(i<=getmaxY()){
    gotoxy(x,y);cout<<"█";
    gotoxy(0,y--);cout<<"█";
    i++;
  }
  y=getmaxY();
  while(j<=getmaxX()){
    gotoxy(x,y);cout<<"█";
    gotoxy(x--,0);cout<<"█";
    j++;
  }

cout<<RESET_COLOR;fflush(stdout);
}
int main(){
 startCompat();//para mostrar caracteres UTF8 en Windows
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
    cout << "Ingrese el número N para el archivo nivel_N.txt: ";
    unsigned int N=validarEntradaInt();
    Nivel nivel(N);
      if(!nivel.cargarNivel()){
        cout << "Error: No se pudo abrir el archivo " << nivel.getNombreArchivo() << endl;
      }else{
        
        /*cout<< "Nombre del Nivel: "<< nivel.getNombreNivel() <<endl;
        cout << "Tabla del archivo" << nivel.getNombreArchivo() << endl;
        cout << "getAnchoNivel " << nivel.getAnchoNivel() << endl;
        cout << "getAltoNivel " << nivel.getAltoNivel() << endl;*/
        vector<string> matriz3 = nivel.getTableroNivel();
        Tabla tablaSolucion = Tabla(matriz3);
        
        tablaSolucion.printTabla();

        //tablaSolucion.imprimirBloques();

        tablaSolucion.printTabla();
        Klotski klotski = (tablaSolucion);
        unsigned int solucion = klotski.solucionador();

          if(solucion==0){
           clrscr();
           gotoxy(getmaxX()/2 - 15/2 ,getmaxY()/2 );
           cout<<"no hay solucion";
           cout <<FG_RED;recuadro();
           cin.get();
          }else{
            cout << "Solucion Encontrada\n";
            klotski.printMovimientosSolucion(solucion);//pasos para la solucion
          }

        
  
        }//nivel cargado
    endCompat();
  return 0;
}
