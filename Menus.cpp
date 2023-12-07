#include "Menus.h"

/*logo y graficos*/

inline void Menus::logouaa(){
const int altura_grafico=16,ancho_grafico=43;
int x=(getmaxX()/4)-(ancho_grafico/2),y=(getmaxY()/2)-(altura_grafico/2);
gotoxy(x, y);  cout<<FG_BLUE<<"█▒  "<< FG_CYAN<<"██████       "<<FG_CYAN<<"██████ "<<FG_BLUE<<"▒▒█████▒▒▒        "; 
gotoxy(x, y++);cout<<FG_BLUE<<"███  "<<FG_CYAN<<"███████   "<<FG_CYAN<<"███████ "<<FG_BLUE<<"▒█████████████     "; 
gotoxy(x, y++);cout<<FG_BLUE<<"███▒ "<<FG_CYAN<<"███████                      "<<FG_BLUE<<"█████   "; 
gotoxy(x, y++);cout<<FG_BLUE<<"███▒ "<<FG_CYAN<<"███████               "<<FG_CYAN<<"███████  "<<FG_BLUE<<"▒███▒ ";
gotoxy(x, y++);cout<<FG_BLUE<<"███▒ "<<FG_CYAN<<"███████        "<<FG_YELLOW<<"██      "<<FG_CYAN<<"████████ "<<FG_BLUE<<"▒███▒"; 
gotoxy(x, y++);cout<<FG_BLUE<<"███▒ "<<FG_CYAN<<"███████       "<<FG_YELLOW<<"████ "<<FG_RED<<"█    "<<FG_CYAN<<"████████ "<<FG_BLUE<<"▒███";
gotoxy(x, y++);cout<<FG_BLUE<<"███▒ "<<FG_CYAN<<"███████      "<<FG_YELLOW<<"████ "<<FG_RED<<"███    "<<FG_CYAN<<"███████ "<<FG_BLUE<<"▒███";
gotoxy(x, y++);cout<<FG_BLUE<<"███▒ "<<FG_CYAN<<"███████     "<<FG_YELLOW<<"████ "<<FG_RED<<"█████   "<<FG_CYAN<<"███████ "<<FG_BLUE<<"▒███"; 
gotoxy(x, y++);cout<<FG_BLUE<<"███▒ "<<FG_CYAN<<"███████    "<<FG_YELLOW<<"████ "<<FG_RED<<"██████   "<<FG_CYAN<<"███████ "<<FG_BLUE<<"▒███";
gotoxy(x, y++);cout<<FG_BLUE<<"███▒ "<<FG_CYAN<<"███████    "<<FG_YELLOW<<"███ "<<FG_RED<<"██████    "<<FG_CYAN<<"███████ "<<FG_BLUE<<"▒███";
gotoxy(x, y++);cout<<FG_BLUE<<"███▒ "<<FG_CYAN<<"███████    "<<FG_YELLOW<<"██ "<<FG_RED<<"█████      "<<FG_CYAN<<"███████ "<<FG_BLUE<<"▒███";
gotoxy(x, y++);cout<<FG_BLUE<<"████ "<<FG_CYAN<<"████████      "<<FG_RED<<"████       "<<FG_CYAN<<"███████ "<<FG_BLUE<<"▒███"; 
gotoxy(x, y++);cout<<FG_BLUE<<" ███▒ "<<FG_CYAN<<"████████      "<<FG_RED<<"██        "<<FG_CYAN<<"███████ "<<FG_BLUE<<"▒███";
gotoxy(x, y++);cout<<FG_BLUE<<" ▒████  "<<FG_CYAN<<"███████               ███████ "<<FG_BLUE<<"▒███"; 
gotoxy(x, y++);cout<<FG_BLUE<<"   █████                      "<<FG_CYAN<<"███████ "<<FG_BLUE<<"▒███";
gotoxy(x, y++);cout<<FG_BLUE<<"     ▒████████████▒ "<<FG_CYAN<<"████████   ███████ "<<FG_BLUE<<"███"<<RESET_COLOR;
fflush(stdout);
}


inline void Menus::flecha_derecha() {
  const int altura_grafico=9, ancho_grafico=14;
  int x=getmaxX()-ancho_grafico,y=getmaxY()-altura_grafico;
  cout<<FG_BLUE;
  gotoxy(x, y++); cout << "   ▒▒▒▒▒▒▒▒    ";
  gotoxy(x, y++); cout << "  ▒        ▒   "; 
  gotoxy(x, y++); cout << " ▒      ▒   ▒  "; 
  gotoxy(x, y++); cout << "▒        ▒   ▒ "; 
  gotoxy(x, y++); cout << "▒  ▒▒▒▒▒▒▒▒  ▒ "; 
  gotoxy(x, y++); cout << "▒        ▒   ▒ ";  
  gotoxy(x, y++); cout << " ▒      ▒   ▒  ";  
  gotoxy(x, y++); cout << "  ▒        ▒   ";  
  gotoxy(x, y++); cout << "   ▒▒▒▒▒▒▒▒    " <<RESET_COLOR;
  fflush(stdout);

}

inline void Menus::flecha_izquierda() {
  const int altura_grafico=9;
  int x=1,y=getmaxY()-altura_grafico;
  cout<<FG_BLUE;
  gotoxy(x, y++); cout << "   ▒▒▒▒▒▒▒▒    ";
  gotoxy(x, y++); cout << "  ▒        ▒   ";  
  gotoxy(x, y++); cout << " ▒   ▒      ▒  ";  
  gotoxy(x, y++); cout << "▒   ▒        ▒ ";  
  gotoxy(x, y++); cout << "▒  ▒▒▒▒▒▒▒▒  ▒ ";  
  gotoxy(x, y++); cout << "▒   ▒        ▒ "; 
  gotoxy(x, y++); cout << " ▒   ▒      ▒  "; 
  gotoxy(x, y++); cout << "  ▒        ▒   "; 
  gotoxy(x, y++); cout << "   ▒▒▒▒▒▒▒▒    " <<RESET_COLOR;
  fflush(stdout);
}

unsigned int Menus::validarEntradaInt(){
//funcion auxiliar para validar entrada de numeros
bool esValido = true; //bandera para validar entrada en el do while
string entrada; //entrada del usuario
  do {
    const string mensaje = "Ingrese el número N para el archivo nivel_N.txt: ";
    const string lineaDeCaptura = "-----";
    gotoxy(getmaxX()/2 - mensaje.size()/2, getmaxY()/2);
    cout<<FG_MAGENTA<<mensaje<<RESET_COLOR;
    gotoxy(getmaxX()/2 + mensaje.size()/2 , getmaxY()/2 + 1);
    cout<<lineaDeCaptura;
    esValido = true;
    fflush(stdin);
    entrada.clear(); //se limpia la entrada
      //para capturar incluso espacios
      gotoxy(getmaxX()/2 + mensaje.size()/2 , getmaxY()/2);
      reset_shell_mode();//salirse de ncurses para usar getline
        cout<<CURSOR_ON;
        getline(cin,entrada);
        cout<<CURSOR_OFF;
      reset_prog_mode();//regresar a ncurses
      string error; 
      //solo se dio enter = error
      if(entrada.length()<1){
        esValido=false;
        error="Error: Ingrese algún número";
      }
      for (char c : entrada) {
        if (!isdigit(c)) {//si no es un numero
          esValido = false;
          error="Error: Ingrese unicamente números";
          break; // Si se encuentra un carácter no numérico, salir del bucle
        }
      }
      if (esValido && entrada.size()>lineaDeCaptura.size()) {//si no es un numero
        esValido = false;
        error="Error: Ingrese maximo "+ to_string(lineaDeCaptura.size()) + " digitos";
      }
      if(error.size()>0){ // debido al stoul
      cout<<FG_RED;
      mensajeCentrado(error);
      }
      
    }while (!esValido);//mientras no sea valido se pide por mas numeros
    
return stoul(entrada);//se convierte de string a numero
}

/*Pantallas del menu*/
void Menus::primer_pantalla() {
  /*Primer Pantalla*/
  clrscr();//se limpia la pantalla
  //se declaran los nombres de los estudiantes
  Maestro blanca("Blanca Guadalupe Estrada Renteria", "Estructuras de Datos");
  Maestro   juan("Juan Pedro Cisneros Santoyo      ", "Programacion II");
  Alumno  miguel("Miguel Ángel Batres Luna   ", 350553, 3, 'A');
  Alumno    alan("Alan Gael Gallardo Jiménez ", 351914, 3, 'A');
  Alumno ernesto("Luis Ernesto López Cárdenas", 350346, 3, 'A');
  Alumno   ariel("Ariel Emilio Parra Martínez", 280862, 3, 'A');

  flecha_derecha();
  //se imprime el logo de la uaa a un costado
  const unsigned int altura_grafico = 16, ancho_grafico = 43;
  unsigned int x = (getmaxX() / 3) + (ancho_grafico / 3);
  unsigned int y = (getmaxY() / 2) - (altura_grafico / 3);
  logouaa();

  x = (getmaxX()/3) + 20;
  y = (getmaxY() / 2) - (altura_grafico / 3);

  gotoxy(x,y++); blanca.imprimirInformacion();
  gotoxy(x,y++); juan.imprimirInformacion();
  gotoxy(x,y++); 
  gotoxy(x,y++); miguel.imprimirInformacion();
  gotoxy(x,y++); alan.imprimirInformacion();
  gotoxy(x,y++); ernesto.imprimirInformacion();
  gotoxy(x,y++); ariel.imprimirInformacion();
  gotoxy(x,y++); 
  fflush(stdout);
}

void Menus::segunda_pantalla() {
  /*segunda Pantalla*/
  clrscr();
  flecha_izquierda();
  flecha_derecha();
  const int ancho_grafico1 = 88,altura_grafico=12;

  int x = (getmaxX() / 2) - (ancho_grafico1 / 2),y = (getmaxY() / 2) - (altura_grafico/2);
  cout<<FG_BLUE;
  gotoxy(x, y++); cout<<"░██████╗░█████╗░██╗░░░░░██╗░░░██╗░█████╗░██╗░█████╗░███╗░░██╗░█████╗░██████╗░░█████╗░██████╗ ";
  gotoxy(x, y++); cout<<"██╔════╝██╔══██╗██║░░░░░██║░░░██║██╔══██╗██║██╔══██╗████╗░██║██╔══██╗██╔══██╗██╔══██╗██╔══██╗";
  gotoxy(x, y++); cout<<"╚█████╗░██║░░██║██║░░░░░██║░░░██║██║░░╚═╝██║██║░░██║██╔██╗██║███████║██║░░██║██║░░██║██████╔╝";
  gotoxy(x, y++); cout<<"░╚═══██╗██║░░██║██║░░░░░██║░░░██║██║░░██╗██║██║░░██║██║╚████║██╔══██║██║░░██║██║░░██║██╔══██╗";
  gotoxy(x, y++); cout<<"██████╔╝╚█████╔╝███████╗╚██████╔╝╚█████╔╝██║╚█████╔╝██║░╚███║██║░░██║██████╔╝╚█████╔╝██║░░██║";
  gotoxy(x, y++); cout<<"╚═════╝░░╚════╝░╚══════╝░╚═════╝░░╚════╝░╚═╝░╚════╝░╚═╝░░╚══╝╚═╝░░╚═╝╚═════╝░░╚════╝░╚═╝░░╚═╝";
  
  gotoxy(x, y++);
  const int ancho_grafico2 = 70;
  x = (getmaxX() / 2) - (ancho_grafico2 / 2);
  cout<<FG_MAGENTA;
  gotoxy(x, y++); cout<<"██████╗░███████╗  ██╗░░██╗██╗░░░░░░█████╗░████████╗░██████╗██╗░░██╗██╗";
  gotoxy(x, y++); cout<<"██╔══██╗██╔════╝  ██║░██╔╝██║░░░░░██╔══██╗╚══██╔══╝██╔════╝██║░██╔╝██║";
  gotoxy(x, y++); cout<<"██║░░██║█████╗░░  █████═╝░██║░░░░░██║░░██║░░░██║░░░╚█████╗░█████═╝░██║";
  gotoxy(x, y++); cout<<"██║░░██║██╔══╝░░  ██╔═██╗░██║░░░░░██║░░██║░░░██║░░░░╚═══██╗██╔═██╗░██║";
  gotoxy(x, y++); cout<<"██████╔╝███████╗  ██║░╚██╗███████╗╚█████╔╝░░░██║░░░██████╔╝██║░╚██╗██║";
  gotoxy(x, y++); cout<<"╚═════╝░╚══════╝  ╚═╝░░╚═╝╚══════╝░╚════╝░░░░╚═╝░░░╚═════╝░╚═╝░░╚═╝╚═╝"<<RESET_COLOR;
  fflush(stdout);
}

void Menus::tercer_pantalla() {
  /*tercer Pantalla*/
  clrscr();
  flecha_izquierda();
  fflush(stdout);
  const int CantOpciones=4;
  const char *colores[CantOpciones] = {FG_CYAN, FG_MAGENTA, FG_BLUE, FG_YELLOW};
  const char *opciones1[CantOpciones] = {"█▀▀ ▄▀█ █▀█ █▀▀ ▄▀█ █▀█",  "▀█▀ ▄▀█ █▄▄ █   █▀▀ █▀█ █▀█","█▀ █▀█ █   █ █ █▀▀ █ █▀█ █▄ █","█▀ ▄▀█ █   █ █▀█"};
  const char *opciones2[CantOpciones] = {"█▄▄ █▀█ █▀▄ █▄█ █▀█ █▀▄",  " █  █▀█ █▄█ █▄▄ ██▄ █▀▄ █▄█","▄█ █▄█ █▄▄ █▄█ █▄▄ █ █▄█ █ ▀█","▄█ █▀█ █▄▄ █ █▀▄"};

  const int altura_grafico = 10, ancho_grafico = 35;
  int x = (getmaxX() / 2) - (ancho_grafico / 2),y = (getmaxY() / 2) - (altura_grafico/2);
 
  for (int i = 0; i < CantOpciones; i++) {
    cout<<colores[i];
    if (i == getSeleccion()) {
      gotoxy(x,y++);cout << "    ▀▄  " << opciones1[i];
      gotoxy(x,y++);cout << "▀▀▀▀▀█▀ " << opciones2[i];
      gotoxy(x,y++);cout << "    ▀   " << RESET_COLOR;
    } else {
      gotoxy(x,y++);cout << "        " << opciones1[i]; 
      gotoxy(x,y++);cout << "        " << opciones2[i];
      gotoxy(x,y++);cout << "        " << RESET_COLOR;
    }
  }
  fflush(stdout);

}

/*Pantallas incluidas en la tercer pantalla*/

unsigned int Menus::elegirNivel(){
clrscr();
bool nivelCargado=false;//para el while
unsigned int N=validarEntradaInt();
  do{
  Nivel nivel(N);
  if(!nivel.cargarNivel()){
    N=validarEntradaInt();
  }else{
    const string cargado="Nivel '" + to_string(N) + "' cargado con exito!";
    cout<<FG_GREEN;
    mensajeCentrado(cargado);
    nivelCargado=true;
    }//nivel cargado
  }while(!nivelCargado);
  return N;
}

void Menus::pantalla_Tabla(unsigned int numNivel){
  clrscr();
  Nivel nivel(numNivel);

  if(nivel.cargarNivel()){

    vector<string> matriz = nivel.getTableroNivel();

    Tabla tablaSolucion = Tabla(matriz);
    tablaSolucion.printTabla();
    gotoxy(getmaxX()/2 - nivel.getNombreNivel().size()/2, getmaxY()/2 - tablaSolucion.getAltoTablero()/2 - 2);
    cout<<nivel.getNombreNivel();
 
    gotoxy(getmaxX()/2 - tablaSolucion.getAnchoTablero()/2, getmaxY()/2 + tablaSolucion.getAltoTablero()/2 + 2);
    cout<<"Alto : "<< nivel.getAltoNivel();
    gotoxy(getmaxX()/2 - tablaSolucion.getAnchoTablero()/2, getmaxY()/2 + tablaSolucion.getAltoTablero()/2 + 3);
    cout<<"Ancho: "<< nivel.getAnchoNivel();
    const string regresar="Presione Cualquier tecla para regresar";
    gotoxy(getmaxX()/2 - regresar.size()/2, getmaxY()/2 + tablaSolucion.getAltoTablero()/2 + 5 );
    cout<<FG_BLUE<<regresar<<RESET_COLOR;fflush(stdout);
    getch();  
  }//nivel cargado
}

void Menus::pantalla_Solucion(unsigned int numNivel){
  clrscr();
  Nivel nivel(numNivel);
  if(nivel.cargarNivel()){
   vector<string> matriz = nivel.getTableroNivel();
    Tabla tablaSolucion = Tabla(matriz);
    
    //tablaSolucion.imprimirBloques();

    Klotski klotski = (tablaSolucion);
    unsigned int solucion = klotski.solucionador();
      clrscr();
      
      if(solucion!=0){
        const string mensajeSolucion="Solucion Encontrada!";
        cout<<FG_GREEN;
        mensajeCentrado(mensajeSolucion);
        klotski.printMovimientosSolucion(solucion,nivel.getNombreNivel());//pasos para la solucion
        const string regresar="Presione Cualquier tecla para regresar";
        gotoxy(getmaxX()/2 - regresar.size()/2, getmaxY()/2 + tablaSolucion.getAltoTablero()/2 + 5 );
        cout<<FG_BLUE<<regresar<<RESET_COLOR;fflush(stdout);
        getch(); 
      }
  }
}

/*funcion principal de menus*/
void Menus::principal(){
  //inializacion de variables
  const string error="Error: Cargue un Nivel primero";

  //while principal del menu
  while (!salir) {

    //switch de pantallas
    switch (getPantalla()) {
      case 1:
        primer_pantalla();
        break;
      case 2:
        segunda_pantalla();
        break;
      case 3:
        tercer_pantalla();
        break;
    }

    //switch de las teclas
    switch (getch()) {
      case KEY_LEFT:
      case 'a':
      case 'A':
        if (getPantalla() > 1) {
          this->pantalla--;
        }
        break;

      case KEY_RIGHT:
      case 'd':
      case 'D':
        if (getPantalla() < 3) {
          this->pantalla++;
        }
        break;

      case KEY_UP:
      case 'w':
      case 'W':
        if (getPantalla() == 3 && getSeleccion() > 0) {
          this->seleccion--;
        }
        break;

      case KEY_DOWN:
      case 's':
      case 'S':
        if (getPantalla() == 3 && getSeleccion() < 3) {
          this->seleccion++;
        }
        break;

      case KEY_ENTER:
      case ' '://tecla espaciadora

        if (getPantalla() == 3) {
          
          //switch de las opciones en la tercer pantalla
          switch (getSeleccion()) {
          case 0: // Cargar Nivel
            numNivel=elegirNivel();
            break;
          case 1: // Mostrar Tablero
            if(numNivel!=-1){
              pantalla_Tabla(numNivel);
            }else{ // no se ha cargado un nivel
              cout<<FG_RED;
              mensajeCentrado(error);
            }
            break;
          case 2: // Solucion del Tablero
            if(numNivel!=-1){
                pantalla_Solucion(numNivel);
            }else{ // no se ha cargado un nivel
                cout<<FG_RED;
                mensajeCentrado(error);
              }
            break;
          case 3: // Salir
            return; // regresar al main
            break;
        }// switch de las opciones en la tercer pantalla
      break;
      
      }//if pantalla==3
    }// switch de las teclas
  }//while principal del menu
}




