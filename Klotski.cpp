#include "Klotski.h"

//public:

  Klotski::Klotski(Tabla tablaSolucion) : tablaSolucion(tablaSolucion), tablaOriginal(tablaSolucion) {}//constructor

  void Klotski::printMovimientosSolucion(unsigned int estadoDelHash){
    
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

      //cout << "\r" << contadorDeProfundidad << "/" << profundidadDestino;//para debuguear

      // se agrega el movimiento actual a la pila (stack)
      movimientosSolucion.push(&solucionActual->movimiento);
      // se obtiene el hash anterior
      solucionActual = &this->memoria.at(solucionActual->ultimoHash);
      // se aumenta el contador de profundidad
      contadorDeProfundidad++;
    }

    // se agrega el ultimo movimiento a la pila (stack)
    movimientosSolucion.push(&solucionActual->movimiento);

    unsigned int contadorDePasos = 0;// similar a contadorDeProfundidad pero para los pasos de la  pila (stack)

    while(movimientosSolucion.size()){// imprime la pila (stack) de movimientos
      // se obtiene el movimiento a realizar
      OrdenDeMovimiento* movimientoArealizar = movimientosSolucion.top();
      // se elimina el movimiento de la pila (stack)
      movimientosSolucion.pop();

      // se imprime la tabla con respecto al movimiento del stack 
      tablaSolucionFinal.moverBloque((Direccion)movimientoArealizar->dir,(char)movimientoArealizar->id);
      tablaSolucionFinal.printTabla();/*podria tener polimorfismo*/
      
      // se imprime el movimiento
      cout << "MOVIDO " << (char)movimientoArealizar->id << " ";//se castea a char para imprimir el caracter
      cout << stringDireccion((Direccion)movimientoArealizar->dir) ; //se castea a Direccion para imprimir la Direccion
      cout <<", paso numero: " <<contadorDePasos++ <<endl;
    }
  }

unsigned int Klotski::solucionador() { //funcion principal para encontrar la solucion

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

unsigned int Klotski::buscarSolucion(unsigned int& ultimoHash, OrdenDeMovimiento& ultimoOrden) {//funcion recursiva usando DFS y Backtracking para encontrar la solucion
   
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

                #ifdef PRINT_DEBUG_LINUX
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
                return buscarSolucion(ultimoHash, ultimoOrden);
            }
        }
    }

    /*Backtracking*/
    // Si no se encuentra una solución desde este estado, se retrocede

    // Verifica si existe el estado
    //if (this->memoria.find(ultimoHash) != this->memoria.end()) {

    // Si no es el estado inicial, se retrocede al estado anterior
    Solucion& revertirEstado = this->memoria.at(ultimoHash);

    // Se actualiza la profundidad
    Solucion& revertirUltimaAccion = this->memoria.at(this->memoria.at(ultimoHash).ultimoHash);
    this->profundidad = revertirUltimaAccion.profundidad;

    // Se revierte el último movimiento
    this->tablaSolucion.moverBloque(direccionOpuesta(revertirEstado.movimiento.dir), revertirEstado.movimiento.id);

    // Se imprime el Backtracking
    #ifdef PRINT_DEBUG_LINUX
    cout << "BACKTRACKING: Profundidad: (" << this->profundidad << "), " << " moviendo '" << (char)revertirUltimaAccion.movimiento.id << "' " << stringDireccion(revertirUltimaAccion.movimiento.dir) << "\n";
    this->tablaSolucion.printTabla();
    #endif

    ultimoHash = revertirEstado.ultimoHash;

    // Llama recursivamente para explorar desde el estado anterior
    return buscarSolucion(ultimoHash, ultimoOrden);
    //}
  //si no se encuentra el estado no hay solucion
  return 0;
}

