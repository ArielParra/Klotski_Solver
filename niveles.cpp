/*falta separar implementación
  falta implementar clase tabla*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

#include "compatibilidad.h"

using namespace std;

class Nivel {
private:
    unsigned int numNivel; 
    string nombreArchivo;
    unsigned int ancho; // numeros Naturales desde 1 hasta n, sin contar negativos ni el 0
    unsigned int altura;
    vector<string> tablero;


    void leerNombreNivel(ifstream& archivo) {
        string nombreNivel;
        getline(archivo, nombreNivel);

        nombreNivel = nombreNivel.substr(0, 40);  // Limitar a 40 caracteres
        cout << "Nombre del nivel: " << nombreNivel << endl;
    }

    void leerDimensionesTablero(ifstream& archivo) {
        archivo >> ancho >> altura;
        cout << "Ancho del tablero: " << ancho << endl;
        cout << "Altura del tablero: " << altura << endl;
        archivo.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea

        tablero.resize(altura);// cambia el tamaño del vector a la altura dada
    }

    void leerTablero(ifstream& archivo) {
        for (unsigned int i = 0; i < altura; ++i) {
            getline(archivo, tablero[i]);
            tablero[i] = tablero[i].substr(0, ancho);// solo toma el ancho dado lo demas se ignora
        }
    }

public:
    Nivel(int num) : numNivel(num), nombreArchivo("nivel_" + to_string(num) + ".txt") {} //constructor 

    void cargarNivel() {
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

    void mostrarTablero() {
        cout << "Tablero:" << endl;
        for (unsigned int i = 0; i < altura; ++i) {
            cout << tablero[i] << " |Fila "
            << i + 1 << endl;//debug
        }
    }
   

    static vector<bool> verificarNiveles(unsigned int nivelesAverificar) {
        vector<bool> existenciaNiveles(nivelesAverificar, false);  // Vector de 11 elementos, inicializados a false

        for (unsigned int i = 1; i <= nivelesAverificar; ++i) {
            string nombreArchivo = "nivel_" + to_string(i) + ".txt";
            ifstream archivo(nombreArchivo);

            if (archivo.is_open()) {
                existenciaNiveles[i-1] = true;
                archivo.close();
            }
        }

        return existenciaNiveles;
    }

};

int main() {
    setUTF8();
    // Verificar existencia de niveles del 0 al 10
    const int nivelesAverificar = 10;
    vector<bool> existenciaNiveles = Nivel::verificarNiveles(nivelesAverificar);

    cout << endl <<  "Existencia de niveles del 1 al 10:" << endl;
    for (int i = 1; i <= nivelesAverificar; ++i) {
        cout << "Nivel " << i << ": " << (existenciaNiveles[i] 
        ? "Existe" //true 
        : "No existe") //false 
        << endl;
    }

    int N;
    cout << "Ingrese el número N para el archivo nivel_N.txt: ";
    cin >> N;

    Nivel nivel(N);
    nivel.cargarNivel();
    nivel.mostrarTablero();

    return 0;
}
