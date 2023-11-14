#include "Nivel.cpp"
#include "compatibilidad.h"

using std::cin;
using std::cerr;

int main() {
    setUTF8();

    int N;
    cout << "Ingrese el número N para el archivo nivel_N.txt: ";
    cin >> N;

    Nivel nivel(N);
    if(!nivel.cargarNivel()){
        cerr << "Error: No se pudo abrir el archivo " << nivel.getNombreArchivo() << endl;
    }else{
        nivel.getTablero().mostrarTabla();
    }

    return 0;
}
