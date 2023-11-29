
#include "Nivel.h"
//private
   
    void Nivel::leerNombreNivel(ifstream& archivo) {
        // lee la primera linea del archivo
        getline(archivo, this->nombreNivel);
        // Limitar a 40 caracteres
        this->nombreNivel = this->nombreNivel.substr(0, 40);  
    }

    bool Nivel::leerDimensionesTablero(ifstream& archivo) {
        // lee la segunda linea del archivo`
        int anchura, altura;
        //si no se puede leer (que no sean numeros)
        if (!(archivo >> anchura >> altura)) {
            return false;
        } 
        //si no son numeros enteros positivos 
        if(anchura<=0 || altura<=0){
            return false;
        }
        // se actualizan las dimensiones del tablero
        this->anchoNivel = anchura;
        this->altoNivel = altura; 
        // Ignora el resto de la línea
        archivo.ignore(numeric_limits<streamsize>::max(), '\n'); 
        // cambia el tamaño de la matriz a la altura dada
        this->tableroNivel.resize(altura);
        return true;
    }

    void Nivel::leerTablero(ifstream& archivo) {
        // lee de la tercer linea en adelante
        for (unsigned int i = 0; i < this->altoNivel; i++) {
            getline(archivo, this->tableroNivel[i]);
            //si en lugar de espacios hay vacios
            if(this->tableroNivel[i].size() != this->anchoNivel){
                this->tableroNivel[i].resize(this->anchoNivel, '&');
            }
            // solo toma el ancho dado lo demas se ignora
            this->tableroNivel[i] = this->tableroNivel[i].substr(0, this->anchoNivel);
        }
    }

//public

    Nivel::Nivel() : numNivel(0), nombreArchivo(""), anchoNivel(0), altoNivel(0), tableroNivel() {} //constructor vacio
    Nivel::Nivel(unsigned int numNivel) : numNivel(numNivel), nombreArchivo("nivel_" + to_string(numNivel) + ".txt"), anchoNivel(0), altoNivel(0), tableroNivel() {} //constructor 

    bool Nivel::cargarNivel() {
        ifstream archivo(nombreArchivo);

        if (!archivo.is_open()) {
            //cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl; //debug
            return false;
        }

        leerNombreNivel(archivo);
        
        if (!leerDimensionesTablero(archivo)){
            //cout << "Error: Dimensiones del tablero incorrectas" << endl; //debug
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
        if(!tieneSalidaYsingular()){
            return false;
        }
        archivo.close();
        return true;
    }
bool Nivel::revisarCaracteres(){
    //no revisara 'ñ' ya que no se encuentra dentro de los ASCII de la 'a' a la 'z'
    for (unsigned int i = 0; i < this->altoNivel; i++) {
        for (unsigned int j = 0; j < this->anchoNivel; j++) {
            if(isalpha(this->tableroNivel[i][j])){
                //aprovecho a pasarlos a minusculas
                this->tableroNivel[i][j]=tolower(this->tableroNivel[i][j]);
            }else{
                //si no son letras, revisa los demas
                switch (this->tableroNivel[i][j]){
                    case '#':
                    case '&':
                    case '-':
                    case '.':
                    case '*':
                    //true
                    break;
                    default:
                    //cualquier otro simbolo
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
            //si es un espacio lo cambia por un ampersand
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

bool Nivel::tieneSalidaYsingular(){
    bool piezaSingular=false;
    bool objetivo=false;
  for (int i = 0; i < getAltoNivel(); i++) {
        for (int j = 0; j < getAnchoNivel(); j++) {
            if (this->tableroNivel[i][j] == '*'){
                piezaSingular=true;
                break;
            }
            if (this->tableroNivel[i][j] == '.'){
                objetivo=true;
                break;
            }
        }
    }

return piezaSingular && objetivo;
     
}
    /*getters*/
    string Nivel::getNombreNivel() const {return this->nombreNivel;}
    string Nivel::getNombreArchivo() const {return this->nombreArchivo;}
    unsigned int Nivel::getAnchoNivel() const {return this->anchoNivel;}
    unsigned int Nivel::getAltoNivel() const{return this->altoNivel;}
    vector<string> Nivel::getTableroNivel() const {return this->tableroNivel;}
