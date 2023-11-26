
#include "Nivel.h"
//private
   
    void Nivel::leerNombreNivel(ifstream& archivo) {
        getline(archivo, this->nombreNivel);
        this->nombreNivel = this->nombreNivel.substr(0, 40);  // Limitar a 40 caracteres
    }

    bool Nivel::leerDimensionesTablero(ifstream& archivo) {
        int anchura, altura;
        if (!(archivo >> anchura >> altura)) {
            return false;
        }  
        if(anchura<0 || altura<0){
            return false;
        }
        this->anchoNivel = anchura;
        this->altoNivel = altura; 
        archivo.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
        this->tableroNivel.resize(altura);// cambia el tamaño del vector a la altura dada
        return true;
    }

    void Nivel::leerTablero(ifstream& archivo) {
        for (unsigned int i = 0; i < this->altoNivel; i++) {
            getline(archivo, this->tableroNivel[i]);
            if(this->tableroNivel[i].size() != this->anchoNivel){//si en lugar de espacios hay vacios
                this->tableroNivel[i].resize(this->anchoNivel, '&');
            }
            this->tableroNivel[i] = this->tableroNivel[i].substr(0, this->anchoNivel);// solo toma el ancho dado lo demas se ignora
        }
    }

//public

    Nivel::Nivel() : numNivel(0), nombreArchivo(""), anchoNivel(0), altoNivel(0), tableroNivel() {} //constructor vacio
    Nivel::Nivel(int num) : numNivel(num), nombreArchivo("nivel_" + to_string(num) + ".txt"), anchoNivel(0), altoNivel(0), tableroNivel() {} //constructor 

    bool Nivel::cargarNivel() {
        ifstream archivo(nombreArchivo);

        if (!archivo.is_open()) {
            //cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
            return false;
        }

        leerNombreNivel(archivo);
        
        if (!leerDimensionesTablero(archivo)){
            //cout << "Error: Dimensiones del tablero incorrectas" << endl;
            return false;
        }
        leerTablero(archivo);
        cambiarVacioPorAmpersand();
        if(!revisarCaracteres()){
            return false;
        }
        if(tieneRepetidasNoContiguas()){
            return false;
        }
        archivo.close();
        return true;
    }
bool Nivel::revisarCaracteres(){//no revisar ñ ya que no se encuentra dentro de los ASCII de la 'a' a la 'z'
    for (unsigned int i = 0; i < this->altoNivel; i++) {
        for (unsigned int j = 0; j < this->anchoNivel; j++) {
            if(isalpha(this->tableroNivel[i][j])){
                this->tableroNivel[i][j]=tolower(this->tableroNivel[i][j]);//a minuscula de pasada las letras
            }else{
                switch (this->tableroNivel[i][j]){
                    case '#':
                    case '&':
                    case '-':
                    case '.':
                    case '*':
                    break;
                    default://cualquier otro simbolo
                    return false;
                }
            }
        }
    }
    return true;
}

void Nivel::cambiarVacioPorAmpersand(){
    for (unsigned int i = 0; i < this->altoNivel; i++) {
        for (unsigned int j = 0; j < this->anchoNivel; j++) {
            if(this->tableroNivel[i][j]==' '){
                this->tableroNivel[i][j]='&';
            }
        }
    }
}
bool Nivel::buscarRepetidasNoContiguas(int i, int j, char objetivo, vector<vector<bool>>& visitado) {
    // Verifica si las coordenadas están fuera de los límites del tablero o si ya se visitó la posición actual
    // Si la letra en la posición actual no coincide con el objetivo, se detiene la búsqueda.
    if (i < 0 || i >= getAltoNivel() || j < 0 || j >= getAnchoNivel() || visitado[i][j] || this->tableroNivel[i][j] != objetivo) {
        return false;
    }

    // Marca la posición actual como visitada
    visitado[i][j] = true;

    // Define los movimientos posibles (arriba, abajo, izquierda, derecha)
    int movimientos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Explora los vecinos de la posición actual
    for (unsigned int k = 0; k < 4; k++) {
        int ni = i + movimientos[k][0];
        int nj = j + movimientos[k][1];

        // Verifica si el vecino está dentro de los límites del tablero y tiene la misma letra que el objetivo
        if (ni >= 0 && ni < getAltoNivel() && nj >= 0 && nj < getAnchoNivel() && this->tableroNivel[ni][nj] == objetivo) {
            // Si el vecino no ha sido visitado, realiza una llamada recursiva a la función DFS
            if (!visitado[ni][nj]) {
                if (buscarRepetidasNoContiguas(ni, nj, objetivo, visitado)) {
                    return true;  // Si se encuentra una letra repetida no contigua, se detiene la búsqueda
                }
            } else {
                // Si el vecino ya ha sido visitado, significa que la letra repetida no es contigua
                return true;
            }
        }
    }

    // Si se han explorado todos los vecinos sin encontrar una letra repetida no contigua, retorna false
    return false;
}

// Función principal para verificar si hay letras repetidas no contiguas en el tablero
bool Nivel::tieneRepetidasNoContiguas() {
    // Inicializa una matriz para rastrear las posiciones visitadas
    vector<vector<bool>> visitado(getAltoNivel(), vector<bool>(getAnchoNivel(), false));
    // Recorre todas las celdas del tablero con DFS
    for (int i = 0; i < getAltoNivel(); i++) {
        for (int j = 0; j < getAnchoNivel(); j++) {
            // Ignora caracteres especiales
            if (this->tableroNivel[i][j] != '#' && this->tableroNivel[i][j] != '&' 
             && this->tableroNivel[i][j] != '*' && this->tableroNivel[i][j] != '-') {
                // Llama a la función DFS para buscar letras repetidas no contiguas
                char objetivo = this->tableroNivel[i][j];
                if (buscarRepetidasNoContiguas(i, j, objetivo, visitado)) {
                    return false;  // Si se encuentra una letra repetida no contiguas
                }
            }
        }
    }
    // Si no se encontraron letras repetidas no contiguas
    return true;
}

    string Nivel::getNombreNivel() const {return this->nombreNivel;}
    string Nivel::getNombreArchivo() const {return this->nombreArchivo;}
    unsigned int Nivel::getAnchoNivel() const {return this->anchoNivel;}
    unsigned int Nivel::getAltoNivel() const{return this->altoNivel;}
    vector<string> Nivel::getTableroNivel() const {return this->tableroNivel;}
