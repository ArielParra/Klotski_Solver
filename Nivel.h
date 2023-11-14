#ifndef Nivel_h
#define Nivel_h

#include "Tabla.cpp"
#include <fstream>

using std::ifstream;

class Nivel {
private:
  unsigned int numNivel;
  string nombreArchivo;
  string nombreNivel;
  Tabla tablero;

  void leerNombreNivel(ifstream &archivo);
  void leerDimensionesTablero(ifstream &archivo);
  void leerTablero(ifstream &archivo);

public:
  Nivel();
  Nivel(unsigned int num);
  bool cargarNivel();
  unsigned int getNumNivel() const;
  string getNombreArchivo() const;
  string getNombreNivel() const;
  Tabla getTablero() const;
};

#endif // Nivel_h
