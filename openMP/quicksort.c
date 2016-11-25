#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int lista[20];


void QuickSort(int left, int right);

int main()
{     
    
    int n;
    while ( scanf("%d", &n)==1 )
    {
        for (int i = 0; i < n; ++i)
              scanf("%d", &lista[i]);

        QuickSort( 0, n-1 );

        for (int i = 0; i < n; ++i)
              printf("%d ", lista[i]);
        printf("\n");
    }
return 0;
}

void QuickSort(int left, int right) 
{
    int i = left, j = right;
    int tmp;
    int mitad = lista[(left + right) / 2];

    while (i <= j) 
    {
        while (lista[i] < mitad)
            i++;
        while (lista[j] > mitad)
            j--;
        if (i <= j) 
        {
            tmp =lista[i];
            lista[i] = lista[j];
            lista[j] = tmp;
            i++;
            j--;
        }
    };
	int numeroDeHilos=2;
    #pragma omp parallel for num_threads(numeroDeHilos)
    for (int w = 0; w < 2; ++w)
    {
        if (left < j && w)
            QuickSort(left, j);
        if (i < right && !w)
            QuickSort(i, right);
    }    
}
