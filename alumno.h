#pragma once //para que no de problemas de compilacion por inclusion multiple

#include "compatibilidad.h"
#include "id.h"

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
