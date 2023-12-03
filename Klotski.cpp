#include "Klotski.h"

//public:
Klotski::Klotski(){};//constructor vacio

Klotski::Klotski(Tabla tablaSolucion) : tablaSolucion(tablaSolucion), tablaOriginal(tablaSolucion) {}//constructor  

  
void Klotski::printMovimientosSolucion(unsigned int estadoDelHash, string nombreNivel){
  
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
    
    gotoxy(getmaxX()/2 - nombreNivel.size()/2, getmaxY()/2 - tablaSolucionFinal.getAltoTablero()/2 - 2);
    cout<<nombreNivel;
    gotoxy(0,0);

    tablaSolucionFinal.printTabla();/*podria tener polimorfismo*/
    
    //para gotoxy
    unsigned int y=2;
    #if defined(_WIN32) || defined(_CYGWIN_) 
      unsigned int milisegundos=0;
    #else
      unsigned int milisegundos=5;
    #endif
    // se imprime el movimiento

    gotoxy(getmaxX()/2 - tablaSolucionFinal.getAnchoTablero() , getmaxY()/2 + tablaSolucionFinal.getAltoTablero()/2 + y++);
    cout << "Movida la pieza: '" << (char)movimientoArealizar->id << "'";//se castea a char para imprimir el caracter
    gotoxy(getmaxX()/2 - tablaSolucionFinal.getAnchoTablero() , getmaxY()/2 + tablaSolucionFinal.getAltoTablero()/2 + y++);
    cout << "Hacia la direccion: " << stringDireccion((Direccion)movimientoArealizar->dir) ; //se castea a Direccion para imprimir la Direccion
    gotoxy(getmaxX()/2 - tablaSolucionFinal.getAnchoTablero() , getmaxY()/2 + tablaSolucionFinal.getAltoTablero()/2 + y++);
    cout << "Paso numero: " << setw(4) << contadorDePasos++  << " / " <<  contadorDeProfundidad;
    
    if(contadorDePasos>=contadorDeProfundidad * 0.7){//cuando llega al 70% de la solucion imprime más lento
      #if defined(_WIN32) || defined(_CYGWIN_) 
        milisegundos=0;
      #else
        milisegundos=50;
      #endif   
    }
    /*
    //para ver que funcione la regla de pausas
    gotoxy(getmaxX()/2 - tablaSolucionFinal.getAnchoTablero() , getmaxY()/2 + tablaSolucionFinal.getAltoTablero()/2 + y++);
    cout << "Pausas de: "<< milisegundos << " ms";
    */
    fflush(stdout);
    delay(milisegundos);//para poder imprimir

    //}//bloque si se puede mover porque es la solucion, implicito
  }
}


unsigned int Klotski::solucionador() { 
//funcion principal para encontrar la solucion, esta inicializa variables 
//que son ncesarias para la funcion recursiva buscarSolucion

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

unsigned int Klotski::rotacionDeDireccion(unsigned int num) {
  // Incrementa el número
  num++;
  // Verifica si el número supera el límite superior (3)
  if (num > 3) {
    // Si es así, reinicia el número a 0
    num = 0;
  }
  // Retorna de 0 a 3 = 4 (direcciones)
  return num;
}

unsigned int Klotski::buscarSolucion(unsigned int& ultimoHash, OrdenDeMovimiento& ultimoOrden) {//funcion recursiva usando DFS y Backtracking para encontrar la solucion
  recursion://directiva de recursion para evitar segmentation fault
   if(this->profundidad>=LIMITE_DE_PROFUNDIDAD){
    // error: no se puede llegar al objetivo
    return 0;// no hay solucion
   }
    this->profundidad++; // Aumenta la profundidad por cada llamada recursiva (inicia en 1)

    // Recorre todas las piezas en el tablero
    for (char i = PIEZA_SINGULAR; i != PIEZA_PARED ; i = (i + 1) % LIMITE_DE_CHAR ) {//se usa char para evitar overflow
      
      // Verifica si la pieza actual existe
      if (this->tablaSolucion.bloques[i].getID() == 0) continue;

      // Selecciona una dirección inicial seudo alotoria pero constante
      //unsigned int direccionInicial = rand() % 4;

      // Recorre las direcciones posibles
      for (unsigned int j = 0; j < 4; j++) {
        //Direccion dir = static_cast<Direccion>((direccionInicial + j) % 4); //con numero seaudo aleatorio constante
        Direccion dir = static_cast<Direccion>((rotacionDeDireccion(j)) % 4); //con rotacion deterministica de 0 a 3

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
          //return buscarSolucion(ultimoHash, ultimoOrden);//crea segmentation fault si no hay solucion
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
  //return buscarSolucion(ultimoHash, ultimoOrden);//crea segmentation fault si no hay solucion
  goto recursion;
  }//verifica si existe el estado

// si no se encuentra el estado no hay solucion
// error: no se pueden mover las piezas
return 0;
}

