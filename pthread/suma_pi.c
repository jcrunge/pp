#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int numeroDehilos;
double suma=0.0;
long long n=10000000;
void* sumaDepi(void* rank);

int main(int argc, char* argv[])
{
	long hilo;
    pthread_t* manejadorDehilos;

    numeroDehilos=strtol(argv[1], NULL, 10);
    manejadorDehilos=malloc(numeroDehilos*sizeof(pthread_t));

    for(hilo=0;hilo<numeroDehilos;hilo++){
        
        pthread_create(&manejadorDehilos[hilo], NULL, sumaDepi, (void*) hilo);

    }

    for(hilo=0; hilo<numeroDehilos; hilo++){
                
                pthread_join(manejadorDehilos[hilo], NULL);

    }

    double resultado=4*suma;
    printf("Suma %lf\n", resultado);



	return 0;
}

void* sumaDepi(void* rank){
	//n doble ser par

	long my_rank=(long)rank;
	double factor;
	long long i;

	long long my_n= n/numeroDehilos;
	long long mi_primer_elemento=my_n*my_rank;
	long long mi_ultimo_elemento=mi_primer_elemento+my_n;
	double my_suma=0.0;
	pthread_mutex_t mutex;
	pthread_mutex_init (&mutex, NULL);

	if (mi_primer_elemento%2 == 0)
	{
		factor=1.0;
	}

	else{

		factor=-1.0;
	}

	for(i=mi_primer_elemento; i<mi_ultimo_elemento;i++, factor=-factor){
		my_suma+=factor/(2*i+1);

	}

	pthread_mutex_lock(&mutex);

	suma+=my_suma;

	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);

	return NULL;


}