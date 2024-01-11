#include "persona.h"

Persona::Persona() : nombre("") {}

Persona::Persona(const string& nombre) : nombre(nombre) {}

void Persona::imprimirInformacion() const {
    cout << getNombre();
}

void Persona::setNombre(string nombre) {
    this->nombre = nombre;
}

string Persona::getNombre() const {
    return this->nombre;
}
