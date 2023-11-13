#include "Tabla.h"
#include <iostream>

using std::cout;
using std::endl;

Tabla::Tabla() : ancho(0), altura(0) {}// constructor vacio

Tabla::Tabla(unsigned int ancho, unsigned int altura) : ancho(ancho), altura(altura) {// constructor 
    matriz.resize(altura, string(ancho, ' '));// Inicializa la matriz con strings vacíos
}

void Tabla::cargarFila(unsigned int fila, const string& datos) {
    matriz[fila] = datos.substr(0, ancho);
}

void Tabla::mostrarTabla() {
    cout << "Tabla:" << endl;
    for (unsigned int i = 0; i < altura; ++i) {
        cout << matriz[i] << "| Fila " << i + 1 << endl;
    }
}
