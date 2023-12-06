#include "alumno.h"
#include <iostream>
using namespace std;
Alumno::Alumno() : ID(), semestre(0), grupo(' ') {}

Alumno::Alumno(const string& nombre, unsigned int id, unsigned int semestre, char grupo)
    : ID(nombre, id), semestre(semestre), grupo(grupo) {}

void Alumno::imprimirInformacion() const {
    cout << FG_CYAN << getNombre() <<RESET_COLOR<< FG_YELLOW<<"  ID: " <<RESET_COLOR<< getID() <<FG_RED <<"  Semestre: "<<RESET_COLOR << getSemestre() <<FG_MAGENTA<< "  Grupo: "<<RESET_COLOR<< getGrupo();
}

unsigned int Alumno::getSemestre() const {
    return this->semestre;
}

char Alumno::getGrupo() const {
    return this->grupo;
}

void Alumno::setGrupo(char grupo) {
    this->grupo = grupo;
}

void Alumno::setSemestre(unsigned int semestre) {
    this->semestre = semestre;
}
