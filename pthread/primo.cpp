#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

long long tam;
bitset<10000010> es_primo;
vector <int> primos;
int num_hilos;
pthread_t* manejador_de_hilos;
long c;
long long i;

void * tachar(void * hilo)
{	
	long long mi_hilo = (long long)hilo;
	long long ini = i*i + (mi_hilo )*c*i;
	long long fin = min(tam,ini + c*i);
	
	for ( ;ini < fin; ini += i) 
		es_primo[ini] = 0;
	return NULL;
}

void criba()
{
	tam = 10000001;	
	es_primo.set();
	es_primo[0] = es_primo[1] = 0;
	
	for (i = 2; i < tam; i++) 
		if (es_primo[i]) 
		{		
			primos.push_back((int)i);
			if (i*i>tam) continue;

			c = max((tam - i*i)/i + 1, 1LL);
			c /= num_hilos;
			++c;

			for (long long hilo = 0; hilo < num_hilos; ++hilo)
				pthread_create( &manejador_de_hilos[hilo], NULL, tachar, (void *)hilo );

			for (long long hilo = 0; hilo < num_hilos; ++hilo)
				pthread_join(manejador_de_hilos[hilo], NULL);
					
		}
	return;
}

int main(int argc, char const *argv[])
{	
	//recibir el numero de hilos a crear
	num_hilos = strtol(argv[1],NULL,10);	
	
	manejador_de_hilos = (pthread_t * )malloc( num_hilos * sizeof(pthread_t) );
	
	criba();
	
	for (auto &p: primos)
		printf("%d\n", p );
	
	//liberar memoria
	free(manejador_de_hilos);	
	return 0;
}
//$ g++ -std=c++11 -g -Wall -o A criba.cpp -lpthread
//$ ./A 5 > salida.out
