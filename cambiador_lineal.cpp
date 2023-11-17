#include <bits/stdc++.h>
std::set<char> letrasUsadas;

void cambiarLetrasRepetidas(std::vector<std::string>& matriz) {
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[0].size(); j++) {
            if (isalpha(matriz[i][j])) {
                char letra = matriz[i][j];
                letrasUsadas.insert(letra);
                bool primeraAparicion = true;

                // Verificar si es la primera aparición de la letra
                for (int x = 0; x < i; x++) {
                    for (int y = 0; y < matriz[0].size(); y++) {
                        if (matriz[x][y] == letra) {
                            primeraAparicion = false;
                            break;
                        }
                    }
                    if (!primeraAparicion) break;
                }

                // Si no es la primera aparición y no es contigua, cambiar la letra
                if (!primeraAparicion) {
                    bool contigua = false;

                    // Verificar si la letra ya apareció antes y es contigua
                    for (int x = 0; x < matriz.size(); x++) {
                        for (int y = 0; y < matriz[0].size(); y++) {
                            if (matriz[x][y] == letra) {
                                if (std::abs(x - i) + std::abs(y - j) == 1) {
                                    contigua = true;
                                    break;
                                }
                            }
                        }
                        if (contigua) break;
                    }

                    // Cambiar la letra si no es contigua
                    if (!contigua) {
                        char nuevaLetra = 'a';
                        while (letrasUsadas.find(nuevaLetra) != letrasUsadas.end()) {
                            nuevaLetra++;
                        }
                        matriz[i][j] = nuevaLetra; 
                        letrasUsadas.insert(nuevaLetra);  
                    }
                }
            }
        }
    }
}

int main() {
    // Tu matriz original
    std::vector<std::string> matriz = {
        "&&&&&&&&&&",
        "&&&&&&&&&&",
        "&&######&&",
        "&&#a**b#&&",
        "&&#a**b#&&",
        "&&#cdde#&&",
        "&&#cfge#&&",
        "&&#a&&b#&&", // solo se cambiaria 'a' por 'h' y 'b' por 'i' 
        "&&##--##&&",
        "&&&&&&&&..",
        "&&&&&&&&.."
    };

    // Cambia las letras repetidas no contiguas
    cambiarLetrasRepetidas(matriz);

    // Imprime la matriz
    for (const auto& fila : matriz) {
        std::cout << fila << '\n';
    }

    return 0;
}
