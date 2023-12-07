#pragma once //para que no de problemas de compilacion por inclusion multiple

#include "persona.h"
#include "compatibilidad.h"

class Maestro : public Persona {
private:
    string materiaDada;

public:
    Maestro();
    Maestro(const string & nombre, string materiaDada);

    void setMateriaDada(string materiaDada);
    void imprimirInformacion() const override;
};
