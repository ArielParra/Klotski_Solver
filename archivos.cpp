#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

int main() {
    int N;
    cout << "Ingrese el número N para el archivo nivel_N.txt: ";
    cin >> N;

    string filename = "nivel_" + to_string(N) + ".txt";
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << filename << endl;
        return 1;
    }

    // Leer nombre del nivel
    string nombreNivel;
    getline(file, nombreNivel);

    nombreNivel = nombreNivel.substr(0, 40);  // Limitar a 40 caracteres
    cout << "Nombre del nivel: " << nombreNivel << endl;

    // Leer ancho y altura del tablero
    int ancho, altura;
    file >> ancho >> altura;
    cout << "Ancho del tablero: " << ancho << endl;
    cout << "Altura del tablero: " << altura << endl;
    file.ignore(numeric_limits<streamsize>::max(), '\n');//ignora todo lo demas del archivo hasta el salto de linea

    // Leer el tablero
    for (int i = 0; i < altura; ++i) {
        string linea;
        getline(file, linea);

        // Mostrar solo los primeros 'ancho' caracteres de la línea
        cout << "Fila " << i+1 << ": " << linea.substr(0, ancho) << endl;
    }

    file.close();

    return 0;
}
