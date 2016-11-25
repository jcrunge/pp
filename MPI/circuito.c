#include <mpi.h>
#include <stdio.h>
#define EXTRACT_BIT(n,i) ((n&(1<<i))?1:0)

int cicuito (int my_rank, int z);

int main (int argc, char *argv[]) 
{
 
	int i, my_rank, comm_sz, posib, comparador_total, solucion;	
	int circuito (int, int);
	MPI_Init (&argc, &argv);
	MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size (MPI_COMM_WORLD, &comm_sz);
	solucion = 0;
	//las posibilidades (2^16)=65536
	posib = 65536;	
	for (i = my_rank; i < posib; i += comm_sz)
  		solucion += cicuito (my_rank, i);
	
	MPI_Reduce (&solucion,&comparador_total,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	//printf("Prosesando desde %d\n",my_rank);
	fflush (stdout);
	MPI_Finalize();

	if (my_rank==0)
		printf ("hay %d soluciones\n",comparador_total);
		return 0;
	}

int cicuito (int my_rank, int z) {
   int v[16];       
   int i;

   for (i = 0; i < 16; i++) v[i] = EXTRACT_BIT(z,i);

   if ((v[0] || v[1]) && (!v[1] || !v[3]) && (v[2] || v[3])
      && (!v[3] || !v[4]) && (v[4] || !v[5])
      && (v[5] || !v[6]) && (v[5] || v[6])
      && (v[6] || !v[15]) && (v[7] || !v[8])
      && (!v[7] || !v[13]) && (v[8] || v[9])
      && (v[8] || !v[9]) && (!v[9] || !v[10])
      && (v[9] || v[11]) && (v[10] || v[11])
      && (v[12] || v[13]) && (v[13] || !v[14])
      && (v[14] || v[15])) 
      return 1;
      else
      return 0;
}


