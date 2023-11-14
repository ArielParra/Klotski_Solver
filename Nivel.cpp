#include "Nivel.h"
#include <iostream>
#include <limits> // para limitar la captura de renglones

using std::numeric_limits;
using std::streamsize;
using std::to_string;

Nivel::Nivel() : numNivel(0) {} // constructor vacio

Nivel::Nivel(unsigned int num)
    : numNivel(num), nombreArchivo("nivel_" + to_string(num) + ".txt") {
} // constructor

/*Private*/
void Nivel::leerNombreNivel(ifstream &archivo) { // primera linea
  string nombreNivel;
  getline(archivo, nombreNivel);
  nombreNivel = nombreNivel.substr(0, 40);
}

void Nivel::leerDimensionesTablero(ifstream &archivo) { // segunda linea
  unsigned int ancho, altura;
  archivo >> ancho >> altura;
  cout << "Ancho del tablero: " << ancho << endl;
  cout << "Altura del tablero: " << altura << endl;
  archivo.ignore(numeric_limits<streamsize>::max(),
                 '\n'); // Ignora el resto de la línea
  tablero = Tabla(ancho, altura);
}

void Nivel::leerTablero(ifstream &archivo) { // tercera linea en adelante
  for (unsigned int i = 0; i < tablero.getAltura(); i++) {
    string fila;
    getline(archivo, fila);
    this->tablero.cargarFila(i, fila);
  }
}

/*Public*/
bool Nivel::cargarNivel() {
  ifstream archivo(nombreArchivo);

  if (!archivo.is_open()) {
    return false;
  }

  leerNombreNivel(archivo);
  leerDimensionesTablero(archivo);
  leerTablero(archivo);

  archivo.close();
  return true;
}

/*Metodos get*/
unsigned int Nivel::getNumNivel() const { return this->numNivel; }
string Nivel::getNombreArchivo() const { return this->nombreArchivo; }
Tabla Nivel::getTablero() const { return this->tablero; }

