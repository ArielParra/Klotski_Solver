#ifndef Nivel_h
#define Nivel_h

#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::vector;
using std::string;


class Nivel {
private:
  unsigned int numNivel;
  string nombreArchivo;
  string nombreNivel;
  unsigned int ancho;
  unsigned int alto;
  vector<string> tableroNivel;
  bool NivelCargado;

  void leerNombreNivel(ifstream &archivo);
  bool leerDimensionesTablero(ifstream &archivo);
  void leerTablero(ifstream &archivo);

public:

  Nivel(unsigned int num);
  bool cargarNivel();
  unsigned int getNumNivel() const;
  string getNombreArchivo() const;
  string getNombreNivel() const;
  unsigned int getAnchoNivel();
  unsigned int getAltoNivel();
  vector<string> getTableroNivel();
  
};

#endif // Nivel_h
