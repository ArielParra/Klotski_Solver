#include "Klotski.h"

//public:
Klotski::Klotski(){};//constructor vacio

Klotski::Klotski(Tabla tablaSolucion) : tablaSolucion(tablaSolucion), tablaOriginal(tablaSolucion) {}//constructor  

  
void Klotski::printMovimientosSolucion(unsigned int estadoDelHash, string nombreNivel){
  // se obtiene la profundidad de la solucion
  unsigned int profundidadDestino = this->memoria.at(estadoDelHash).profundidad;

  char piezaAnterior = ' ';/* para cumplir que Cada pieza diferente que se mueve se considera un movimiento.
  Al mover una pieza que acaba de ser movida se considera que es una continuación del movimiento anterior, y no cuenta como movimiento.*/

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

    // Si la pieza es diferente de la anterior, incrementa el contador de profundidad
    if ((char)solucionActual->movimiento.id != piezaAnterior) {
      contadorDeProfundidad++;
      piezaAnterior = solucionActual->movimiento.id;  // Actualiza la pieza anterior
    }
  }// while de captura de pasos

  if(contadorDeProfundidad==0){contadorDeProfundidad++;}//por si ocupa un solo paso

  // se agrega el ultimo movimiento a la pila (stack)
  movimientosSolucion.push(&solucionActual->movimiento);

  unsigned int contadorDePasos = 0;// similar a contadorDeProfundidad pero para los pasos de la  pila (stack)

  piezaAnterior = ' '; 

  /*para: Al final deberá indicar cuantos movimientos realizo para solucionar el reto, así como el camino recorrido para la solución*/
  vector <string> caminoRecorrido; //implicito al mostrar pasos en ejecucion

  while(movimientosSolucion.size()){// imprime la pila (stack) de movimientos

    // se obtiene el movimiento a realizar
    OrdenDeMovimiento* movimientoArealizar = movimientosSolucion.top();

    // se elimina el movimiento de la pila (stack)
    movimientosSolucion.pop();
    
    // se imprime la tabla con respecto al movimiento del stack 
    tablaSolucionFinal.moverBloque((Direccion)movimientoArealizar->dir,(char)movimientoArealizar->id);

    // Si la pieza es diferente de la anterior, incrementa el contador de profundidad
    if ((char)movimientoArealizar->id != piezaAnterior) {
      contadorDePasos++;
      piezaAnterior = (char)movimientoArealizar->id;  // Actualiza la última pieza movida
    }

    gotoxy(getmaxX()/2 - nombreNivel.size()/2, getmaxY()/2 - tablaSolucionFinal.getAltoTablero()/2 - 2);
    cout<<nombreNivel;

    tablaSolucionFinal.printTabla();string movidaLaPieza,haciaDireccion, pasoNumero;
    
    //para gotoxy
    unsigned int y=2;

    #if defined(_WIN32) || defined(_CYGWIN_) 
      unsigned int milisegundos=50;//windows es lento, no ocupa tanto delay
    #else
      unsigned int milisegundos=100;
    #endif

    // se imprime el movimiento
    movidaLaPieza ="Movida la pieza: '" + string(1, (char)movimientoArealizar->id)  + "'";//se castea a char para imprimir el caracter
    caminoRecorrido.push_back(movidaLaPieza);
    gotoxy(getmaxX()/2 - tablaSolucionFinal.getAnchoTablero() , getmaxY()/2 + tablaSolucionFinal.getAltoTablero()/2 + y++);
    cout<<movidaLaPieza;
    
    haciaDireccion ="Hacia la direccion: " + stringDireccion((Direccion)movimientoArealizar->dir) ; //se castea a Direccion para imprimir la Direccion
    caminoRecorrido.push_back(haciaDireccion);
    gotoxy(getmaxX()/2 - tablaSolucionFinal.getAnchoTablero() , getmaxY()/2 + tablaSolucionFinal.getAltoTablero()/2 + y++);
    cout<<haciaDireccion;
    
    pasoNumero = "Paso numero: " + to_string(contadorDePasos)  + " / " +  to_string(contadorDeProfundidad);
    caminoRecorrido.push_back(pasoNumero);
    gotoxy(getmaxX()/2 - tablaSolucionFinal.getAnchoTablero() , getmaxY()/2 + tablaSolucionFinal.getAltoTablero()/2 + y++);
    cout << "Paso numero: " << setw(4) << contadorDePasos  << " / " <<  contadorDeProfundidad;
    caminoRecorrido.push_back("\n");

    fflush(stdout);
    delay(milisegundos);//para poder imprimir

  }//while de impresion 
 
//DEBUG: imprimir vector mostrarcaminoRecorrido
 /*
  const string mostrarcaminoRecorrido="Presione Cualquier tecla para mostrar el camino recorrido";
  gotoxy(getmaxX()/2 - mostrarcaminoRecorrido.size()/2, getmaxY()/2 + tablaSolucion.getAltoTablero()/2 + 5 );
  cout<<FG_BLUE<<mostrarcaminoRecorrido<<RESET_COLOR;fflush(stdout);
  getch(); 
  clrscr();

  reset_shell_mode();
  for(unsigned int i=0;i<caminoRecorrido.size(); i++){
    cout<< caminoRecorrido[i]<<std::endl;
  }
  reset_prog_mode();
  */

  const string regresar="Presione Cualquier tecla para regresar";
  gotoxy(getmaxX()/2 - regresar.size()/2, getmaxY()/2 + tablaSolucion.getAltoTablero()/2 + 5 );
  cout<<FG_BLUE<<regresar<<RESET_COLOR;fflush(stdout);
  getch(); 
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
  // es unsigned int porque se usa el for con j que es unsigned int, solo se casteara

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
      const string error2="No se pudo llegar al objetivo en menos de "+to_string(LIMITE_DE_PROFUNDIDAD)+" pasos";
      cout<<FG_RED;
      mensajeCentrado(error2);
      return 0;
   }
    this->profundidad++; // Aumenta la profundidad por cada llamada recursiva 

    // Recorre el ASCII desde '*'(42) hasta 'z' (122) (rango de 80 caracteres)  despues se valida si la pieza existe
    for (char i = PIEZA_SINGULAR; i <='z' ; i++ ){ 
      
      // Verifica si la pieza actual existe  y filtra bloques que se trabajan
      if (this->tablaSolucion.bloques[i].getID() == 0) {
        continue; //si no existe el caracter en los bloques usables del tablero se continua la siguiente iteracion de piezas
      }


      // Selecciona una direccion inicial seudo aleatoria pero constante
      //                                 rand() %  (limteSUP - limiteINF + 1) + limiteINF
      //                                 rand() % (3 - 0 + 1) + 0 ;
      // unsigned int direccionInicial = rand() % 4;

      // Recorre las direcciones posibles en las 4 direcciones (ARRIBA,ABAJO,IZQUIERDA,DERECHA) 
      for (unsigned int j = 0; j < 4; j++) {
        //Direccion dir = static_cast<Direccion>((direccionInicial + j) % 4); // con numero seaudo aleatorio constante de 0 a
        Direccion dir = static_cast<Direccion>(rotacionDeDireccion(j)); // con rotacion deterministica de 0 a 3

        // Verifica si es posible mover la pieza en la dirección actual
        if (ultimoOrden != OrdenDeMovimiento{direccionOpuesta(dir), i} && this->tablaSolucion.bloquePuedeMorverse(dir, i)) {

        /* La función direccionOpuesta(dir) se utiliza para obtener la dirección opuesta a la direccion actual 'dir'.
          Esto se hace para comprobar si el último movimiento realizado (ultimoOrden) no es el opuesto al movimiento actual.
          Si es asi, esto significa que el movimiento actual simplemente esta deshaciendo el ultimo movimiento (es redundante).
          Por lo tanto, si el último movimiento es opuesto al movimiento actual, esta condición sera falsa y se omitira el movimiento actual.
          Si el ultimo movimiento no es el contrario, la condición verifica si la pieza actual se puede mover en la dirección actual.
          Si ambas condiciones son verdaderas, la pieza se mueve en la direccion actual.*/

          ultimoOrden = {dir, i}; // direccion y pieza movida 

          this->tablaSolucion.moverBloque(dir, i); // como si se puede mover debido a la segunda condicion del if anterior, se mueve

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

              // si ya se exploro se hace un Back Tracking simple

              // se regresa la profundidad en 1
              this->profundidad--;

              // regresa el movimiento
              this->tablaSolucion.moverBloque(direccionOpuesta(dir), i);

              continue; // for de las direcciones

          } else { // no se encontro = no se ha explorado

              // Almacena el nuevo estado en la memoria
              this->memoria[hashMovido] = Solucion{EN_PROGRESO, this->profundidad, ultimoHash, ultimoOrden};
          }

          // Actualiza el último hash con el nuevo estado
          ultimoHash = hashMovido;

          //return buscarSolucion(ultimoHash, ultimoOrden);//crea segmentation fault si no hay solucion
          goto recursion; //el goto evita segmentation fault cuando no hay solucion
        }// if es posible mover la pieza
      }// for de direciones
    }// for de piezas

  /*Back Tracking*/
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

  ultimoHash = revertirEstado.ultimoHash; //el ultimo hash sera el ultimoHash del backtracking

  // Llama recursivamente para explorar desde el estado anterior
  //return buscarSolucion(ultimoHash, ultimoOrden);//crea segmentation fault si no hay solucion
  goto recursion;
  }//verifica si existe el estado

// si no se encuentra el estado no hay solucion
const string error2="No Existe Solucion, no se pudo mover alguna pieza";
cout<<FG_RED;
mensajeCentrado(error2);
return 0;
}

