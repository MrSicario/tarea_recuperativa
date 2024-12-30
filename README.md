# Tarea Recuperativa README

## Requerimientos

### C++

- Compilador compatible con C++23 o superior.
- CMake

## Python

- Matplotlib
- json

## Compilación

Utilizar CMake para armar y compilar la tarea.

## Ejecución

Correr el archivo ejecutable de la tarea, los 4 experimentos corren de forma automatica.  
El programa imprime en consola los resultados de cada experimento y los almacena en `log.txt`, ubicado en el mismo directorio del ejecutable.

Para generar los gráficos, se requiere el archivo `data.json` y que siga la misma estructura. Se puede alterar los datos con los obtenidos de distintas ejecuciones del archivo compilado pero no hay una forma automática de traspasar los datos de `log.txt` a `data.json`