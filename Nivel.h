#ifndef Nivel_h
#define Nivel_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <unordered_set>


//#include "compatibilidad.h"

using std::vector;
using std::unordered_set;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::to_string;
using std::numeric_limits;
using std::streamsize;

class Nivel {
    private:
        unsigned int numNivel; 
        string nombreArchivo;
        string nombreNivel;
        unsigned int anchoNivel;
        unsigned int altoNivel;

        vector<string> tableroNivel;
        void leerNombreNivel(ifstream& archivo);
        bool leerDimensionesTablero(ifstream& archivo);
        void leerTablero(ifstream& archivo);

    public:
        Nivel();
        Nivel(int num); 

        bool cargarNivel();
        bool revisarCaracteres();
        void cambiarVacioPorAmpersand();
        void cambiarLetrasRepetidas();

        string getNombreNivel() const;
        string getNombreArchivo() const ;
        unsigned int getAnchoNivel() const;
        unsigned int getAltoNivel() const;
        vector<string> getTableroNivel() const;

   
};//Clase Nivel

#endif //Nivel_h 