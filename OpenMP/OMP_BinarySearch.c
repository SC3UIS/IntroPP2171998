/*

  Purpose:

    TRANSFORM is an example of a transformation of an EDP using some parameters for Intro PP Students.

  Example:

    31 May 2001 09:45:54 AM

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    24 September 2003

  Author:
  George 
  OpenMP Modification:
  24 March 2024 by Carlos Sanjuan, Universidad Industrial de Santander carlos2171998@correo.uis.edu.co                   
  This OpenMP Modification makes a parallelization of the original Code...  
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Necesario para la función time
#include <omp.h>

void binary_search(int [], int, int, int);
void bubble_sort(int [], int);

int main()
{
    int key, size, i;
    int list[50];

    printf("Enter size of a list: ");
    size = 50;

    // Generar números aleatorios para llenar la lista
    srand((unsigned int)
    time(NULL)); // Inicializar la semilla
    printf("Generated elements: ");
    for(i = 0; i < size; i++)
    {
        list[i] = rand() % 100; // Rango de números aleatorios de 0 a 99
        printf("%d ", list[i]); // Mostrar los números generados
    }
    printf("\n");

    printf("Enter key to search: ");
    scanf("%d", &key);

    bubble_sort(list, size);

    #pragma omp parallel
    {
        #pragma omp single
        {
            binary_search(list, 0, size, key);
        }
    }

}

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

void binary_search(int list[], int lo, int hi, int key)
{
    int mid;

    if (lo > hi)
    {
        printf("Key not found\n");
        return;
    }
    mid = (lo + hi) / 2;
    if (list[mid] == key)
    {
        printf("Key found\n");
    }
    else if (list[mid] > key)
    {
        binary_search(list, lo, mid - 1, key);
    }
    else if (list[mid] < key)
    {
        binary_search(list, mid + 1, hi, key);
    }
}
