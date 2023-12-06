#include "id.h"
#include <iostream>
using namespace std;
ID::ID() : Persona(""), id(0) {}

ID::ID(const string& nombre, unsigned int id) : Persona(nombre), id(id) {}

void ID::imprimirInformacion() const {
    cout << getNombre() << ", ID: " << getID();
}

unsigned int ID::getID() const {
    return this->id;
}

void ID::setID(unsigned int id) {
    this->id = id;
}
