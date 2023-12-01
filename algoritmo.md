

El algoritmo utilizado en el código implementa una búsqueda de solución utilizando la técnica de Depth-First Search (DFS) con Backtracking. A continuación, se explica paso a paso:

# 1. **Inicialización de la Tabla y la Memoria:**
   - Se crea una instancia de la clase `Klotski` con la tabla de juego proporcionada como argumento.
   - La memoria (`unordered_map`) se inicializa con el hash del estado inicial de la tabla y se marca como "en progreso" (`EN_PROGRESO`).

# 2. **Búsqueda de Solución (DFS con Backtracking):**
   - Se realiza una iteración sobre todas las piezas en el tablero para explorar posibles movimientos y configuraciones en el ciclo for.
   - Para cada pieza, se selecciona una dirección inicial y se intenta mover la pieza en esa dirección.
   - Si el movimiento es válido y lleva a un nuevo estado del tablero, se calcula el hash de ese nuevo estado y se procede a explorar desde ese nuevo estado llamando recursivamente a la función `buscarSolucion`.
   - Se almacena la información del nuevo estado en la memoria, marcándolo como "en progreso" y registrando la profundidad, el último hash y el último movimiento realizado.
   - Si se encuentra una solución (por ejemplo, si la pieza singular llega a la posición objetivo), se registra como "solución encontrada" (`SOLUCION_ENCONTRADA`) y se devuelve el hash del estado actual.
   - Si no se encuentra una solución desde el estado actual, se utiliza la técnica de Backtracking: se retrocede al estado anterior y se continúa explorando desde ese punto.
   - Para definir Si no Existe solucion se toma en cuenta el limite de (`LIMITE_DE_PROFUNDIDAD`) y también se considera si no se pueden mover las piezas

# 3. **Impresión de la Solución:**
   - Una vez encontrada la solución, se utiliza la información almacenada en la memoria para reconstruir la secuencia de movimientos realizados desde el estado inicial hasta el estado final.
   - Se crea una Tabla Para imprimir los tableros con respecto a los movimientos.
   - Se utiliza una pila (`stack`) para almacenar los movimientos en orden inverso (desde el final hasta el principio).
   - Se imprime cada tablero moviendo la pieza correspondiente a la pila.
   - Se imprime cada movimiento, incluyendo la pieza movida, la dirección y el paso en el que se realizó.

En resumen, el algoritmo realiza una búsqueda exhaustiva del espacio de estados, utilizando la técnica DFS para explorar en profundidad y el Backtracking para retroceder cuando se alcanzan situaciones sin solución desde un estado particular. La memoria se utiliza para evitar explorar estados ya visitados, mejorando la eficiencia del algoritmo.


