#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
using namespace std;

pthread_mutex_t lock;
int arr[40];

struct por
{
    int first;
    int second;    
};

void * quickSort(void * par)
{
    por *mi_par = (por *)par;
    int izq = mi_par->first, der = mi_par->second;

    int i = izq, j = der;
    int tmp;
    int pivote = arr[(izq + der) / 2];

    /* partition */
    while (i <= j) 
    {
        while (arr[i] < pivote)
            i++;
        while (arr[j] > pivote)
            j--;
        if (i <= j) 
        {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }

    por par1{izq,j}, par2{i, der};
    
    pthread_t* manejador_de_hilos;
    manejador_de_hilos = (pthread_t * )malloc( 2 * sizeof(pthread_t) );

    if (izq < j)
        pthread_create( &manejador_de_hilos[0], NULL, quickSort, (void *)&par1 );
    if (i < der)
        pthread_create( &manejador_de_hilos[1], NULL, quickSort, (void *)&par2 );        
    
    pthread_join(manejador_de_hilos[0], NULL);
    pthread_join(manejador_de_hilos[1], NULL);
    
    //liberar memoria
    free(manejador_de_hilos);
    return NULL;
}


int main()
{     
    int n;    
    
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
          scanf("%d", &arr[i]);

    por par1{0,n-1};
    pthread_t* manejador_de_hilos;
    manejador_de_hilos = (pthread_t * )malloc( 1 * sizeof(pthread_t) );

    pthread_create( &manejador_de_hilos[0], NULL, quickSort, (void *)&par1 );
    pthread_join(manejador_de_hilos[0], NULL);

    free(manejador_de_hilos);

    for (int i = 0; i < n; ++i)
          printf("%d ", arr[i]);
    printf("\n");    
    return 0;
}

//$ g++ -std=c++11 -g -Wall -o A quicksort.c -lpthread
//$ ./A
