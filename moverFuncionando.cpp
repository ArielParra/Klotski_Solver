#include "Tabla.cpp"
#include <unordered_map>
#include <iostream>
#include <queue>
#include <cctype>
#include <algorithm>

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
    Tabla& tablero;
public:
    PiezasEnTablero(Tabla& tablero);
    // Método público para identificar piezas en el tablero
    void identificarPiezas();

    // Método público para imprimir la información de las piezas en el tablero
    void imprimirPiezasEnTablero();
    void mover( char pieza, DIRECCION direccion);
    bool tableroTerminado();
    Pieza& getPieza(char c);
    Tabla& getTablero();

};

PiezasEnTablero::PiezasEnTablero(Tabla& tablero) : tablero(tablero) {}

void PiezasEnTablero::identificarPiezas() {
    const vector<string>& matriz = tablero.getMatriz();

    // Matriz para rastrear las celdas visitadas durante el recorrido BFS
    vector<vector<bool>> visitado(tablero.getAltura(), vector<bool>(tablero.getAncho(), false));

    for (unsigned int i = 0; i < tablero.getAltura(); i++) {
        for (unsigned int j = 0; j < tablero.getAncho(); j++) {
            char c = matriz[i][j];

            if ((isalpha(c) || c == '*' ||  c == '.') && !visitado[i][j]) {
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

void PiezasEnTablero::mover(char pieza, DIRECCION direccion) {
    if (piezasExistentes.find(pieza) == piezasExistentes.end()) {
        cout << "Pieza '" << pieza << "' no encontrada en el tablero." << endl;
        return;
    }

    Pieza& piezaAMover = piezasExistentes[pieza];

    // Determinar la nueva posición según la dirección
    unsigned int nuevaPosX = piezaAMover.getPosX();
    unsigned int nuevaPosY = piezaAMover.getPosY();

    switch (direccion) {
        case ARRIBA:
            nuevaPosY = nuevaPosY - 1;
            break;
        case ABAJO:
            nuevaPosY = nuevaPosY + 1;
            break;
        case IZQUIERDA:
            nuevaPosX = nuevaPosX - 1;
            break;
        case DERECHA:
            nuevaPosX =  nuevaPosX + 1;
            break;
        default:
            return;
    }

    // Verificar si la nueva posición está disponible
    bool posicionValida = true;

    for (unsigned int i = 0; i < piezaAMover.getAltura(); i++) {
        for (unsigned int j = 0; j < piezaAMover.getAncho(); j++) {
            if (tablero.getAltura() <= nuevaPosY + i || tablero.getAncho() <= nuevaPosX + j) {
                // Se sale del tablero
                posicionValida = false;
                break;
            }
            if (tablero.getMatriz()[nuevaPosY + i][nuevaPosX + j] != ' ' &&
                tablero.getMatriz()[nuevaPosY + i][nuevaPosX + j] != '&' &&
                tablero.getMatriz()[nuevaPosY + i][nuevaPosX + j] != pieza) {
                if (pieza != '*') {
                    // Piezas normales
                    posicionValida = false;
                    break;
                } else if (tablero.getMatriz()[nuevaPosY + i][nuevaPosX + j] != '-' &&
                           tablero.getMatriz()[nuevaPosY + i][nuevaPosX + j] != '.') {
                    // Piezas singular
                    posicionValida = false;
                    break;
                }
            }
        }
    }

    // Actualizar la posición de la pieza si la nueva posición es válida
    if (posicionValida) {
        // Limpiar la antigua posición de la pieza en el tablero
        for (unsigned int i = 0; i < piezaAMover.getAltura(); i++) {
            for (unsigned int j = 0; j < piezaAMover.getAncho(); j++) {
                tablero.getMatriz()[piezaAMover.getPosY() + i][piezaAMover.getPosX() + j] = '&';
            }
        }

        // Actualizar la posición de la pieza
        piezaAMover.setPosX(nuevaPosX);
        piezaAMover.setPosY(nuevaPosY);

        // Colocar la pieza en la nueva posición en el tablero
        for (unsigned int i = 0; i < piezaAMover.getAltura(); i++) {
            for (unsigned int j = 0; j < piezaAMover.getAncho(); j++) {
                tablero.getMatriz()[nuevaPosY + i][nuevaPosX + j] = pieza;
            }
        }
    }
}

bool PiezasEnTablero::tableroTerminado() {
    if (piezasExistentes['*'].getPosX() == piezasExistentes['.'].getPosX() &&
        piezasExistentes['*'].getPosY() == piezasExistentes['.'].getPosY()) {
        return true;
    }
    return false;
}

Pieza& PiezasEnTablero::getPieza(char c) {
    return this->piezasExistentes[c];
}
Tabla& PiezasEnTablero::getTablero(){
    return  this->tablero; 
}


int main() {
    vector<string> matriz = {
        "&&&&&&&&&&",
        "&&&&&&&&&&",
        "&&######&&",
        "&&#a**b#&&",
        "&&#a**b#&&",
        "&&#cdde#&&",
        "&&#c&&e#&&",
        "&&#h&&i#&&",
        "&&##--##&&",
        "&&&&&&&&..",
        "&&&&&&&&..",
    };
    Tabla tablero(matriz);

    PiezasEnTablero piezasEnTablero(tablero);
    piezasEnTablero.identificarPiezas();
    piezasEnTablero.imprimirPiezasEnTablero();
    piezasEnTablero.mover('h',DERECHA);
    piezasEnTablero.getTablero().mostrarTabla();


    return 0;
}
