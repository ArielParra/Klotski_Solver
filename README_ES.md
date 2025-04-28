# Klotski Solver

Este proyecto es un solucionador del juego **Klotski** que utiliza algoritmos de **DFS (Depth-First Search)** y **Backtracking** para encontrar soluciones a tableros definidos en archivos `nivel_#.txt`, donde `#` es un número entero del 1 al 99999. El programa valida las entradas del usuario, verifica la validez de los tableros y muestra paso a paso cómo resolver el tablero de Klotski dado.

![KlotskiSolver-Demo](KlotskiSolver-Demo.gif)

## Características

- **Algoritmos de búsqueda:** Implementación de DFS y Backtracking para encontrar soluciones óptimas.
- **Validación de tableros:** Verifica que los tableros cargados sean válidos antes de intentar resolverlos.
- **Interfaz gráfica en consola:** Representación visual del tablero y los movimientos realizados.
- **Soporte multiplataforma:** Compatible con Windows y sistemas basados en Unix (Linux, macOS) usando la librería `ncurses`.
- **Carga dinámica de niveles:** Los tableros se cargan desde archivos externos sin necesidad de recompilar el programa.
- **Indicadores de solución:** Muestra el número de movimientos realizados y el camino recorrido para resolver el tablero.

## Compilación

### En Windows

- Es necesario contar con el compilador `gcc`, que puede obtenerse a través de **MSYS2**.
- Para compilar con el ícono incluido, puedes ejecutar el script `Compilar_Con_ICONO.bat` haciendo doble clic sobre él.

### En Linux/MacOS

- Se requiere instalar las librerías `ncurses` y `ncurses-dev` (o `ncurses-devel` en algunas distribuciones).
- Para compilar, simplemente ejecuta el comando:

  ```bash
  make
  ```

### Uso del Makefile

El proyecto incluye un archivo `Makefile` que facilita la compilación y la instalación. Aquí tienes los comandos más comunes:

- **Compilar:**  
  ```bash
  make
  ```

- **Instalación**

    En **Windows**, el ejecutable se instalará en `C:\Users\$(USERNAME)\Desktop\`.  
    En **Linux**, el ejecutable se ubicará en `/usr/local/bin/`, el icono en `/usr/share/icons/` y los accesos directos en el escritorio en `/home/$(USER)/Desktop/`.

    ```bash
    make install
    ```

- **Desinstalar:**  
  Elimina los archivos instalados.  
  ```bash
  make uninstall
  ```

- **Limpiar:**  
  Elimina los archivos generados durante la compilación.  
  ```bash
  make clean
  ```
