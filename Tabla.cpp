#include "Tabla.h"
#include <iostream>
#include <unordered_set>

using std::cout;
using std::endl;
using std::unordered_set;

/*Public*/

Tabla::Tabla() : ancho(0), altura(0) {} // constructor vacio

Tabla::Tabla(unsigned int ancho, unsigned int altura)
    : ancho(ancho), altura(altura)
{                                              // constructor
    matriz.resize(altura, string(ancho, ' ')); // Inicializa la matriz con strings vacíos
}

Tabla::Tabla(const vector<string> &matriz)
{ // constructor con matriz
    // Asigna la matriz proporcionada
    this->matriz = matriz;

    // Establece la altura y el ancho basándose en la matriz
    this->altura = matriz.size();
    this->ancho = matriz[0].size();
}

/*Metodos get*/
unsigned int Tabla::getAncho() const { return this->ancho; }

unsigned int Tabla::getAltura() const { return this->altura; }

void Tabla::mostrarTabla()
{
    for (unsigned int i = 0; i < Tabla::getAltura(); i++)
    {
        cout << matriz[i] << endl;
    }
}

vector<string> &Tabla::getMatriz()
{
    return this->matriz;
}
const vector<string> &Tabla::getMatriz() const
{
    return this->matriz;
}

/*Metodos set*/
void Tabla::cargarFila(unsigned int fila, const string &datos)
{
    this->matriz[fila] = datos.substr(0, ancho);
}

void Tabla::cambiarRepetidos()
{
    char maximaLetra = 'a';
    for (unsigned int i = 0; i < Tabla::getAltura(); i++)
    {
        for (unsigned int j = 0; j < Tabla::getAncho(); j++)
        {
            char letra = matriz[i][j];
            if (isalpha(letra))
            {
                if (letra > maximaLetra)
                {
                    maximaLetra = letra;
                }
            }
        }
    }

    vector<vector<bool>> casillas_revisadas(getAltura(), vector<bool>(Tabla::getAncho(), false));
    unordered_set<char> letrasUsadas;

    for (unsigned int i = 0; i < Tabla::getAltura(); i++)
    {
        for (unsigned int j = 0; j < Tabla::getAncho(); j++)
        {
            char letra = matriz[i][j];
            if (letrasUsadas.find(letra) == letrasUsadas.end() && isalpha(letra) && !casillas_revisadas[i][j])
            {
                cout << "first " << matriz[i][j] << endl;
                letrasUsadas.insert(letra);
                casillas_revisadas[i][j] = true;

                if (i + 1 < Tabla::getAltura() && matriz[i + 1][j] == letra && !casillas_revisadas[i + 1][j])
                { // abajo
                    casillas_revisadas[i + 1][j] = true;
                }
                if (i + 1 < Tabla::getAltura() && j + 1 < Tabla::getAncho() && matriz[i + 1][j + 1] == letra && !casillas_revisadas[i + 1][j + 1])
                { // abajo derecha
                    casillas_revisadas[i + 1][j + 1] = true;
                }
                if (i + 1 < Tabla::getAltura() && j - 1 < 0 && matriz[i + 1][j - 1] == letra && !casillas_revisadas[i + 1][j - 1])
                { // abajo izquierda
                    casillas_revisadas[i + 1][j - 1] = true;
                }
                if (i - 1 >= 0 && matriz[i - 1][j] == letra && !casillas_revisadas[i - 1][j])
                { // arriba
                    casillas_revisadas[i - 1][j] = true;
                }
                if (i - 1 >= 0 && j + 1 < Tabla::getAncho() && matriz[i - 1][j + 1] == letra && !casillas_revisadas[i - 1][j + 1])
                { // arriba derecha
                    casillas_revisadas[i - 1][j + 1] = true;
                }
                if (i - 1 >= 0 && j - 1 < 0 && matriz[i - 1][j - 1] == letra && !casillas_revisadas[i - 1][j - 1])
                { // arriba izquierda
                    casillas_revisadas[i - 1][j - 1] = true;
                }
                if (j - 1 >= 0 && matriz[i][j - 1] == letra && !casillas_revisadas[i][j - 1])
                { // izquierda
                    casillas_revisadas[i][j - 1] = true;
                }
                if (j + 1 < Tabla::getAncho() && matriz[i][j + 1] == letra && !casillas_revisadas[i][j + 1])
                { // derecha
                    casillas_revisadas[i][j + 1] = true;
                }
            }
            else if (letrasUsadas.find(letra) != letrasUsadas.end() && isalpha(letra) && !casillas_revisadas[i][j])
            {
                cout << "first " << matriz[i][j] << endl;
                casillas_revisadas[i][j] = true;
                maximaLetra++;
                matriz[i][j] = maximaLetra;
                letrasUsadas.insert(matriz[i][j]);
                if (i + 1 < Tabla::getAltura() && matriz[i + 1][j] == letra && !casillas_revisadas[i + 1][j])
                { // abajo
                    casillas_revisadas[i + 1][j] = true;
                    matriz[i + 1][j] = maximaLetra;
                }
                if (i + 1 < Tabla::getAltura() && j + 1 < Tabla::getAncho() && matriz[i + 1][j + 1] == letra && !casillas_revisadas[i + 1][j + 1])
                { // abajo derecha
                    casillas_revisadas[i + 1][j + 1] = true;
                    matriz[i + 1][j + 1] = maximaLetra;
                }
                if (i + 1 < Tabla::getAltura() && j - 1 < 0 && matriz[i + 1][j - 1] == letra && !casillas_revisadas[i + 1][j - 1])
                { // abajo izquierda
                    casillas_revisadas[i + 1][j - 1] = true;
                    matriz[i + 1][j - 1] = maximaLetra;
                }
                if (i - 1 >= 0 && matriz[i - 1][j] == letra && !casillas_revisadas[i - 1][j])
                { // arriba
                    casillas_revisadas[i - 1][j] = true;
                    matriz[i - 1][j] = maximaLetra;
                }
                if (i - 1 >= 0 && j + 1 < Tabla::getAncho() && matriz[i - 1][j + 1] == letra && !casillas_revisadas[i - 1][j + 1])
                { // arriba derecha
                    casillas_revisadas[i - 1][j + 1] = true;
                    matriz[i - 1][j + 1] = maximaLetra;
                }
                if (i - 1 >= 0 && j - 1 < 0 && matriz[i - 1][j - 1] == letra && !casillas_revisadas[i - 1][j - 1])
                { // arriba izquierda
                    casillas_revisadas[i - 1][j - 1] = true;
                    matriz[i - 1][j - 1] = maximaLetra;
                }
                if (j - 1 >= 0 && matriz[i][j - 1] == letra && !casillas_revisadas[i][j - 1])
                { // izquierda
                    casillas_revisadas[i][j - 1] = true;
                    matriz[i][j - 1] = maximaLetra;
                }
                if (j + 1 < Tabla::getAncho() && matriz[i][j + 1] == letra && !casillas_revisadas[i][j + 1])
                { // derecha
                    casillas_revisadas[i][j + 1] = true;
                    matriz[i][j + 1] = maximaLetra;
                }
            }
        }
    }
}