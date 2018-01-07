/*
test:
5
0 1 1
0 2 2
0 3 1
1 2 1
2 4 1
3 4 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
#define INF 1e5
#define VTRUE 1
#define VFALSE 0

int N=5;
int edge[MAX][MAX]={0};
int dist[MAX]={0};
int vset[MAX]={0};
int prev[MAX]={0};

void InitEdge()
{
	int i,j, w;
	
	for (i=0; i<MAX; i++)
		for (j=0; j<MAX; j++)
			edge[i][j] = (i==j ? 0 : INF);

	scanf("%d", &N);
	getchar();
	while (scanf("%d %d %d", &i, &j, &w)!=EOF) {
		getchar();
		edge[i][j] = edge[j][i] = w;
	}

	for (i=0; i<N; i++) {
		for (j=0; j<N; j++)
			printf("%d ", edge[i][j]);
		putchar('\n');
	}

}

void Dijk(int v0, int n)
{
	int i,j,k;
	int min, t;
	for (i=0; i<n; i++) {
		vset[i] = VFALSE;
		dist[i] = edge[v0][i];
		prev[i] = v0;
	}
	vset[v0] = VTRUE;

	for (k=1; k<n; k++) {
		min = INF;
		for (i=0; i<n; i++) {
			if (vset[i]==VFALSE && dist[i]<min) {
				t = i;
			}
		}
		vset[t] = VTRUE;

		for (i=0; i<n; i++) {
			if (vset[i]==VFALSE && dist[t]+edge[t][i]<dist[i]) {
				dist[i] = dist[t]+edge[t][i];
				prev[i] = t;
			}
		}
	}

	for (i=0; i<n; i++)
		printf("%d ", dist[i]);
	putchar('\n');
	putchar('\n');
	for (i=0; i<n; i++)
		printf("%d ", prev[i]);
	putchar('\n');
	putchar('\n');
	for (i=0; i<n; i++)
		printf("%d ", vset[i]);
	putchar('\n');


}

int main(int argc, char *argv[])
{
	InitEdge();
	Dijk(0, N);

}