#ifndef Tabla_h
#define Tabla_h

#include <string>
#include <vector>

using std::string;
using std::vector;

class Tabla {
private:
  unsigned int ancho;
  unsigned int altura;
  vector<string> matriz;

public:
  Tabla();
  Tabla(unsigned int ancho, unsigned int altura);
  Tabla(const vector<string>& matriz);
  unsigned int getAncho() const;
  unsigned int getAltura() const;
  vector<string>& getMatriz();
  const vector<string>& getMatriz() const;
  void cargarFila(unsigned int fila, const string &datos);
  void mostrarTabla();
  void cambiarRepetidos();
};

#endif // Tabla_h
