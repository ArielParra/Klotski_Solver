El algoritmo utilizado en el código implementa una búsqueda de solución utilizando la técnica de Depth-First Search (DFS) con Backtracking. A continuación, se explica paso a paso:

# 1. **Inicialización de la Tabla y la Memoria:**
   - Se crea una instancia de la clase `Klotski` con la tabla de juego proporcionada como argumento.
   - La memoria (`unordered_map`) se inicializa con el hash del estado inicial de la tabla y se marca como "en progreso" (`EN_PROGRESO`).

# 2. **Búsqueda de Solución (DFS con Backtracking):**
   - Se realiza una iteración sobre todas las piezas en el tablero para explorar posibles movimientos y configuraciones.
   - Para cada pieza, se selecciona una dirección inicial aleatoria y se intenta mover la pieza en esa dirección.
   - Si el movimiento es válido y lleva a un nuevo estado del tablero, se calcula el hash de ese nuevo estado y se procede a explorar desde ese nuevo estado llamando recursivamente a la función `buscarSolucion`.
   - Se almacena la información del nuevo estado en la memoria, marcándolo como "en progreso" y registrando la profundidad, el último hash y el último movimiento realizado.
   - Si se encuentra una solución (por ejemplo, si la pieza singular llega a la posición objetivo), se registra como "solución encontrada" (`SOLUCION_ENCONTRADA`) y se devuelve el hash del estado actual.
   - Si no se encuentra una solución desde el estado actual, se utiliza la técnica de Backtracking: se retrocede al estado anterior y se continúa explorando desde ese punto.

# 2.1 **Mas detalles:**

### 2.1 Más Detalles:

#### 2.1.1 Inicio:
- El algoritmo comienza explorando el nodo actual, que representa el estado actual del problema.

#### 2.1.2 Generación de Movimientos:
- Para cada movimiento posible desde el estado actual:
  - Verifica si el movimiento es válido.

#### 2.1.3 Actualización del Estado:
- Si el movimiento es válido, se realiza y se genera un nuevo estado.

#### 2.1.4 Manejo de la Memoria:
- Calcula el hash del nuevo estado y verifica en la memoria:
  - Si el nuevo estado no está en la memoria, se agrega con la marca "en progreso".
  - Si el nuevo estado ya está en la memoria marcado como "resuelto", se ignora este camino.
  - Si el nuevo estado está en la memoria marcado como "en progreso", se ha encontrado un ciclo, y se realiza backtracking.

#### 2.1.5 Llamada Recursiva:
- Se realiza una llamada recursiva para explorar más profundamente con el nuevo estado.

#### 2.1.6 Verificación de Solución:
- Si la llamada recursiva devuelve verdadero, se ha encontrado una solución, y se termina la búsqueda.

#### 2.1.7 Manejo de Backtracking:
- Si la llamada recursiva devuelve falso, se revierte el movimiento y se continúa con el siguiente movimiento posible.

#### 2.1.8 Marcado de Estado y Backtracking:
- Si se han explorado todos los movimientos posibles y no se ha encontrado una solución, se marca el estado actual como "resuelto" en la memoria y se realiza backtracking.

### Este proceso se repite hasta que se haya explorado todo el espacio de búsqueda o se haya encontrado una solución. Es importante destacar que el backtracking es esencial para deshacer los movimientos y explorar diferentes caminos cuando la búsqueda no conduce a una solución.


# 3. **Impresión de la Solución:**
   - Una vez encontrada la solución, se utiliza la información almacenada en la memoria para reconstruir la secuencia de movimientos realizados desde el estado inicial hasta el estado final.
   - Se crea una Tabla Para imprimir los tableros con respecto a los movimientos.
   - Se utiliza una pila (`stack`) para almacenar los movimientos en orden inverso (desde el final hasta el principio).
   - Se imprime cada tablero moviendo la pieza correspondiente a la pila.
   - Se imprime cada movimiento, incluyendo la pieza movida, la dirección y el paso en el que se realizó.

# 4. **Consideraciones Específicas del Código:**
   - Se utiliza un hash para representar el estado del tablero, lo que permite almacenar eficientemente información en la memoria y evitar la exploración repetida de los mismos estados.
   - Se utiliza la estructura `Solucion` para almacenar información sobre el estado actual, incluyendo el tipo de solución, la profundidad, el último hash y el último movimiento realizado.


En resumen, el algoritmo realiza una búsqueda exhaustiva del espacio de estados, utilizando la técnica DFS para explorar en profundidad y el Backtracking para retroceder cuando se alcanzan situaciones sin solución desde un estado particular. La memoria se utiliza para evitar explorar estados ya visitados, mejorando la eficiencia del algoritmo.
