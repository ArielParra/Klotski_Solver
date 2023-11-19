#include <iostream>
#include <string>
#include <vector>
using namespace std;


enum Direccion{
  ARRIBA,
  ABAJO,
  IZQUIERDA,
  DERECHA,
};

class Piezas
{
private:
  char pieza;
  unsigned int ancho, altura, posX, posY;

public:
  Piezas() {}
  Piezas(char pieza, unsigned int ancho, unsigned int altura, unsigned int posX, unsigned int posY);
  void actualizarLugar(vector<string>& matriz);
  bool puedeMover(vector<string>& matriz, char pieza, Direccion dir);
  void moverPieza(vector<string>& matriz, char pieza, Direccion dir);
};

Piezas::Piezas(char pieza, unsigned int ancho, unsigned int altura, unsigned int posX, unsigned int posY) : pieza(pieza), ancho(ancho), altura(altura), posX(posX), posY(posY) {}
// Implementación
void Piezas::actualizarLugar(vector<string>& matriz)
{
    for(int i = this->posY; i < this->posY + this->altura; ++i)
    {
        for(int j = this->posX; j < this->posX + this->ancho; ++j)
        {
            matriz[i][j] = pieza;
        }
    }
}

bool Piezas::puedeMover(vector<string>& matriz,char letra,  Direccion dir)
{
    unsigned int desX = this->posX, desY = this->posY;
    
    if(dir == IZQUIERDA) { desX--;} // Hacia la izquierda
    if(dir == DERECHA) { desX++;} // Hacia la derecha
    if(dir == ABAJO) { desY++;} // Hacia abajo
    if(dir == ARRIBA) { desY--;} // Hacia arriba
    
    if(desX >= 0 && desX + this->ancho <= matriz[0].size() && desY >= 0 && desY + this->altura <= matriz.size())
    {
        for (unsigned int i = desY; i < desY + this->altura; ++i)
        {
            for (unsigned int j = desX; j < desX + this->ancho; ++j)
            {
                // Verifica que no haya colisión con las letras, espacios en blanco y paredes
                if (matriz[i][j] != ' ' && matriz[i][j] != '#' && matriz[i][j] != '&' && matriz[i][j] != '.') {
                    return false;
                }
            }
        }
        return true;
    }

    return false;
}

void Piezas::moverPieza(vector<string>& matriz, char pieza, Direccion dir)
{
    if(puedeMover(matriz, pieza ,dir))
    {
        if(dir == IZQUIERDA) { this->posX--;}
        if(dir == DERECHA) { this->posX++;}
        if(dir  == ABAJO) { this->posY++;}
        if(dir == ARRIBA) { this->posY--;}
    }
    actualizarLugar(matriz);
}

int main(void)
{   
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
    "&&&&&&&&.."
};
    prueba.actualizarLugar(matriz);
    prueba.movimientoMatriz(matriz, 'h', DERECHA);    
    return 0;
}
