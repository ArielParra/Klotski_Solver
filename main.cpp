#include "Nivel.cpp"
//#include "compatibilidad.h"

using std::cin;
using std::cerr;

int main() {
//    setUTF8();

    int N;
    cout << "Ingrese el número N para el archivo nivel_N.txt: ";
    cin >> N;

    Nivel nivel(N);
    if(!nivel.cargarNivel()){
        cerr << "Error: No se pudo abrir el archivo " << nivel.getNombreArchivo() << endl;
    }else{
        cout << "Tabla del archivo" << nivel.getNombreArchivo() << endl;
        cout<< "Nombre del Nivel: "<< nivel.getNombreNivel() <<endl;
        nivel.getTablero().mostrarTabla();
    }

    vector<string> matriz = {
        "&&&&&&&&&&",
        "&&&&&&&&&&",
        "&&######&&",
        "&&#a**b#&&",
        "&&#a**b#&&",
        "&&#cdde#&&",
        "&&#cfge#&&",
        "&&#a&&b#&&",
        "&&##--##&&",
        "&&&&&&&&..",
        "&&&&&&&&.."
    };
    Tabla tablero(matriz);
    tablero.cambiarRepetidos();
    
    cout << endl <<  "Tabla del tipo Tabla:" << endl;
    tablero.mostrarTabla();
    return 0;
}
