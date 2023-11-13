#include "Nivel.cpp"
#include "compatibilidad.h"

using std::cin;

int main() {
    setUTF8();

    int N;
    cout << "Ingrese el número N para el archivo nivel_N.txt: ";
    cin >> N;

    Nivel nivel(N);
    nivel.cargarNivel();
    nivel.mostrarTablero();

    return 0;
}
