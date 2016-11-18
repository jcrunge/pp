#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


void sumaPi(void);


int main(int argc, char *argv[])
{

	int	n = strtol(argv[1], NULL, 10);
	double factor;
	double sum = 0.0, pi_approx;
	int k;
	#pragma omp parallel for num_threads(n) \
	 default(none) reduction(+:sum) private(k, factor) \
	 shared(n)
	for(k= 0; k<n; k++){
		if(k%2 == 0){
			factor=1.0;
		}

		else{

			factor=-1.0;
		}	
		sum += factor / (2*k+1);	
	}

	pi_approx = 4.0*sum;
	printf("Suma %lf\n", pi_approx);

	return 0;
}
