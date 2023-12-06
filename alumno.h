#pragma once

#include "id.h"
using namespace std;
class Alumno : public ID {
private:
    unsigned int semestre;
    char grupo;

public:
    Alumno();
    Alumno(const string& nombre, unsigned int id, unsigned int semestre, char grupo);

    void imprimirInformacion() const override;
    unsigned int getSemestre() const;
    char getGrupo() const;
    void setGrupo(char grupo);
    void setSemestre(unsigned int semestre);
};
