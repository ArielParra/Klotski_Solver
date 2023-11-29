
#include "Nivel.cpp"
//#define DEBUG_LINUX //debug para imprimir en Klotski solucionador

#include "Klotski.cpp"

/* 
// Implicitos dentro de Klotski.cpp
// si se incluyen da el error de: error: redefinition of...
#include "compatibilidad.h"
#include "TiposDeDatos.h"
#include "FuncionesAuxiliares.h"
#include "Bloque.cpp"
#include "Tabla.cpp"
*/

void elegirNivel(){
clrscr();
bool nivelCargado=false;//para el while

  do{
  unsigned int N=validarEntradaInt();
  Nivel nivel(N);
  if(!nivel.cargarNivel()){
    const string errorArchivo="Error: No se pudo abrir '" + nivel.getNombreArchivo() +"'";
    gotoxy(getmaxX()/2 - errorArchivo.size()/2, getmaxY()/2 + 1);
    cout<<FG_RED<<errorArchivo;fflush(stdout);
    recuadro();
    delay(2000);
    clrscr();
  }else{
    nivelCargado=true;
    /*cout<< "Nombre del Nivel: "<< nivel.getNombreNivel() <<endl;
    cout << "Tabla del archivo" << nivel.getNombreArchivo() << endl;
    cout << "getAnchoNivel " << nivel.getAnchoNivel() << endl;
    cout << "getAltoNivel " << nivel.getAltoNivel() << endl;*/
    vector<string> matriz3 = nivel.getTableroNivel();
    Tabla tablaSolucion = Tabla(matriz3);
    
    //tablaSolucion.imprimirBloques();

    Klotski klotski = (tablaSolucion);
    unsigned int solucion = klotski.solucionador();
    string mensajeSolucion;
      clrscr();
      if(solucion==0){
        gotoxy(getmaxX()/2 - 15/2 ,getmaxY()/2 );
        mensajeSolucion="No Existe Solucion!";
        gotoxy(getmaxX()/2 - mensajeSolucion.size()/2, getmaxY()/2 );
        cout<<FG_RED<<mensajeSolucion;fflush(stdout);
        recuadro();
        delay(2000);
        clrscr();
      }else{
        mensajeSolucion="Solucion Encontrada!";
        gotoxy(getmaxX()/2 - mensajeSolucion.size()/2, getmaxY()/2 );
        cout<<FG_GREEN<<mensajeSolucion;fflush(stdout);
        recuadro();
        delay(2000);
        clrscr();
        klotski.printMovimientosSolucion(solucion,nivel.getNombreNivel());//pasos para la solucion
      }
    }//nivel cargado
  }while(!nivelCargado);
}

inline void logouaa(){
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


inline void flecha_derecha() {
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
  gotoxy(x, y++); cout << "   ▒▒▒▒▒▒▒▒    "<<RESET_COLOR;
  fflush(stdout);

}

inline void flecha_izquierda() {
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
  gotoxy(x, y++); cout << "   ▒▒▒▒▒▒▒▒    "<<RESET_COLOR;
  fflush(stdout);
}

void primer_pantalla() {
  /*Primer Pantalla*/
  clrscr();
  flecha_derecha();
  const unsigned int altura_grafico = 16, ancho_grafico = 43;
  const unsigned int x = (getmaxX() / 3) + (ancho_grafico / 3);
  unsigned int y = (getmaxY() / 2) - (altura_grafico / 3);
  logouaa();
  gotoxy(x, y++);

  fflush(stdout);
}
void segunda_pantalla() {
  /*segunda Pantalla*/
  clrscr();
  flecha_izquierda();
  flecha_derecha();
  cout<<"segunda pantalla";
  fflush(stdout);
}
void tercer_pantalla() {
  /*tercer Pantalla*/
  clrscr();
  flecha_izquierda();
  cout<<"tercer pantalla, presiona enter para captura de nivel";
  fflush(stdout);
}

void menus(){
 int pantalla = 1, seleccion = 0;
  bool salir = false;
  while (!salir) {

    switch (pantalla) {
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

    switch (getch()) {
    case KEY_LEFT:
      if (pantalla > 1) {
        pantalla--;
      }
      break;
    case KEY_RIGHT:
      if (pantalla < 3) {
        pantalla++;
      }
      break;
    case KEY_UP:
      if (pantalla == 3 && seleccion > 0) {
        seleccion--;
      }
      break;
    case KEY_DOWN:
      if (pantalla == 3 && seleccion < 4) {
        seleccion++;
      }
      break;
    case KEY_ENTER: // windows
      if (pantalla == 3) {
        salir=true;
      }
      break;
      }//getch
    }// while
}
