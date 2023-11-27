#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

/*
    Persona
   /      \
  ID   Maestro
   \           
    Alumno
*/

// Clase base Persona
class Persona {
protected:// no es private, porque hay que acceder a nombre desde Alumno
    string nombre;

public:

    Persona() : nombre("") {}//constructor vacio
    Persona(const string& nombre) : nombre(nombre) {}
    // Funcion virtual pura para la impresión
    virtual void imprimirInformacion() const {
        cout << getNombre() << endl;
    }
    void setNombre(string nombre){
      this->nombre = nombre;
    }

    virtual string getNombre() const{
    // es virtual para ser usada en imprimirInformacion()
      return this->nombre;
    }

};

// Clase derivada Alumno
class ID : public Persona {//herencia
private:
    unsigned int id;
public:

    ID() : Persona(""), id(0) {}//constructor vacio
    ID(const string& nombre, unsigned int id) : Persona(nombre), id(id) {}

    // Implementación de la función virtual
    // Polimorfismo
    void imprimirInformacion() const override {
        cout << getNombre() << ", ID: " << getID() << endl;
    }
    virtual unsigned int getID() const{
      return this->id;
    }
    void setID(unsigned int id){
      this->id = id;
    }
};

class Maestro : public Persona {//herencia
private:
    string materiaDada;
public:
    Maestro() : Persona(""), materiaDada("") {}//constructor vacio
    Maestro(const string& nombre, string materiaDada) : Persona(nombre), materiaDada(materiaDada) {}

    void setMateriaDada(string materiaDada){
      this->materiaDada = materiaDada;
    }

    void imprimirInformacion() const override {
        cout << getNombre() << ", Materia: " << this->materiaDada << endl;
    }

};


class Alumno : public ID {//herencia
private:
unsigned int semestre;
char grrupo;
public:
    Alumno() : ID(), semestre(0), grrupo(' ') {}//constructor vacio
    Alumno(const string& nombre, unsigned int id, unsigned int semestre, char grupo) : ID(nombre, id), semestre(semestre), grrupo(grupo) {}
      void imprimirInformacion() const override {
        cout << getNombre() << ", ID: " << getID() << ", Semestre: " << getSemestre() << ", grupo: "<< getGrupo() <<endl;
    }
    unsigned int getSemestre() const{
      return this->semestre;
    }

    char getGrupo() const{
      return this->grrupo;
    }
    void setGrupo(char grupo){
      this->grrupo = grupo;
    }

    void setSemestre(unsigned int semestre){
      this->semestre = semestre;
    }


};
int main() {
    // Crear un objeto Alumno
    Maestro blanca("Blanca Guadalupe Estrada Renteria", "Estructuras de Datos");
    Maestro juan("Juan Pedro Cisneros Santoyo", "Programacion II");
    Alumno miguel("Miguel Ángel Batres Luna", 350553, 3 , 'A');
    Alumno alan("Alan Gael Gallardo Jiménez", 351914, 3, 'A');
    Alumno ernesto("Luis Ernesto López Cárdenas", 350346, 3, 'A');
    Alumno ariel("Ariel Emilio Parra Martínez", 280862, 3, 'A');


    // Llamar a la función para imprimir la información
    blanca.imprimirInformacion();
    juan.imprimirInformacion();

    miguel.imprimirInformacion();
    alan.imprimirInformacion();
    ernesto.imprimirInformacion();
    ariel.imprimirInformacion();

    return 0;
}
