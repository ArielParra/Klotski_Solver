#pragma once //para que no de problemas de compilacion por inclusion multiple

#include <string>
using std::string;

#include <iostream>
using std::cout;

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
