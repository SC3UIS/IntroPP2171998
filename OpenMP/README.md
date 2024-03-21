
# Descripción del Repositorio

Este repositorio proporciona un ejemplo de cómo paralelizar un código en C utilizando OpenMP, generar una reserva interactiva en GuaneExa (un entorno de computación de alto rendimiento), compilar el archivo OpenMP y evaluar los resultados.

Incluye un archivo de código en C que implementa un algoritmo paralelizable, junto con un script sbatch que configura una reserva interactiva en GuaneExa y compila el código utilizando OpenMP. Además, se proporciona una guía detallada paso a paso sobre cómo utilizar OpenMP para paralelizar el código, cómo solicitar una reserva interactiva en GuaneExa utilizando sbatch y cómo evaluar los resultados obtenidos.

Este repositorio es útil para aquellos que deseen aprender sobre programación paralela con OpenMP y cómo trabajar con sistemas de computación de alto rendimiento como GuaneExa.


# Descripción de los Cambios entre el Código No Paralelizado y el Paralelizado con OpenMP

El código original en C implementa un algoritmo de búsqueda binaria y ordenamiento de burbuja de manera secuencial. Sin embargo, para mejorar el rendimiento y aprovechar mejor los recursos de hardware disponibles en sistemas con múltiples núcleos de CPU, se ha paralelizado el código utilizando OpenMP.

Las diferencias principales entre el código no paralelizado y el paralelizado con OpenMP son:

1. **Uso de Directivas OpenMP**: En el código paralelizado, se agregan directivas OpenMP para identificar secciones del código que se pueden ejecutar en paralelo. Estas directivas incluyen pragmas como `#pragma omp parallel`, `#pragma omp for`, `#pragma omp sections`, entre otros, que permiten especificar cómo se debe dividir el trabajo entre los hilos de ejecución.

2. **Compartición de Recursos**: Con OpenMP, se pueden especificar variables compartidas y privadas para controlar cómo se comparten los datos entre los hilos de ejecución. Esto se logra utilizando cláusulas como `shared` y `private` en las directivas OpenMP para garantizar la consistencia de los datos y evitar condiciones de carrera.

3. **Paralelización de Bucles**: En el código paralelizado, se identifican bucles que pueden ejecutarse en paralelo y se utilizan directivas OpenMP como `#pragma omp parallel for` para distribuir el trabajo entre los hilos de ejecución. Esto permite aprovechar los recursos de hardware disponibles y acelerar la ejecución del programa.

En resumen, el código paralelizado con OpenMP aprovecha la capacidad de procesamiento paralelo de sistemas con múltiples núcleos de CPU para mejorar el rendimiento y la eficiencia del algoritmo, en comparación con la versión secuencial del código.

```c
void bubble_sort(int list[], int size)
{
    int temp, i, j;

    #pragma omp parallel for private(i,j,temp)
    for (i = 0; i < size; i++)
    {
        for (j = i; j < size; j++)
        {
            if (list[i] > list[j])
            {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}
```
## Cambios Realizados en el Código

Se han realizado los siguientes cambios en el código:

- Se agregó la función `srand((unsigned int)time(NULL))` para sembrar una semilla basada en el tiempo actual. Esto garantiza que se generen diferentes secuencias de números aleatorios en cada ejecución del programa.

- Se utilizó un bucle para generar números aleatorios y llenar la lista con ellos. Esto asegura que el output del programa contenga una salida y no este vacia o diga key not found.

## Adicionales
Luego se genero una reserva interactiva desde toctoc a GuaneExa usando:
```sh
srun -n 10 -w ExaDELL --pty /bin/bash
```

Una vez alli se procede a compilar con GCC los archivos .c tanto de base para probar y de OMP para compilar y validar.
Luego se escribe el codigo del SBATCH siendo: 
```sbatch
#!/bin/bash
#SBATCH --job-name=OMP_BinarySearch
#SBATCH --output=output_BinarySearch.txt
#SBATCH --error=binary_search_error.txt
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --time=00:10:00
gcc -o OMP_BinarySearch OMP_BinarySearch.c -fopenmp
./OMP_BinarySearch

```
Finalmente de la practica obtenemos todos los archivos construidos y una vez ejecutado el el archivo obtenemos como salida 

```
Enter size of a list: Generated elements: 46 85 81 22 31 57 63 61 12 1 54 0 73 71 76 73 20 15 0 91 60 45 21 13 33 20 91 13 21 19 65 20 56 99 42 39 56 6 53 20 7 7 72 80 79 48 53 51 63 6 
Enter key to search: Key found
```