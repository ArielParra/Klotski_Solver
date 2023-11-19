#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum DIRECCIONES {
    ARRIBA,
    ABAJO,
    IZQUIERDA,
    DERECHA,
};

void imprimirMatriz(const vector<string>& matriz) {
    for (const string& fila : matriz) {
        for (char c : fila) {
            cout << c;
        }
        cout << endl;
    }
}

vector<pair<int, int>> encontrarPosicion(const vector<string>& matriz, char pieza) {
    vector<pair<int, int>> posiciones;
    for (int i = 0; i < matriz.size(); ++i) {
        for (int j = 0; j < matriz[i].size(); ++j) {
            if (matriz[i][j] == pieza) {
                posiciones.push_back(make_pair(i, j));
            }
        }
    }
    return posiciones;
}

void mover(vector<string>& matriz, char pieza, DIRECCIONES direccion) {
    // Encontrar todas las posiciones actuales de la pieza
    vector<pair<int, int>> posiciones = encontrarPosicion(matriz, pieza);

    // Verificar si la pieza fue encontrada
    if (posiciones.empty()) {
        cout << "Pieza no encontrada en el tablero." << endl;
        return;
    }

    // Obtener las dimensiones del tablero
    int filas = matriz.size();
    int columnas = matriz[0].size();

    // Mover la pieza en cada posición encontrada
    for (const auto& posicion : posiciones) {
        int nuevaFila = posicion.first;
        int nuevaColumna = posicion.second;

        switch (direccion) {
            case ARRIBA:
                nuevaFila = max(0, nuevaFila - 1);
                break;
            case ABAJO:
                nuevaFila = min(filas - 1, nuevaFila + 1);
                break;
            case IZQUIERDA:
                nuevaColumna = max(0, nuevaColumna - 1);
                break;
            case DERECHA:
                nuevaColumna = min(columnas - 1, nuevaColumna + 1);
                break;
        }

        // Verificar las coordenadas calculadas
        cout << "Coordenadas actuales: (" << posicion.first << ", " << posicion.second << ")" << endl;
        cout << "Nuevas coordenadas: (" << nuevaFila << ", " << nuevaColumna << ")" << endl;

        // Verificar si la nueva posición está vacía
        if (matriz[nuevaFila][nuevaColumna] == '&') {
            // Actualizar la matriz
            matriz[posicion.first][posicion.second] = '&';
            matriz[nuevaFila][nuevaColumna] = pieza;
        } else {
            cout << "Movimiento no válido, la nueva posición no está vacía." << endl;
        }
    }

    // Imprimir el tablero después de mover la pieza
    cout << "Movimiento exitoso:" << endl;
    imprimirMatriz(matriz);
}

int main() {
    vector<string> tablero = {
        "&&&&&&aa&&&&&&",
        "&&&&&&aa&&&&&&",
        "&&&&&&&&&ccc&&",
        "&&&&&&&&&ccc&&",
        "&&&&&&&&&ccc&&",
        "&&&&&&&&&&&&&&",
    };

    // Imprimir la matriz original
    cout << "tablero original:" << endl;
    imprimirMatriz(tablero);

    // Mover la pieza 'a' hacia abajo
    cout << "\ntablero después de mover 'a' hacia abajo:" << endl;
    mover(tablero, 'a', ABAJO);

    return 0;
}
