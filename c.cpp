#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cctype>

using namespace std;

enum DIRECCION { ARRIBA, ABAJO, IZQUIERDA, DERECHA };

std::unordered_map<char, std::pair<unsigned int, unsigned int>> piezasEnTablero;

class Tabla {
private:
    vector<string> matriz;

public:
    Tabla(const vector<string>& m) : matriz(m) {}
    const vector<string>& getMatriz() const { return matriz; }
    unsigned int getAltura() const { return matriz.size(); }
    unsigned int getAncho() const { return matriz[0].size(); }
    void mostrarTabla() const {
        for (const auto& fila : matriz) {
            cout << fila << endl;
        }
    }
};

class Piezas {
private:
    char pieza;
    unsigned int ancho, altura, posX, posY;

public:
    Piezas() {}
    Piezas(char pieza, unsigned int ancho, unsigned int altura, unsigned int posX, unsigned int posY);
    void actualizarLugar(vector<string>& matriz);
    bool puedeMover(const vector<string>& matriz, char pieza, DIRECCION dir);
    void moverPieza(vector<string>& matriz, char pieza, DIRECCION dir);
};

Piezas::Piezas(char pieza, unsigned int ancho, unsigned int altura, unsigned int posX, unsigned int posY)
    : pieza(pieza), ancho(ancho), altura(altura), posX(posX), posY(posY) {}

void Piezas::actualizarLugar(vector<string>& matriz) {
    for (unsigned int i = this->posY; i < this->posY + this->altura; ++i) {
        for (unsigned int j = this->posX; j < this->posX + this->ancho; ++j) {
            matriz[i][j] = pieza;
        }
    }
}

bool Piezas::puedeMover(const vector<string>& matriz, char letra, DIRECCION dir) {
    unsigned int desX = this->posX, desY = this->posY;

    if (dir == IZQUIERDA) {
        desX--;
    }  // Hacia la izquierda
    if (dir == DERECHA) {
        desX++;
    }  // Hacia la derecha
    if (dir == ABAJO) {
        desY++;
    }  // Hacia abajo
    if (dir == ARRIBA) {
        desY--;
    }  // Hacia arriba

    if (desX >= 0 && desX + this->ancho <= matriz[0].size() && desY >= 0 &&
        desY + this->altura <= matriz.size()) {
        for (unsigned int i = desY; i < desY + this->altura; ++i) {
            for (unsigned int j = desX; j < desX + this->ancho; ++j) {
                // Verifica que no haya colisión con las letras, espacios en blanco y paredes
                if (matriz[i][j] != ' ' && matriz[i][j] != '#' && matriz[i][j] != '&' &&
                    matriz[i][j] != '.') {
                    return false;
                }
            }
        }
        return true;
    }

    return false;
}

void Piezas::moverPieza(vector<string>& matriz, char pieza, DIRECCION dir) {
    if (puedeMover(matriz, pieza, dir)) {
        if (dir == IZQUIERDA) {
            this->posX--;
        }
        if (dir == DERECHA) {
            this->posX++;
        }
        if (dir == ABAJO) {
            this->posY++;
        }
        if (dir == ARRIBA) {
            this->posY--;
        }
    }
    actualizarLugar(matriz);
}

void identificarPiezas(Tabla tablero) {
    const vector<string>& matriz = tablero.getMatriz();

    vector<vector<bool>> visitado(tablero.getAltura(), vector<bool>(tablero.getAncho(), false));

    for (unsigned int i = 0; i < tablero.getAltura(); i++) {
        for (unsigned int j = 0; j < tablero.getAncho(); j++) {
            char c = matriz[i][j];

            if (isalpha(c) && !visitado[i][j]) {
                unsigned int altura = 0;
                unsigned int ancho = 0;

                queue<pair<unsigned int, unsigned int>> cola;
                cola.push({i, j});

                while (!cola.empty()) {
                    pair<unsigned int, unsigned int> actual;

                    actual = cola.front();
                    cola.pop();

                    unsigned int x = actual.first;
                    unsigned int y = actual.second;

                    if (x >= tablero.getAltura() || y >= tablero.getAncho() || visitado[x][y] ||
                        matriz[x][y] != c) {
                        continue;
                    }

                    visitado[x][y] = true;

                    altura = x - i + 1;
                    ancho = y - j + 1;

                    cola.push({x + 1, y});
                    cola.push({x, y + 1});
                }

                piezasEnTablero[c] = make_pair(altura, ancho);

                cout << "Pieza '" << c << "' en (" << i << ", " << j << ") - Altura: " << altura
                     << ", Ancho: " << ancho << endl;
            }
        }
    }
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

    identificarPiezas(tablero);
    tablero.mostrarTabla();

    Piezas prueba;
    char pieza = 'h';

    for (unsigned int i = 0; i < matriz.size(); ++i) {
        for (unsigned int j = 0; j < matriz[0].size(); ++j) {
            char letra = matriz[i][j];
            if (isalpha(letra) && letra == pieza) {
                prueba = Piezas(pieza, piezasEnTablero[pieza].second, piezasEnTablero[pieza].first, j, i);
                break;
            }
        }
    }

    prueba.moverPieza(matriz, pieza, DERECHA);
    tablero.mostrarTabla();

    prueba.moverPieza(matriz, pieza, DERECHA);
    tablero.mostrarTabla();

    prueba.moverPieza(matriz, pieza, ABAJO);
    tablero.mostrarTabla();

    return 0;
}
