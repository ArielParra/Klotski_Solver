// Nivel.h
#ifndef Nivel_h
#define Nivel_h

#include "Tabla.cpp"
#include <fstream>

using std::ifstream;

class Nivel {
private:
    unsigned int numNivel;
    string nombreArchivo;
    unsigned int ancho;
    unsigned int altura;
    Tabla tablero;

    void leerNombreNivel(ifstream& archivo);
    void leerDimensionesTablero(ifstream& archivo);
    void leerTablero(ifstream& archivo);

public:
    Nivel();
    Nivel(unsigned int num);
    void cargarNivel();
    void mostrarTablero();
};

#endif // Nivel_h
