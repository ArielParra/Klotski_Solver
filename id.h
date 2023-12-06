#pragma once

#include "persona.h"
using namespace std;
class ID : public Persona {
private:
    unsigned int id;

public:
    ID();
    ID(const string& nombre, unsigned int id);

    void imprimirInformacion() const override;
    virtual unsigned int getID() const;
    void setID(unsigned int id);
};
