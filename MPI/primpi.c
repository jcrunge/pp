#include<stdio.h>
#include<string.h>
#include<mpi.h>
#include<stdlib.h>
#define MAESTRO 0

const int MAX_STRING=10000;

int main(void){
        int arreglo_enteros[MAX_STRING];
        int bandera[MAX_STRING];
        int total[MAX_STRING];
        int comm_sz;
        int my_rank;
        int resultado=0;
        double inicio, fin;

        for (int i = 0; i < MAX_STRING; ++i)
        {
                arreglo_enteros[i]=i;
        }

        MPI_Init(NULL, NULL);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
        MPI_Comm_rank(MPI_COMM_WORLD, & my_rank);

        int tareas=MAX_STRING%comm_sz;
        int tamanioDePedazos=(MAX_STRING/comm_sz);
        int recorrido=tamanioDePedazos;


                if(my_rank == MAESTRO){

                       
                        

                        for (int q = 1; q < comm_sz; ++q)
                        {
                                MPI_Send(&recorrido, 1, MPI_INT, q, 0, MPI_COMM_WORLD);
                                MPI_Send(&arreglo_enteros[recorrido], tamanioDePedazos, MPI_INT, q, 0, MPI_COMM_WORLD);
                                recorrido=recorrido+tamanioDePedazos;
                        }

                        recorrido=tamanioDePedazos;
                        for(int q=1; q<comm_sz; q++){
                        
                        	MPI_Recv(&arreglo_enteros[recorrido], tamanioDePedazos, MPI_INT, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        	for(int i=0; i<tamanioDePedazos;i++)
                        		if(arreglo_enteros[recorrido+i]=!0){
                        			printf("%d\n",arreglo_enteros[recorrido+i] );
                        		}
                          	
                          	recorrido=recorrido+tamanioDePedazos;
                        }

                        
                       
                }

                if(my_rank>MAESTRO){

                        int suma=0;
                        MPI_Recv(&recorrido, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        MPI_Recv(&arreglo_enteros[recorrido], tamanioDePedazos, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                        for (int i = 0; i < recorrido; ++i)
                        {
                        	for(int j=0; j<i;j++){
                        		if(i%j==0)
                                suma++;
                        	}
                        	if(suma>2)
                        		arreglo_enteros[i]=0;
                        	else
                        		arreglo_enteros[i]=i;
                        }

                        MPI_Send(&recorrido, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
                        MPI_Send(&arreglo_enteros[recorrido], tamanioDePedazos, MPI_INT, 0, 0, MPI_COMM_WORLD);
                }
MPI_Finalize();
        return 0;
}