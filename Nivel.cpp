#include "Nivel.h"
#include <iostream>
#include <limits> // para limitar la captura de renglones

using std::numeric_limits;
using std::streamsize;
using std::to_string;
using std::endl;
using std::cout;



Nivel::Nivel(unsigned int num)
    : numNivel(num), nombreArchivo("nivel_" + to_string(num) + ".txt") {
} // constructor

/*Private*/
void Nivel::leerNombreNivel(ifstream &archivo) { // primera linea
  getline(archivo, nombreNivel);
  nombreNivel = nombreNivel.substr(0, 40);
}

bool Nivel::leerDimensionesTablero(ifstream &archivo) { // segunda linea
  int anchura, altura;
  if (!(archivo >> anchura >> altura)) {
    return false;
  }  
  if(anchura<0 || altura<0){
    return false;
  }  
  cout << "Ancho del tablero: " << anchura << endl;
  cout << "Altura del tablero: " << altura << endl;

  archivo.ignore(numeric_limits<streamsize>::max(),'\n'); // Ignora el resto de la línea

  this->alto=(unsigned int)altura;
  this->ancho=(unsigned int)anchura;
  return true;
}

void Nivel::leerTablero(ifstream &archivo) { // tercera linea en adelante
  if(this->NivelCargado){
    for (unsigned int i = 0; i< this->alto; i++) {
      string fila;
      getline(archivo, fila);
      this->tableroNivel[i] = fila.substr(0, this->ancho);
    }
  }
}

/*Public*/
bool Nivel::cargarNivel() {
  ifstream archivo(nombreArchivo);

  if (!archivo.is_open()) {
    this->NivelCargado=false;
    return false;
  }

  this->leerNombreNivel(archivo);

  if(!leerDimensionesTablero(archivo)){
    this->NivelCargado=false;
    return false;
  }

  this->leerTablero(archivo);

  archivo.close();
  this->NivelCargado=true;
  return true;
}

/*Metodos get*/
unsigned int Nivel::getNumNivel() const { return this->numNivel; }
string Nivel::getNombreArchivo() const { return this->nombreArchivo; }
string Nivel::getNombreNivel() const { return this->nombreNivel; }
vector<string> Nivel::getTableroNivel() {return this->tableroNivel; }
    unsigned int Nivel::getAnchoNivel(){
      return this->alto;
    }
  unsigned int Nivel::getAltoNivel(){
      return this->alto;
  }


