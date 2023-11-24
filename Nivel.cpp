
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
        cambiarLetrasRepetidas();
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

void Nivel::cambiarLetrasRepetidas()
{
    char maximaLetra = 'a';
    for (unsigned int i = 0; i < this->altoNivel; i++) {
        for (unsigned int j = 0; j < this->anchoNivel; j++) {
        char letra = this->tableroNivel[i][j];
            if (isalpha(letra) && letra > maximaLetra) {
                maximaLetra = letra;
            }
        }
    }
    vector<vector<bool>> casillas_revisadas(this->altoNivel, vector<bool>( this->anchoNivel, false));
    unordered_set<char> letrasUsadas;

    for (unsigned int i = 0; i < this->altoNivel; i++)
    {
        for (unsigned int j = 0; j < this->anchoNivel; j++)
        {
            char letra = this->tableroNivel[i][j];
            if (letrasUsadas.find(letra) == letrasUsadas.end() && isalpha(letra) && !casillas_revisadas[i][j])
            {
                cout << "first " << this->tableroNivel[i][j] << endl;
                letrasUsadas.insert(letra);
                casillas_revisadas[i][j] = true;

                if (i + 1 < this->altoNivel && this->tableroNivel[i + 1][j] == letra && !casillas_revisadas[i + 1][j])
                { // abajo
                    casillas_revisadas[i + 1][j] = true;
                }
                if (i + 1 <this->altoNivel && j + 1 < this->anchoNivel && this->tableroNivel[i + 1][j + 1] == letra && !casillas_revisadas[i + 1][j + 1])
                { // abajo derecha
                    casillas_revisadas[i + 1][j + 1] = true;
                }
                if (i + 1 < this->altoNivel && j - 1 < 0 && this->tableroNivel[i + 1][j - 1] == letra && !casillas_revisadas[i + 1][j - 1])
                { // abajo izquierda
                    casillas_revisadas[i + 1][j - 1] = true;
                }
                if (i - 1 >= 0 && this->tableroNivel[i - 1][j] == letra && !casillas_revisadas[i - 1][j])
                { // arriba
                    casillas_revisadas[i - 1][j] = true;
                }
                if (i - 1 >= 0 && j + 1 < this->anchoNivel && this->tableroNivel[i - 1][j + 1] == letra && !casillas_revisadas[i - 1][j + 1])
                { // arriba derecha
                    casillas_revisadas[i - 1][j + 1] = true;
                }
                if (i - 1 >= 0 && j - 1 < 0 && this->tableroNivel[i - 1][j - 1] == letra && !casillas_revisadas[i - 1][j - 1])
                { // arriba izquierda
                    casillas_revisadas[i - 1][j - 1] = true;
                }
                if (j - 1 >= 0 && this->tableroNivel[i][j - 1] == letra && !casillas_revisadas[i][j - 1])
                { // izquierda
                    casillas_revisadas[i][j - 1] = true;
                }
                if (j + 1 < this->anchoNivel && this->tableroNivel[i][j + 1] == letra && !casillas_revisadas[i][j + 1])
                { // derecha
                    casillas_revisadas[i][j + 1] = true;
                }
            }
            else if (letrasUsadas.find(letra) != letrasUsadas.end() && isalpha(letra) && !casillas_revisadas[i][j])
            {
                cout << "first " << this->tableroNivel[i][j] << endl;
                casillas_revisadas[i][j] = true;
                maximaLetra++;
                this->tableroNivel[i][j] = maximaLetra;
                letrasUsadas.insert(this->tableroNivel[i][j]);
                if (i + 1 < this->altoNivel && this->tableroNivel[i + 1][j] == letra && !casillas_revisadas[i + 1][j])
                { // abajo
                    casillas_revisadas[i + 1][j] = true;
                    this->tableroNivel[i + 1][j] = maximaLetra;
                }
                if (i + 1 < this->altoNivel && j + 1 < this->anchoNivel && this->tableroNivel[i + 1][j + 1] == letra && !casillas_revisadas[i + 1][j + 1])
                { // abajo derecha
                    casillas_revisadas[i + 1][j + 1] = true;
                    this->tableroNivel[i + 1][j + 1] = maximaLetra;
                }
                if (i + 1 < this->altoNivel && j - 1 < 0 && this->tableroNivel[i + 1][j - 1] == letra && !casillas_revisadas[i + 1][j - 1])
                { // abajo izquierda
                    casillas_revisadas[i + 1][j - 1] = true;
                    this->tableroNivel[i + 1][j - 1] = maximaLetra;
                }
                if (i - 1 >= 0 && this->tableroNivel[i - 1][j] == letra && !casillas_revisadas[i - 1][j])
                { // arriba
                    casillas_revisadas[i - 1][j] = true;
                    this->tableroNivel[i - 1][j] = maximaLetra;
                }
                if (i - 1 >= 0 && j + 1 < this->anchoNivel && this->tableroNivel[i - 1][j + 1] == letra && !casillas_revisadas[i - 1][j + 1])
                { // arriba derecha
                    casillas_revisadas[i - 1][j + 1] = true;
                    this->tableroNivel[i - 1][j + 1] = maximaLetra;
                }
                if (i - 1 >= 0 && j - 1 < 0 && this->tableroNivel[i - 1][j - 1] == letra && !casillas_revisadas[i - 1][j - 1])
                { // arriba izquierda
                    casillas_revisadas[i - 1][j - 1] = true;
                    this->tableroNivel[i - 1][j - 1] = maximaLetra;
                }
                if (j - 1 >= 0 && this->tableroNivel[i][j - 1] == letra && !casillas_revisadas[i][j - 1])
                { // izquierda
                    casillas_revisadas[i][j - 1] = true;
                    this->tableroNivel[i][j - 1] = maximaLetra;
                }
                if (j + 1 < this->anchoNivel && this->tableroNivel[i][j + 1] == letra && !casillas_revisadas[i][j + 1])
                { // derecha
                    casillas_revisadas[i][j + 1] = true;
                    this->tableroNivel[i][j + 1] = maximaLetra;
                }
            }
        }
    }
}
    string Nivel::getNombreNivel() const {return this->nombreNivel;}
    string Nivel::getNombreArchivo() const {return this->nombreArchivo;}
    unsigned int Nivel::getAnchoNivel() const {return this->anchoNivel;}
    unsigned int Nivel::getAltoNivel() const{return this->altoNivel;}
    vector<string> Nivel::getTableroNivel() const {return this->tableroNivel;}
