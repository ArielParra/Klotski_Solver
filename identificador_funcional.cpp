#include "Tabla.cpp"
#include <unordered_map>
#include <iostream>
#include <queue>
#include <cctype>


using namespace std;

// Enumeración para las direcciones de movimiento
enum DIRECCION { ARRIBA, ABAJO, IZQUIERDA, DERECHA };

//variable global 
std::unordered_map<char, std::pair<unsigned int, unsigned int>> piezas;


void identificarPiezas(Tabla tablero) {

  const vector<string>& matriz = tablero.getMatriz();
  
  // Matriz para rastrear las celdas visitadas durante el recorrido BFS
  vector<vector<bool>> visitado(tablero.getAltura(), vector<bool>(tablero.getAncho(), false));

  for (unsigned int i = 0; i < tablero.getAltura(); i++) {
    for (unsigned int j = 0; j < tablero.getAncho(); j++) {
      char c = matriz[i][j];

      if (isalpha(c) && !visitado[i][j]) {
        // Inicializar variables para la pieza actual
        unsigned int altura = 0;
        unsigned int ancho = 0;

        // Usar una cola para el recorrido BFS
        queue<pair<unsigned int, unsigned int>> cola;
        cola.push({i, j});

        // Inicio del recorrido BFS
        while (!cola.empty()) {
          // Declare the 'actual' variable
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
          ancho =  y - j + 1;

          // Agregar celdas adyacentes a la cola para continuar el BFS
          cola.push({x + 1, y});
          cola.push({x, y + 1});
        }
        // Fin del recorrido BFS

        // Almacenar la información de la pieza
        piezas[c] = std::make_pair(altura, ancho);

        cout << "Pieza '" << c << "' en (" << i << ", " << j << ") - Altura: " << altura
             << ", Ancho: " << ancho << endl;
      }
    }
  }
}

void moverPiezas(Tabla &tablero, char pieza, DIRECCION dir) {
    if (piezas.find(pieza) == piezas.end()) {
        return;
    }

    unsigned int x = 0, y = 0;

    // Encontrar la posición inicial de la pieza
    for (unsigned int i = 0; i < tablero.getAltura(); i++) {
        for (unsigned int j = 0; j < tablero.getAncho(); j++) {
            char letra = tablero.getMatriz()[i][j];
            if (isalpha(letra) && letra == pieza) {
                x = i;
                y = j;
                break;
            }
        }
    }

    switch (dir) {
        case ARRIBA:
            break;

        case ABAJO:
            break;

        case IZQUIERDA:
            break;

        case DERECHA:

            break;
    }

    // Mostrar el tablero actualizado
    tablero.mostrarTabla();
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
  moverPiezas(tablero,'h',DERECHA);
  moverPiezas(tablero,'h',DERECHA);
  moverPiezas(tablero,'c',ABAJO);



  return 0;
}
