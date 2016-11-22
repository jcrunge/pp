#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int v[40];


//void QuickSort(int left, int right);

void QuickSort(int left, int right) 
{
    int i = left, j = right;
    int tmp;
    int pivote = v[(left + right) / 2];

    while (i <= j) 
    {
        while (v[i] < pivote)
            i++;
        while (v[j] > pivote)
            j--;
        if (i <= j) 
        {
            tmp = v[i];
            v[i] = v[j];
            v[j] = tmp;
            i++;
            j--;
        }
    };
    #pragma omp parallel for num_threads(numeroDeHilos)
    for (int w = 0; w < 2; ++w)
    {
        if (left < j && w)
            QuickSort(left, j);
        if (i < right && !w)
            QuickSort(i, right);
    }    
}


int main()
{     
    int numeroDeHilos=2;
    int n;
    while ( scanf("%d", &n)==1 )
    {
        for (int i = 0; i < n; ++i)
              scanf("%d", &v[i]);

        QuickSort( 0, n-1 );

        for (int i = 0; i < n; ++i)
              printf("%d ", v[i]);
        printf("\n");
    }
return 0;
}
