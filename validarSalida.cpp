#include <iostream>
#include <vector>

bool validarSalida(const std::vector<std::string>& tablero) {
    int filas = tablero.size();
    int columnas = tablero[0].size();

    //posiciones iniciales de X, para 1='.' y 2='*'
    int iX1=0, iX2=0;
    int iY1=0, iY2=0;
    //posiciones finales de X, para 1='.' y 2='*'
    int fX1=0 ,fX2=0;
    int fY1=0, fY2=0;

    for(unsigned int i = 0; i < filas; i++) {
        for(unsigned int j = 0; j < columnas; j++) {
            if(tablero[i][j]=='.'){
                if(i<iX1){ iX1=i; }
                if(j<iY1){ iY1=j; }
                if(i>fX1){ fX1=i; }
                if(j>fY1){ fY1=j; }
            }
            if(tablero[i][j]=='*'){
                if(i<iX2){ iX2=i; }
                if(j<iY2){ iY2=j; }
                if(i>fX2){ fX2=i; }
                if(j>fY2){ fY2=j; }
            }
        }
    }
    //diferencia de X , para 1='.' y 2='*'
    int dX1= fX1- iX1;
    int dX2= fX2- iX2;
    //diferencia de Y , para 1='.' y 2='*'
    int dY1= fY1- iY1;
    int dY2= fY2- iY2;

    //si es menor que cero 
    if(dX1<=0 || dX2<=0  
    || dY1<=0 || dY2<=0  ){
        return false;
    }
    //si es mas chico que el '*'
    if(dX1<dX2 && dY1<dY2){
        return false;
    }
    for(unsigned int i = iX1; i <= fX1; i++) {
        for(unsigned int j = iY1; j <= fY1; j++) {
            /*quiero verificar que si esta tapado por ambos lados sea falso:
                ##
              ##..
              ##..             
            */
        }
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
