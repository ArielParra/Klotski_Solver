#include "maestro.h"

Maestro::Maestro() : Persona(""), materiaDada("") {}

Maestro::Maestro(const string& nombre, string materiaDada) : Persona(nombre), materiaDada(materiaDada) {}

void Maestro::setMateriaDada(string materiaDada) {
    this->materiaDada = materiaDada;
}

void Maestro::imprimirInformacion() const {
    cout << FG_GREEN <<getNombre() << FG_BLUE << "   Materia: " << RESET_COLOR << this->materiaDada;
}
