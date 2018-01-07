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
#define MAX 500
#define INF 1e5
#define VTRUE 1
#define VFALSE 0
#define NOPREV -1

#define DEBUG 0

int N,M,C1,C2;
int wgt[MAX];//weight
int edge[MAX][MAX]={0};
int dist[MAX]={0};
int vset[MAX]={0};//visited set
int prev[MAX]={0};
int snum[MAX]={0};//number of shortest path

void InitEdge()
{
	int i,j,k,w;
	char pr[1024];
	for (i=0; i<MAX; i++)
		for (j=0; j<MAX; j++)
			edge[i][j] = (i==j ? 0 : INF);

	scanf("%d %d %d %d", &N, &M, &C1, &C2);
	getchar();
	for (i=0; i<N; i++) {
		scanf("%d", &wgt[i]);
		getchar();
	}
	for (k=0; k<M; k++) {
		scanf("%d %d %d", &i, &j, &w);
		getchar();
		edge[i][j] = edge[j][i] = w;//no direction
	}

#if DEBUG
	printf("%d %d %d %d\n", N, M, C1, C2);
	for (i=0; i<N; i++)
		printf("%d ", wgt[i]);
	putchar('\n');
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			sprintf(pr, "%d", edge[i][j]);
			printf("%s ", (edge[i][j]==INF?"+":pr));
		}
		putchar('\n');
	}
#endif

}

int GetWgt(int s, int d)
{
	int w=0;
	while(d!=s) {
		w += wgt[d];
		d = prev[d];
		if (d==NOPREV)
			return 0;
	}
	w += wgt[s];
	return w;
}

void Dijk(int s, int d, int n)
{
	int i,j,k;
	int min, t;
	for (i=0; i<n; i++) {
		vset[i] = VFALSE;
		dist[i] = edge[s][i];
		if (dist[i]==INF) {
			prev[i] = NOPREV;
			snum[i] = 0;
		}
		else {
			prev[i] = s;
			snum[i] = 1;
		}
		
	}
	vset[s] = VTRUE;

	for (k=1; k<n; k++) {
		min = INF;
		for (i=0; i<n; i++) {
			if (vset[i]==VFALSE && dist[i]<min) {
				t = i;
				min = dist[i];//refresh, don't miss
			}
		}
		vset[t] = VTRUE;

		for (i=0; i<n; i++) {
			if (vset[i]==VFALSE) {
				if (dist[t]+edge[t][i]<dist[i]) {
					dist[i] = dist[t]+edge[t][i];
					prev[i] = t;
					snum[i] = snum[t];//careful
				}
				else if (dist[t]+edge[t][i]==dist[i]) {
					snum[i] += snum[t];//careful
					if (GetWgt(s, t)+wgt[i]>GetWgt(s,i)){
						//dist[i] = dist[t]+edge[t][i];
						prev[i] = t;
					}
				}
			}
		}
	}

#if DEBUG
	putchar('\n');
	for (i=0; i<n; i++)
		printf("%d ", dist[i]);
	putchar('\n');
	for (i=0; i<n; i++)
		printf("%d ", prev[i]);
	putchar('\n');
	for (i=0; i<n; i++)
		printf("%d ", vset[i]);
	putchar('\n');
	for (i=0; i<n; i++)
		printf("%d ", GetWgt(s, i));
	putchar('\n');
	for (i=0; i<n; i++)
		printf("%d ", snum[i]);
	putchar('\n');
#endif
	printf("%d %d", snum[d], GetWgt(s, d));//do not add '\n'

}

//===========================================================
int maxwgt[MAX]={0};
int IsIndexInStk(int stk[], int top, int idx)
{
	int i;
	for (i=0; i<=top; i++) {
		if (stk[i]== idx)
			return 1;
	}
	return 0;
}

void bfs(int stk[], int top, int n)
{
	int cur=stk[top];
	int tdist=0, twgt=wgt[stk[0]];
	int i;

	if (top>0) {
		for (i=1; i<=top; i++) {
			tdist += edge[stk[i-1]][stk[i]];
			twgt += wgt[stk[i]];
		}
#if DEBUG
		printf("tdist:%d, twgt:%d\n", tdist, twgt);
		printf("snum[cur]:%d\n", snum[cur]);
		printf("dist[cur]:%d, maxwgt[cur]:%d\n", dist[cur], maxwgt[cur]);
#endif
		if (tdist<dist[cur]) {
			snum[cur] = 1;
			dist[cur] = tdist;
			maxwgt[cur] = twgt;
		}
		else if (tdist==dist[cur]) {
			++snum[cur];
			maxwgt[cur] = twgt>maxwgt[cur]?twgt:maxwgt[cur];
		}
#if DEBUG
		printf("snum[cur]:%d\n", snum[cur]);
		printf("dist[cur]:%d, maxwgt[cur]:%d\n", dist[cur], maxwgt[cur]);
#endif
	}



	for (i=0; i<n; i++) {
		if (edge[cur][i]!= INF && cur!=i && \
				!IsIndexInStk(stk, top, i)) {
#if DEBUG
			printf("cur:%d, i:%d\n", cur, i);
#endif
			stk[top+1] = i;
			bfs(stk, top+1, n);
		}
	}


}

void DfsTrave(int c1, int c2, int n)
{//can not get full score
	int stk[MAX], top=-1;
	int i;

	for (i=0; i<n; i++) {
		dist[i] = INF;//edge[c1][i];
		maxwgt[i] = -1;
	}

	stk[top++] = c1;
	bfs(stk, top, n);

	printf("%d %d", snum[c2], maxwgt[c2]);
}
//===========================================================
int visit[MAX]={0};
void bfs2(int v, int pre, int n)
{
	int i;

	if (pre==-1) {//first vertex
		dist[v]=0;
		maxwgt[v]=wgt[v];
	}
	else {
		if (dist[pre]+edge[pre][v]<dist[v]) {
			snum[v]=1;
			dist[v]=dist[pre]+edge[pre][v];
			maxwgt[v]=maxwgt[pre]+wgt[v];
		}
		else if (dist[pre]+edge[pre][v]==dist[v]) {
			++snum[v];
			maxwgt[v] = maxwgt[pre]+wgt[v]>maxwgt[v]?maxwgt[pre]+wgt[v]:maxwgt[v];
		}
	}

	for (i=0; i<n; i++) {
		if (edge[v][i]!=INF && v!=i && !visit[i]){
			visit[i]=1;
			bfs2(i, v, n);
			visit[i]=0;
		}
	}
}
void DfsTrave2(int c1, int c2, int n)
{
	
	int i;

	for (i=0; i<n; i++) {
		dist[i] = INF;//edge[c1][i];
		maxwgt[i] = -1;
	}
	visit[c1]=1;
	bfs2(c1, -1, n);

	printf("%d %d", snum[c2], maxwgt[c2]);
}

int main(int argc, char *argv[])
{
	InitEdge();
	//Dijk(C1, C2, N);
	//DfsTrave(C1, C2, N);
	DfsTrave2(C1, C2, N);
}