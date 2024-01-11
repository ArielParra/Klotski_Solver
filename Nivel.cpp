
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
            const string error1= "Error: No se pudo abrir el archivo: " + this->nombreArchivo;
            cout<<FG_RED;
            mensajeCentrado(error1);
            return false;
        }

        leerNombreNivel(archivo);
        
        if (!leerDimensionesTablero(archivo)){
            const string error2= "Error: Dimensiones del tablero incorrectas en el archivo: " + this->nombreArchivo;
            cout<<FG_RED;
            mensajeCentrado(error2);
            return false;
        }
        leerTablero(archivo);
        cambiarVacioPorAmpersand();
        if(!revisarCaracteres()){
            const string error3= "Error: Caracteres invalidos en el archivo: " + this->nombreArchivo;
            cout<<FG_RED;
            mensajeCentrado(error3);
            return false;
        }
        /*
        if(tieneRepetidasNoContiguas()){
            const string error4= "Error: Existen letras repetidas no contiguas en el archivo: " + this->nombreArchivo;
            cout<<FG_RED;
            mensajeCentrado(error4);
            return false;
        }
        */
        if(!tieneSalidaYsingular()){
            const string error5= "Error: No existe Salida o la Pieza Singular en el archivo: " + this->nombreArchivo;
            cout<<FG_RED;
            mensajeCentrado(error5);
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

bool Nivel::tieneSalidaYsingular(){
    bool piezaSingular=false;
    bool objetivo=false;
  for (int i = 0; i < getAltoNivel(); i++) {
        for (int j = 0; j < getAnchoNivel(); j++) {
            if (!piezaSingular && this->tableroNivel[i][j] == '*'){
                piezaSingular=true;
            }else if (!objetivo && this->tableroNivel[i][j] == '.'){
                objetivo=true;
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
