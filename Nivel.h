# pragma once //para que no de problemas de compilacion por inclusion multiple
#ifndef Nivel_h
#define Nivel_h

#include "FuncionesAuxiliares.h"

#include <iostream>
using std::cin; 
using std::cout; 
using std::endl; 
using std::streamsize; 

#include <vector>
using std::vector; 

#include <unordered_set>
using std::unordered_set; 

#include <string>
using std::string; 
using std::to_string; 

#include <fstream>
using std::ifstream; 

#include <limits>
using std::numeric_limits;

class Nivel {
    private:
        unsigned int numNivel; 
        string nombreArchivo;
        string nombreNivel;
        unsigned int anchoNivel;
        unsigned int altoNivel;

        vector<string> tableroNivel;//se usa string por sus funciones de redimensionamiento (substrings)
        void leerNombreNivel(ifstream& archivo);
        bool leerDimensionesTablero(ifstream& archivo);
        void leerTablero(ifstream& archivo);

    public:
        Nivel();
        Nivel(unsigned int numNivel); 

        bool cargarNivel();
        
        bool revisarCaracteres();
        void cambiarVacioPorAmpersand();

        bool buscarRepetidasNoContiguas(unsigned int i,unsigned int j,unsigned char objetivo, vector<vector<bool>>& visitado);
        bool tieneRepetidasNoContiguas();
        bool tieneSalidaYsingular();

        string getNombreNivel() const;
        string getNombreArchivo() const ;
        unsigned int getAnchoNivel() const; //para herencia 
        unsigned int getAltoNivel() const; //para herencia
        vector<string> getTableroNivel() const;

   
};//Clase Nivel

#endif //Nivel_h 