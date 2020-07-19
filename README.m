# Generacion de archivos para graficar estructura de bandas y densidad de estados

El programa properties, parte del codigo Crystal, puede generar la información de estructura de bandas y densidad de estados a partir de la información de la función de onda de un sistema periódico.

Esta información la almacena en el archivo fort.25 (o con extension .f25), pero en el formato en el que se encuentra no es trivial graficar su contenido con algun programa graficador, como por ejemplo gnuplot. Por ello, necesitamos convertir estos archivos a otros mas legibles, aprovechando además para obtener datos como el band gap.

# Estructura

Cuando se calcula la estructura de bandas o la densidad de estados el archivo fort.25 generado tiene varias similitudes. La estructura que sigue en el caso de las bandas es la siguiente:

Linea 1) Un símbolo '-%-',un digito que indica si el cálculo fue de capa cerrada o abierta y de un sistema conductor o aislante,'BAND',el numero de bandas,numero de puntos k del muestreo,un numero que no se usa, distancia entre los pasos de muestreo, energía de Fermi (en Hartree)

Linea 2) energía mínima de las bandas en el camino explorado, energía maxima.

Linea 3) coordinadas del segmento (tres numeros para la coordenada inicial, y tres para la coordenada final)

Linea 4) matriz con eigenvalores (en hartrees)

Ejemplo)

-%-0BAND   20   43 0.00000E+00 1.07738E-02-1.62669E-01
-2.46244E-01 1.42585E-01
    0    0    0    1   -1    0
-2.31033E-01-2.28420E-01-2.14544E-01-2.09788E-01-1.96924E-01-1.94207E-01
...

------------
En el caso de la densidad de estados (DOS):

Linea 1) Un símbolo '-%-',un digito que indica si el cálculo fue de capa cerrada o abierta y de un sistema conductor o aislante,'DOSS',un '1',numero de valores de energía donde se calcula la DOS,el incremento entre valores,un numero que no se usa,energía de Fermi (en Hartree)

Linea 2) energía del inicio, un numero que no se usa

Linea 3) numero de proyeccion, numero de orbitales atomicos de la proyeccion, 4 numeros que no se usan

Linea 4) matriz con DOS

Ejemplo)

-%-0DOSS    1  502 0.00000E+00 5.19125E-04-1.48445E-01
 0.00000E+00-1.72323E-01
     1  682    0    0    0    0
 0.00000E+00 6.57323E-13 7.83424E+00 1.83106E+01 3.75469E+01 6.15580E+01
...

------------

# El programa

Hay dos programas que leen esta información: lectura_bandas_crystal y lectura_dos_crystal. En su estado actual, ambos necesitan que se agregue una linea al inicio del archivo fort.25:

* Para las bandas, se debe agregar el numero de bandas de valencia
* Para la densidad de estados, se agrega el eigenvalor de la última banda de valencia.

La forma en la que se ejecutan ambos programas es:

>./lectura_prop_crystal < fort.25

La salida del programa son los datos para los gráficos, en un formato adecuado (deben redireccionarse a un archivo con '>' para su uso posterior).

# Proyecto

Hay que integrar ambos programas en uno solo, donde no sea necesario editar el archivo fort.25. Además, es importante que podamos usar este programa para muchos archivos, como en el siguiente ejemplo:

> for i in $(ls *f25); do ./lectura_prop_crystal < $i > salida-$i; done

En su estado actual de ambos programas esto se puede hacer; al realizar cambios hay que cuidar que esto aún pueda realizarse, ya sea de esta u otra manera.

Como un primer paso, hay que concentrarse en lectura_band, ya que lectura_dos necesita (por ahora) de un valor que da lectura_band.

Para este primer paso, un consejo es fijarse en como se calcula el valor del band gap, y pensar como es su valor si el numero de bandas de valencia es menor o mayor al adecuado. Esto puede ser útil, más no necesariamente el camino a la mejor solución.
