#ifndef Tabla_h
#define Tabla_h

#include <vector>
#include <string>

using std::vector;
using std::string;

class Tabla {
private:
    unsigned int ancho;
    unsigned int altura;
    vector<string> matriz;

public:
    Tabla();
    Tabla(unsigned int ancho, unsigned int altura);
    void cargarFila(unsigned int fila, const string& datos);
    void mostrarTabla();
};

#endif // Tabla_h
