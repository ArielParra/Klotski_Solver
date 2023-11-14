#include "Tabla.h"
#include <iostream>
#include <queue>

using std::cout;
using std::endl;

/*Public*/
Tabla::Tabla() : ancho(0), altura(0) {} // constructor vacio

Tabla::Tabla(unsigned int ancho, unsigned int altura)
    : ancho(ancho), altura(altura) { // constructor
  matriz.resize(altura,
                string(ancho, ' ')); // Inicializa la matriz con strings vacíos
}

/*Metodos get*/
unsigned int Tabla::getAncho() const { return this->ancho; }

unsigned int Tabla::getAltura() const { return this->altura; }

void Tabla::cargarFila(unsigned int fila, const string &datos) {
  this->matriz[fila] = datos.substr(0, ancho);
}

void Tabla::mostrarTabla() {
  cout << "Tabla:" << endl;
  for (unsigned int i = 0; i < Tabla::getAltura(); i++) {
    cout << matriz[i] << "| Fila " << i + 1 << endl;
  }
}

