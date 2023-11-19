#include "Tabla.cpp"
#include <unordered_map>
#include <iostream>
#include <queue>
#include <cctype>

using namespace std;

// Enumeración para las direcciones de movimiento
enum DIRECCION { ARRIBA, ABAJO, IZQUIERDA, DERECHA };

class Pieza {
private:
    unsigned int ancho;
    unsigned int altura;
    unsigned int posX;
    unsigned int posY;

public:
    // Métodos getters
    unsigned int getAncho() const { return ancho; }
    unsigned int getAltura() const { return altura; }
    unsigned int getPosX() const { return posX; }
    unsigned int getPosY() const { return posY; }

    // Métodos setters
    void setAncho(unsigned int nuevoAncho) { ancho = nuevoAncho; }
    void setAltura(unsigned int nuevaAltura) { altura = nuevaAltura; }
    void setPosX(unsigned int nuevaPosX) { posX = nuevaPosX; }
    void setPosY(unsigned int nuevaPosY) { posY = nuevaPosY; }
};

class PiezasEnTablero {
private:
    std::unordered_map<char, Pieza> piezasExistentes;

public:
    // Método público para identificar piezas en el tablero
    void identificarPiezas(Tabla tablero);

    // Método público para imprimir la información de las piezas en el tablero
    void imprimirPiezasEnTablero();
    void mover(Tabla& tablero, char pieza, DIRECCION direccion);

};

void PiezasEnTablero::identificarPiezas(Tabla tablero) {
    const vector<string>& matriz = tablero.getMatriz();

    // Matriz para rastrear las celdas visitadas durante el recorrido BFS
    vector<vector<bool>> visitado(tablero.getAltura(), vector<bool>(tablero.getAncho(), false));

    for (unsigned int i = 0; i < tablero.getAltura(); i++) {
        for (unsigned int j = 0; j < tablero.getAncho(); j++) {
            char c = matriz[i][j];

            if ((isalpha(c) || c == '*') && !visitado[i][j]) {
                // Inicializar variables para la pieza actual
                unsigned int altura = 0;
                unsigned int ancho = 0;

                // Usar una cola para el recorrido BFS
                queue<pair<unsigned int, unsigned int>> cola;
                cola.push({i, j});

                // Inicio del recorrido BFS
                while (!cola.empty()) {
                    pair<unsigned int, unsigned int> actual;
                    actual = cola.front();
                    cola.pop();

                    unsigned int x = actual.first;
                    unsigned int y = actual.second;

                    // Verificar si la celda es válida y aún no ha sido visitada
                    if (x >= tablero.getAltura() || y >= tablero.getAncho() || visitado[x][y] || matriz[x][y] != c) {
                        continue;
                    }

                    // Marcar la celda como visitada
                    visitado[x][y] = true;

                    // Actualizar altura y ancho de la pieza
                    altura = x - i + 1;
                    ancho = y - j + 1;

                    // Agregar celdas adyacentes a la cola para continuar el BFS
                    cola.push({x + 1, y});
                    cola.push({x, y + 1});
                }
                // Fin del recorrido BFS

                // Almacenar la información de la pieza
                Pieza nuevaPieza;
                nuevaPieza.setAncho(ancho);
                nuevaPieza.setAltura(altura);
                nuevaPieza.setPosX(j);
                nuevaPieza.setPosY(i);

                this->piezasExistentes[c] = nuevaPieza;
            }
        }
    }
}

void PiezasEnTablero::imprimirPiezasEnTablero() {
    cout << "Información de las piezas en el tablero:" << endl;
    for (const auto& par : piezasExistentes) {
        char c = par.first;
        const Pieza& pieza = par.second;
        cout << "Pieza '" << c << "' en (" << pieza.getPosY() << ", " << pieza.getPosX() << ") - Altura: "
             << pieza.getAltura() << ", Ancho: " << pieza.getAncho() << ", Posición X: " << pieza.getPosX()
             << ", Posición Y: " << pieza.getPosY() << endl;
    }
}

void PiezasEnTablero::mover(Tabla& tablero, char pieza, DIRECCION direccion) {
    if (piezasExistentes.find(pieza) == piezasExistentes.end()) {
        cout << "Pieza '" << pieza << "' no encontrada en el tablero." << endl;
        return;
    }

    Pieza& piezaAMover = piezasExistentes[pieza];

    // Obtener las dimensiones de la pieza
    unsigned int altura = piezaAMover.getAltura();
    unsigned int ancho = piezaAMover.getAncho();

    // Determinar la nueva posición según la dirección
    unsigned int nuevaPosX = piezaAMover.getPosX();
    unsigned int nuevaPosY = piezaAMover.getPosY();

    switch (direccion) {
        case ARRIBA:
            nuevaPosY = nuevaPosY - 1;
            break;
        case ABAJO:
            nuevaPosY = min(tablero.getAltura() - altura, nuevaPosY + 1);
            break;
        case IZQUIERDA:
            nuevaPosX = nuevaPosX - 1;
            break;
        case DERECHA:
            nuevaPosX = min(tablero.getAncho() - ancho, nuevaPosX + 1);
            break;
        default:
            cout << "Dirección no válida." << endl;
            return;
    }

    // Verificar si la nueva posición está disponible
    bool posicionValida = true;
    for (unsigned int i = 0; i < altura; i++) {
        for (unsigned int j = 0; j < ancho; j++) {
            if (tablero.getMatriz()[nuevaPosY + i][nuevaPosX + j] != ' ' && tablero.getMatriz()[nuevaPosY + i][nuevaPosX + j] != '&' && tablero.getMatriz()[nuevaPosY + i][nuevaPosX + j] != pieza) {
                posicionValida = false;
                break;
            }
        }
        if (!posicionValida) {
            break;
        }
    }

    // Actualizar la posición de la pieza si la nueva posición es válida
    if (posicionValida) {
        // Limpiar la antigua posición de la pieza en el tablero
        for (unsigned int i = 0; i < altura; i++) {
            for (unsigned int j = 0; j < ancho; j++) {
                tablero.getMatriz()[piezaAMover.getPosY() + i][piezaAMover.getPosX() + j] = '&';
            }
        }

        // Actualizar la posición de la pieza
        piezaAMover.setPosX(nuevaPosX);
        piezaAMover.setPosY(nuevaPosY);

        // Colocar la pieza en la nueva posición en el tablero
        for (unsigned int i = 0; i < altura; i++) {
            for (unsigned int j = 0; j < ancho; j++) {
                tablero.getMatriz()[nuevaPosY + i][nuevaPosX + j] = pieza;
            }
        }

    } //else {
      //  cout << "Movimiento no válido. La nueva posición está ocupada por otra pieza." << endl;
    //}
}

int main() {
    vector<string> matriz = {
        "&&&&&&&&&&",
        "&&&&&&&&&&",
        "&&######&&",
        "&&#a**b#&&",
        "&&#a**b#&&",
        "&&#cdde#&&",
        "&&#cfge#&&",
        "&&#h&&i#&&",
        "&&##--##&&",
        "&&&&&&&&..",
        "&&&&&&&&..",
    };
    Tabla tablero(matriz);

    PiezasEnTablero piezasEnTablero;
    piezasEnTablero.identificarPiezas(tablero);
    tablero.mostrarTabla();
    piezasEnTablero.imprimirPiezasEnTablero();
    piezasEnTablero.mover(tablero,'h',DERECHA);
    piezasEnTablero.mover(tablero,'h',DERECHA);
    tablero.mostrarTabla();
    piezasEnTablero.mover(tablero,'c',ABAJO);
      piezasEnTablero.mover(tablero,'a',ABAJO);

        tablero.mostrarTabla();




    return 0;
}
