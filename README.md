# Descripcion 

Este es un programa el cual busca solucion a travez de DFS y Backtracking a tableros del juego Klotski obtenidos de los archivos nivel_#.txt siendo # un numero entero del 1 al 99999, el programa valida las entradas de usuario, valida los tableros y muestra los pasos para resolver el tablero de klotski dado. 

# Compilacion

En Windows es necesario el compilador gcc, el cual puede obtenerse a travez de MSYS2, para compilar junto con el icono diseñe un batch script llamado Compilar_Con_ICONO.bat el cual se puede ejecutar dando doble click derecho.
Para compilar en sistemas basados en Unix como MacOS o Linux, se requiere de las librerias de ncurses y ncurses-dev, se puede compilar ejecutando el comando "make"

---

# Requisitos del proyecto


## Codigo

- [x] Debe aplicar todos temas vistos en el curso
- [x] menús claros y validados.
- [x] Validar las capturas (que no existan errores de ejecución, es decir, que no “truene” el programa).
- [x] Cada sección de código del programa debe estar perfectamente bien comentada, es decir, cada función
o clase debe tener comentarios acerca de lo que se realiza.
- [x]  Los nombres de las funciones o clases deben ser de acuerdo a la funcionalidad que implementa.
- [x] Graficos hasta 2 pts extra
- [x] La solución debe cargar nuevos tableros y resolverlo sin necesidad de recompilar el ejercicio.
    - [x] Al cargar el tablero el programa deberá dibujarlo en forma gráfica y generar la(s) solución(es) posible(s).
- [x] La pantalla del juego contendrá al menos:
    - [x] El tablero vacío.
    - [x] Método de carga del archivo (reto).
    - [x] Dibujar el tablero completo.
    - [x] Botón para general solución e Iniciar recorrido.
 - [x] Las piezas y los muros se representarán de modo que aparezcan conexos, inclusive si ocupan varios cuadrados del tablero.
 - [x] Cada pieza diferente que se mueve se considera un movimiento. Al mover una pieza que acaba de ser movida se considera que es una continuación del movimiento anterior, y no cuenta como movimiento.
 - [x] Al final deberá indicar cuantos movimientos realizo para solucionar el reto, así como el camino recorrido para la solución

## Documento

- [x] Portada
    - [x] Imagen con título de la UAA
    - [x] Título del proyecto
    - [x] Nombre de la materia
    - [x] Nombres de los integrantes
    - [x] Carrera, semestre y grupo
    - [x] Nombre del profesor
    - [x] Fecha de entrega
- [x] Resumen descriptivo 
    - [x] Fortalezas
    - [x] Debilidades
    - [x] redactar con sus propias palabras
    - [x] justificar sus comentarios
- [x] Temas investigados para la realización del proyecto.
- [x] Bitácora de trabajo por cada uno de los integrantes del equipo.
    - [x]Hacer una tabla donde incluyan el nombre del integrante del equipo, actividades realizadas y tiempo (días)
- [x] Conclusiones por cada uno de los integrantes del equipo.
    - [x] Conlcusion de Ariel
- [x] Referencias consultadas.
- [x] Manual de usuario
    - [x] capturas de pantalla
    - [x] como se realiza cada tarea de su aplicación

## Programacion Orientada a Objetos

- [x] Uso de los 4 pilares de la POO
    - [x] Abstraccion
    - [x] Encapsulamiento
    - [x] Herencia
    - [x] Polimorfismo 
- [x] Separacion de la interfaz y la implementación
- [x] Uso de métodos amigos
- [x] Uso de métodos const