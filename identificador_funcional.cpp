#include "Tabla.cpp"
#include <unordered_map>
#include <iostream>
#include <queue>

using namespace std;

// Enumeración para las direcciones de movimiento
enum Direccion { ARRIBA, ABAJO, IZQUIERDA, DERECHA };

class Piezas {
private:
  std::unordered_map<char, std::pair<unsigned int, unsigned int>> piezas;

public:
  Piezas();
  void identificarPiezas(Tabla tablero);
  void moverPieza(char pieza, Direccion direccion, Tabla& tablero);
};

Piezas::Piezas() {}

void Piezas::identificarPiezas(Tabla tablero) {
  const vector<string>& matriz = tablero.getMatriz();
  
  // Matriz para rastrear las celdas visitadas durante el recorrido BFS
  vector<vector<bool>> visitado(tablero.getAltura(), vector<bool>(tablero.getAncho(), false));

  for (unsigned int i = 0; i < tablero.getAltura(); i++) {
    for (unsigned int j = 0; j < tablero.getAncho(); j++) {
      char c = matriz[i][j];

      if (c != '&' && !visitado[i][j]) {
        // Inicializar variables para la pieza actual
        unsigned int altura = 0;
        unsigned int ancho = 0;

        // Usar una cola para el recorrido BFS
        queue<pair<unsigned int, unsigned int>> cola;
        cola.push({i, j});

        // Inicio del recorrido BFS
        while (!cola.empty()) {
          auto actual = cola.front();
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
          altura = max(altura, x - i + 1);
          ancho = max(ancho, y - j + 1);

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

void Piezas::moverPieza(char pieza, Direccion direccion, Tabla &tablero)
{
    // Verificar si la pieza existe en el mapa
    if (piezas.find(pieza) == piezas.end())
    {
        cout << "Pieza '" << pieza << "' no encontrada." << endl;
        return;
    }

    // Obtener la información de la pieza
    auto infoPieza = piezas[pieza];
    unsigned int altura = infoPieza.first;
    unsigned int ancho = infoPieza.second;

    // Encontrar la posición actual de la pieza en el tablero
    unsigned int posX = 0, posY = 0;
    bool encontrada = false;

    for (unsigned int i = 0; i < tablero.getAltura(); i++)
    {
        for (unsigned int j = 0; j < tablero.getAncho(); j++)
        {
            if (tablero.getMatriz()[i][j] == pieza)
            {
                posX = i;
                posY = j;
                encontrada = true;
                break;
            }
        }
    }

    // Verificar si es posible mover la pieza en la dirección deseada
    unsigned int nuevoPosX = posX, nuevoPosY = posY;

    switch (direccion)
    {
    case ARRIBA:
        nuevoPosX--;
        break;
    case ABAJO:
        nuevoPosX++;
        break;
    case IZQUIERDA:
        nuevoPosY--;
        break;
    case DERECHA:
        nuevoPosY++;
        break;
    }

    // Verificar si la nueva posición es válida
    if (nuevoPosX + altura <= tablero.getAltura() && nuevoPosY + ancho <= tablero.getAncho())
    {
        // Verificar si las celdas a ocupar están vacías
        bool celdasVacias = true;

        for (unsigned int i = nuevoPosX; i < nuevoPosX + altura; i++)
        {
            for (unsigned int j = nuevoPosY; j < nuevoPosY + ancho; j++)
            {
                if (tablero.getMatriz()[i][j] != '&')
                {
                    celdasVacias = false;
                    break;
                }
            }
            if (!celdasVacias)
            {
                break;
            }
        }

        // Realizar el movimiento si las celdas están vacías
        if (celdasVacias)
        {
            for (unsigned int i = 0; i < altura; i++)
            {
                for (unsigned int j = 0; j < ancho; j++)
                {
                    tablero.getMatriz()[posX][posY]='&';
                    tablero.getMatriz()[nuevoPosX][nuevoPosY] = pieza;
                }
            }

            cout << "Movimiento exitoso. Nuevo tablero:" << endl;
            tablero.mostrarTabla();
            return;
        }
    }

    // Si no se puede realizar el movimiento, mostrar mensaje
    cout << "No se puede realizar el movimiento." << endl;
}

int main() {
  vector<string> matriz = {
      "&aa&&&&&&&",
      "&aa&&&&&&&",
      "&&&&&&&&&&",
  };
  Tabla tablero(matriz);

  Piezas piezas;

  piezas.identificarPiezas(tablero);
  piezas.moverPieza('a', DERECHA, tablero);
  piezas.moverPieza('a', DERECHA, tablero);
  piezas.moverPieza('a', ABAJO, tablero);

  return 0;
}