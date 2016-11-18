#include <stdio.h>
#include <stdlib.h>
//#include <omp.h>
#define EXTRACT_BIT(n,i) ((n&(1<<i))?1:0)
int v=16;
int i;
//double a[n],b[n],c[n],d[n],e[n],f[n],g[n],h[n],i[n];

void Cod(int id, int z){
	//int my_rank = omp_get_num_threads();
	for(i=0; i < 16; i++) v[i] = EXTRACT_BIT(z,i);
	
	if ((v[0]||v[1])&&(!v[1] || !v[3]) && (v[2] || v[3])
		&&(!v[3] || !v[4]) && (v[4] || !v[5])
		&&(v[5] || !v[6]) && (v[5] || v[6])
		&&(v[6] || !v[15]) && (v[7] || v[8])
		&&(!v[7] || !v[13]) && (v[8] || v[9])
		&&(v[8] || !v[9]) && (!v[9] || !v[10])
		&&(v[9] || v[11]) && (v[10] || v[11])
		&&(v[12] || v[13]) && (v[13] || !v[14])
		&&(v[14] || v[15])){
		printf("%d %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n",v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],
		v[8],v[9],v[10],v[11],v[12],v[13],v[14],v[15],v[16]);
		fflush(stdout);
	}
}

