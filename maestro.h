#pragma once

#include "persona.h"
using namespace std;

class Maestro : public Persona {
private:
    string materiaDada;

public:
    Maestro();
    Maestro(const string & nombre, string materiaDada);

    void setMateriaDada(string materiaDada);
    void imprimirInformacion() const override;
};
