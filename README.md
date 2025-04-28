# Klotski Solver

This project is a **Klotski** puzzle solver that uses **DFS (Depth-First Search)** and **Backtracking** algorithms to find solutions to puzzle boards defined in `nivel_#.txt` files, where `#` is an integer from 1 to 99999. The program validates user input, checks the validity of the boards, and displays step-by-step how to solve the given Klotski board.

> [!IMPORTANT]  
> This project is made completely in spanish, the Code, Menus and on-screen instructions, all will be displayed only in **Spanish**.

![KlotskiSolver-Demo](KlotskiSolver-Demo.gif)

## Features

- **Search algorithms:** Implements DFS and Backtracking to find optimal solutions.
- **Board validation:** Ensures loaded boards are valid before attempting to solve them.
- **Console-based graphical interface:** Visual representation of the board and the moves made.
- **Cross-platform support:** Compatible with Windows and Unix-based systems (Linux, macOS) using the `ncurses` library.
- **Dynamic level loading:** Boards are loaded from external files without the need to recompile the program.
- **Solution indicators:** Displays the number of moves made and the path taken to solve the puzzle.

## Compilation

### On Windows

- Requires the `gcc` compiler, which can be obtained through **MSYS2**.
- To compile with the icon included, you can double-click the `Compilar_Con_ICONO.bat` script.

### On Linux/MacOS

- Requires the installation of the `ncurses` and `ncurses-dev` (or `ncurses-devel` on some distributions) libraries.
- To compile, simply run:

  ```bash
  make
  ```

### Using the Makefile

The project includes a `Makefile` that simplifies compilation and installation. Here are the most common commands:

- **Compile:**  
  ```bash
  make
  ```

- **Install:**

    On **Windows**, the executable will be installed to `C:\Users\$(USERNAME)\Desktop\`.  
    On **Linux**, the executable will be located in `/usr/local/bin/`, the icon in `/usr/share/icons/`, and desktop shortcuts in `/home/$(USER)/Desktop/`.

    ```bash
    make install
    ```

- **Uninstall:**  
  Removes the installed files.  
  ```bash
  make uninstall
  ```

- **Clean:**  
  Deletes the files generated during compilation.  
  ```bash
  make clean
  ```
