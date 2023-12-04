#pragma once //para que no de problemas de compilacion por inclusion multiple

#ifndef Klostki_h
#define Klostki_h

#include "Tabla.cpp"
#include "TiposDeDatos.h"
#include "FuncionesAuxiliares.h"

#include <iomanip>
using std::setw;

#include <stack>//pilas std
using std::stack;

#define LIMITE_DE_PROFUNDIDAD 1000000000  // limite de profundidad para evitar segmentation fault

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
    Klotski();//constructor vacio
    Klotski(Tabla tablaSolucion);//constructor
    void printMovimientosSolucion(unsigned int estadoDelHash, string nombreNivel);
    unsigned int solucionador() ;
    unsigned int buscarSolucion(unsigned int& ultimoHash, OrdenDeMovimiento& ultimoOrden);
    unsigned int rotacionDeDireccion(unsigned int num);

};//klotski

#endif // Klostki_h
