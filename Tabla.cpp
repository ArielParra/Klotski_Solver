#include "Tabla.h"
// public:
Tabla::Tabla(){}///constructor vacio
  
 Tabla::Tabla(vector<string>& matriz) :
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


void Tabla::imprimirBloques() {
    for (unsigned int i = 0; i < LIMITE_DE_UNSIGNED_CHAR; i++) {
      if (this->bloques[i].getID() != 0) {
        //se castea para poder imprimir el caracter del ID del bloque
        cout << "Bloque " << (char)this->bloques[i].getID() << "(" << this->bloques[i].getX() << " "
             << this->bloques[i].getY() << " " << this->bloques[i].getAncho() << " " << this->bloques[i].getAlto()
             << ") " << this->bloques[i].puedeMoverse(PIEZA_PUERTA) << std::endl;
      }
    }
  }


  Bloque* Tabla::getBloques(){
    return this->bloques;
  }
  unsigned int Tabla::getAltoTablero() const{
    return this->tableroDeJuego.size();
  }

  unsigned int Tabla::getAnchoTablero() const{
    return this->tableroDeJuego[0].size();
  }

  void Tabla::printTabla() const {
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
      //cout << std::endl;
    }//y
  }//printTabla



bool Tabla::bloquePuedeMorverse(Direccion dir, char IDdelBloque) {
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

  void Tabla::moverBloque(Direccion dir, char IDdelBloque){
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

  bool Tabla::juegoGanado(){
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
