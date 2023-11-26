#include <iostream>
#include <vector>

bool validarSalida(const std::vector<std::string>& tablero) {
    int filas = tablero.size();
    int columnas = tablero[0].size();

    // Posiciones iniciales de X, para 1='.' 
    int iX1 = filas;
    int iY1 = columnas;
    // Posiciones finales de X, para 1='.'
    int fX1 = 0;
    int fY1 = 0;

    // Encontrar las posiciones iniciales y finales de '.'
    for (unsigned int i = 0; i < filas; i++) {
        for (unsigned int j = 0; j < columnas; j++) {
            if (tablero[i][j] == '.') {
                if (i < iX1) { iX1 = i; }
                if (j < iY1) { iY1 = j; }
                if (i > fX1) { fX1 = i; }
                if (j > fY1) { fY1 = j; }
            }
        }
    }

    // Verificar si está tapado izquierda
    for (unsigned int i = iX1; i <= fX1; i++) {
          
    }

    return true;
}

int main() {
    std::vector<std::string> tablero1 = {
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
        "&&&&&&&&.."
    };

    std::vector<std::string> tablero2 = {
        "&&&&&&&&&&",
        "&&&&&&&&&&",
        "&&######&&",
        "&&#a**b#&&",
        "&&#a**b#&&",
        "&&#cdde#&&",
        "&&#cfge#&&",
        "&&#h&&i#&&",
        "&&##--####",
        "&&&&&&&#..",
        "&&&&&&&#.."
    };

    if (validarSalida(tablero1)) {
        std::cout << "El tablero 1 es valido." << std::endl;
    } else {
        std::cout << "El tablero 1 no es valido." << std::endl;
    }

    if (validarSalida(tablero2)) {
        std::cout << "El tablero 2 es valido." << std::endl;
    } else {
        std::cout << "El tablero 2 no es valido." << std::endl;
    }

    return 0;
}
