#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
using namespace std;

pthread_mutex_t lock;
int lista[40];

struct por
{
    int first;
    int second;    
};

void * qs(void * par)
{
    por *mi_par = (por *)par;
    int izq = mi_par->first, der = mi_par->second;

    int i = izq, j = der;
    int tmp;
    int mitad = lista[(izq + der) / 2];
    //do{
        //while(lista[i]< mitad && i< der)i++;
        //while(mitad < lista[j] && j > izq)j--;
    
    /* partition */
    while (i <= j) 
    {
        while (lista[i] < mitad)
            i++;
        while (lista[j] > mitad)
            j--;
        if (i <= j) 
        {
            tmp = lista[i];
            lista[i] = lista[j];
            lista[j] = tmp;
            i++;
            j--;
        }
    }//while(i<=j);
    //}
    por par1{izq,j}, par2{i, der};
    
    pthread_t* manejador_de_hilos;
    manejador_de_hilos = (pthread_t * )malloc( 2 * sizeof(pthread_t) );

    if (izq < j)
        pthread_create( &manejador_de_hilos[0], NULL, qs, (void *)&par1 );
    if (i < der)
        pthread_create( &manejador_de_hilos[1], NULL, qs, (void *)&par2 );        
    
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
          scanf("%d", &lista[i]);

    por par1{0,n-1};
    pthread_t* manejador_de_hilos;
    manejador_de_hilos = (pthread_t * )malloc( 1 * sizeof(pthread_t) );

    pthread_create( &manejador_de_hilos[0], NULL, qs, (void *)&par1 );
    pthread_join(manejador_de_hilos[0], NULL);

    free(manejador_de_hilos);

    for (int i = 0; i < n; ++i)
          printf("%d ", lista[i]);
    printf("\n");    
    return 0;
}

//$ g++ -std=c++11 -g -Wall -o A quicksort.c -lpthread
//$ ./A
