#pragma once

#include <string>
#include "compatibilidad.h"
using namespace std;
class Persona {
protected:
    string nombre;

public:
    Persona();
    Persona(const string& nombre);

    virtual void imprimirInformacion() const;
    void setNombre(string nombre);
    virtual string getNombre() const;
};
