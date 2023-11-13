class Tabla {
private:
    unsigned int filas;
    unsigned int columnas;
    char** matriz;

public:
    Tabla(unsigned int filas, unsigned int columnas) : filas(filas), columnas(columnas) {
        matriz = new char*[filas];
        for (unsigned int i = 0; i < filas; ++i) {
            matriz[i] = new char[columnas];
        }
    }

    ~Tabla() {
        for (unsigned int i = 0; i < filas; ++i) {
            delete[] matriz[i];
        }
        delete[] matriz;
    }

    // Resto de las funciones de la clase Tabla
};