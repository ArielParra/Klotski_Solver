#include "maestro.h"
#include <iostream>
using namespace std;
Maestro::Maestro() : Persona(""), materiaDada("") {}

Maestro::Maestro(const string& nombre, string materiaDada) : Persona(nombre), materiaDada(materiaDada) {}

void Maestro::setMateriaDada(string materiaDada) {
    this->materiaDada = materiaDada;
}

void Maestro::imprimirInformacion() const {
    cout << FG_GREEN <<getNombre() <<RESET_COLOR<< "   Materia: " << this->materiaDada;
}
