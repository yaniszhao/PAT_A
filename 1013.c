#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

#define DEBUG 0

void dfs(int i, int n, int visit[], int edge[][MAX])
{
	int j;
	visit[i] = 1;
	for (j=1; j<=n; j++) {
		if (edge[i][j] && !visit[j]) {//different from first judge
			dfs(j, n, visit, edge);
		}
	}

}

void fun1()
{//DFS
	int edge[MAX][MAX] = {0};
	int visit[MAX]={0};
	int n,m,k;
	int i, j, s, d, cnt=0;
	int chk;
	scanf("%d %d %d", &n, &m, &k);
	getchar();
	for (i=0; i<m; i++) {
		scanf("%d %d", &s, &d);
		getchar();
		edge[s][d] = edge[d][s] = 1;
	}

#if DEBUG
	putchar('\n');
	for (i=1; i<=n; i++) {
		for (j=1; j<=n; j++) {
			printf("%d ", edge[i][j]);
		}
		putchar('\n');
	}
	printf("%d %d %d\n", n ,m, k);
#endif

	for (i=0; i<k; i++) {
		scanf("%d", &chk);
		getchar();
		memset(visit, 0, MAX*sizeof(int));
		visit[chk] = 1;
		cnt = 0;
#if DEBUG
	for (j=1; j<=n; j++) {
		printf("%d ", visit[j]);
		fflush(stdout);
	}
	putchar('\n');
#endif

		for (j=1; j<=n; j++) {
			//if (edge[chk][j] && !visit[j]) {
			if (!visit[j]) {
				dfs(j, n, visit, edge);
				cnt++;
			}
		}
		printf("%d\n", cnt-1);
	}

}
//=========================================================
void bfs(int i, int n, int visit[], int edge[][MAX])
{
	int j, out;
	int que[MAX], head, tail;
	head=tail=0;
	visit[i] = 1;
	que[tail++]=i;
	while (head!=tail) {
		out=que[head++];
		for (j=1; j<=n; j++) {
			if (edge[out][j] && !visit[j]) {
				visit[j]=1;
				que[tail++]=j;
			}
		}
	}
}

void fun2()
{//BFS
	int edge[MAX][MAX] = {0};
	int visit[MAX]={0};
	int n,m,k;
	int i, j, s, d, cnt=0;
	int chk;
	scanf("%d %d %d", &n, &m, &k);
	getchar();
	for (i=0; i<m; i++) {
		scanf("%d %d", &s, &d);
		getchar();
		edge[s][d] = edge[d][s] = 1;
	}

#if DEBUG
	putchar('\n');
	for (i=1; i<=n; i++) {
		for (j=1; j<=n; j++) {
			printf("%d ", edge[i][j]);
		}
		putchar('\n');
	}
	printf("%d %d %d\n", n ,m, k);
#endif

	for (i=0; i<k; i++) {
		scanf("%d", &chk);
		getchar();
		memset(visit, 0, MAX*sizeof(int));
		visit[chk] = 1;
		cnt = 0;
#if DEBUG
	for (j=1; j<=n; j++) {
		printf("%d ", visit[j]);
		fflush(stdout);
	}
	putchar('\n');
#endif

		for (j=1; j<=n; j++) {
			//if (edge[chk][j] && !visit[j]) {
			if (!visit[j]) {
				bfs(j, n, visit, edge);
				cnt++;
			}
		}
		printf("%d\n", cnt-1);
	}

}
//=========================================================
int Find(int pre[], int idx, int *n)
{
	int cnt=0;
	while (pre[idx]!=idx) {
		idx = pre[idx];
		cnt++;
	}
	*n = cnt;
	return idx;
	/*if (pre[idx]==idx)
		return idx;
	else {
		return Find(pre, pre[idx]);
	}*/
	//return pre[idx]==idx?idx:pre[idx]=Find(pre, pre[idx]); 
}

void Union(int pre[], int x, int y)
{
	int topx,topy,nx,ny;
	topx = Find(pre, x, &nx);
	topy = Find(pre, y, &ny);
	if (topx!=topy) {
		if (nx<ny)
			pre[topx] = topy;
		else
			pre[topy] = topx;
		//pre[topy] = topx;//pre[topx] = topy;就过不了，看来是平衡性的问题
	}
	return;
}

int IsTwoPointExist(int v1[], int v2[], int n, int x, int y)
{
	int i;
	for (i=0; i<n; i++) {
		if ((v1[i]==x&&v2[i]==y) || (v1[i]==y&&v2[i]==x))
			return 1;
	}
	return 0;
}

void fun3()
{//Union Find,最后一个用例段错误是为什么==》union平衡性的问题
	int pre[MAX];
	int *v1, *v2, vmax=0;
	int edge[MAX][MAX] = {0};
	int n,m,k;
	int chk;
	int i, j, s, d, cnt;

	scanf("%d %d %d", &n, &m, &k);
	v1 = (int *)malloc(m*sizeof(int));
	v2 = (int *)malloc(m*sizeof(int));
	for (i=0; i<m; i++) {
		scanf("%d %d", &v1[i], &v2[i]);
		/*if (!IsTwoPointExist(v1, v1, vmax, s, d)) {
			v1[vmax] = s;
			v2[vmax] = d;
			vmax++;
		}*/
	}

	while (k--) {
		scanf("%d", &chk);
		for (j=1; j<=n; j++) pre[j]=j;//initialize
		cnt = 0;
/*		for (i=1; i<=n; i++) {
			for (j=i+1; j<=n; j++) {
				if (i!=chk && j!=chk && edge[i][j]==1) {
					Union(pre, i, j);
				}
			}
		}*/
		for (j=0; j<m; j++) {
			if (v1[j]!=chk && v2[j]!=chk) {
				Union(pre, v1[j], v2[j]);
			}
		}

		for (j=1; j<=n; j++) {
			if (pre[j]==j && j!=chk)
				cnt++;
		}
		printf("%d\n", cnt-1);
	}
}

int main(int argc, char *argv[])
{
	//fun1();//DFS
	//fun2();//BFS
	fun3();//Union Find
}