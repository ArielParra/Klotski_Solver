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
  unsigned int getAncho() const;
  unsigned int getAltura() const;
  const vector<string>& getMatriz() const;
  void setMatriz(const vector<string>& matriz); 
  void cargarFila(unsigned int fila, const string &datos);
  void mostrarTabla();
};

#endif // Tabla_h
