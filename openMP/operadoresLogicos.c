#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define EXTRACT_BIT(n,i) ((n&(1<<i))?1:0)

int cicuito (int my_rank, int z);

int main (int argc, char *argv[]) 
{
 	int	n = strtol(argv[1], NULL, 10);
	int i, posib, comparador_total;
	double solucion;	
	int circuito (int, int);
	solucion = 0;
	//las posibilidades (2^16)=65536
	posib = 65536;	
	#pragma omp parallel for num_threads(n) \
	 default(none) reduction(+:solucion) \
	 shared(posib)
	for (i =0; i < posib; i += n)
  		solucion += cicuito (I/*my_rank*/, i);
	
	//

	printf ("hay %d soluciones\n",comparador_total);
	return 0;
	}
int cicuito (int my_rank, int z) {
   int v[16];       
   int i;
   printf("Prosesando desde %d\n",my_rank); 	
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

