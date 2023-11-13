#include "Nivel.h"
#include <iostream>
#include <limits> // para limitar la captura de renglones

using std::cerr;
using std::to_string;
using std::numeric_limits;
using std::streamsize;

Nivel::Nivel() : numNivel(0), ancho(0), altura(0) {}// constructor vacio

Nivel::Nivel(unsigned int num) : numNivel(num), nombreArchivo("nivel_" + to_string(num) + ".txt") {}// constructor 

/*Private*/
void Nivel::leerNombreNivel(ifstream& archivo) {// primera linea
    string nombreNivel;
    getline(archivo, nombreNivel);
    nombreNivel = nombreNivel.substr(0, 40);
    cout << "Nombre del nivel: " << nombreNivel << endl;
}

void Nivel::leerDimensionesTablero(ifstream& archivo) {// segunda linea
    archivo >> ancho >> altura;
    cout << "Ancho del tablero: " << ancho << endl;
    cout << "Altura del tablero: " << altura << endl;
    archivo.ignore(numeric_limits<streamsize>::max(), '\n');// Ignora el resto de la línea
    tablero = Tabla(ancho, altura);
}

void Nivel::leerTablero(ifstream& archivo) {// tercera linea en adelante
    for (unsigned int i = 0; i < altura; ++i) {
        string fila;
        getline(archivo, fila);
        tablero.cargarFila(i, fila);
    }
}

/*Public*/
void Nivel::cargarNivel() {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    leerNombreNivel(archivo);
    leerDimensionesTablero(archivo);
    leerTablero(archivo);

    archivo.close();
}

void Nivel::mostrarTablero() {
    tablero.mostrarTabla();
}
