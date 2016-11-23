#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

long long tam;
bitset<10000010> es_primo;
vector <int> primos;
int num_hilos;
void criba()
{
	tam = 10000001;
	es_primo.set();
	es_primo[0] = es_primo[1] = 0;
	for (long long i = 2; i <= tam; i++) 
		if (es_primo[i]) 
		{		
			#pragma omp parallel for num_threads(num_hilos)
			for (long long j = i * i; j <= tam; j += i) 
				es_primo[j] = 0;			
			primos.push_back((int)i);
		} 
}

int main(int argc, char const *argv[])
{	
	//recibir el numero de hilos a crear
	num_hilos = strtol(argv[1],NULL,10)	;

	criba();
	for (auto &p: primos)
		printf("%d\n", p );
	return 0;
}
//$ g++ -std=c++11 -g -Wall -fopenmp -o A criba.cpp
//$ ./A 5 > salida.out
