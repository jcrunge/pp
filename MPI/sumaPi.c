#include <stdio.h>
#include <mpi.h>
#include <math.h>

double dx_arctan(double x);

int main(void)
{
	double aprox, pi;
	double sum , pi_approx;
	int comm_sz;
	int rank;
    MPI_Init(NULL, NULL); 
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    
	if (rank == 0) {
		int n =100000;
		MPI_Bcast(&n, 1, MPI_INT, 0,MPI_COMM_WORLD);
		//printf("calculando pi apartir de %d procesos: ", comm_sz);
 		MPI_Allreduce(&pi_approx, &pi, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
		printf("el valor aproximado de PI es: %f\n", pi);

	}

	
	if(rank  > 0){
		int n;
		MPI_Bcast(&n, 1, MPI_INT, 0,MPI_COMM_WORLD);
		// Calculo de PI
		aprox = 1.0/n;
		sum = 0.0;
		for (int i = rank + 0.5; i < n; i += comm_sz) {
			sum += dx_arctan(i*aprox);
		}
		pi_approx = 4.0*aprox*sum;
		MPI_Allreduce(&pi_approx, &pi, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	}
	MPI_Finalize(); 
    return 0;
}

double dx_arctan(double x)
	{    
		return (1.0 / (1.0 + x*x));
	} 

//mpicc -std=c99 -o sumpi sumaPi.c
//mpiexec -n  150 ./sumpi
