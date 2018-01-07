#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

#define DEBUG 0

typedef struct stVertex {
	int num;
	int *pchd;//child
} Vertex;

Vertex vertex[MAX]={0};
int level[MAX]={0};
int noleaf[MAX]={0};
int maxlev=-1;

void dfs(int v, int lev)
{
	int i;
	level[v] = lev;
	maxlev = lev>maxlev?lev:maxlev;
	if (!vertex[v].pchd) {
		++noleaf[lev];
		return;
	}

	for (i=0; i<vertex[v].num; i++) {
		dfs(vertex[v].pchd[i], lev+1);
	}
}

void fun1()
{
	int n,m, id, num, id2;
	int i, j;

	scanf("%d %d", &n, &m);
	getchar();
	for (i=0; i<m; i++) {
		scanf("%d %d ", &id, &num);
		vertex[id].num = num;
		vertex[id].pchd = (int *)malloc(num * sizeof(int));
		for (j=0; j<num; j++) {
			scanf("%d", &vertex[id].pchd[j]);
			getchar();
		}
	}

	dfs(1, 0);

	if (maxlev>-1) printf("%d", noleaf[0]);
	for (i=1; i<=maxlev; i++)
		printf(" %d", noleaf[i]);
}
//=========================================================================
void fun2()
{
	int n,m, id, num, id2;
	int i, j, t;
	int que[MAX],head,tail;

	scanf("%d %d", &n, &m);
	getchar();
	for (i=0; i<m; i++) {
		scanf("%d %d ", &id, &num);
		vertex[id].num = num;
		vertex[id].pchd = (int *)malloc(num * sizeof(int));
		for (j=0; j<num; j++) {
			scanf("%d", &vertex[id].pchd[j]);
			getchar();
		}
	}

	head = tail = 0;
	level[1] = 0;
	que[tail++] = 1;//in que
	while (head!=tail) {
		t = que[head++];//out que
		maxlev = level[t]>maxlev?level[t]:maxlev;
		if (!vertex[t].pchd)
			++noleaf[level[t]];
		for (i=0; i<vertex[t].num; i++) {
			level[vertex[t].pchd[i]] = level[t]+1;
			que[tail++] = vertex[t].pchd[i];
		}
	}

	if (maxlev>-1) printf("%d", noleaf[0]);
	for (i=1; i<=maxlev; i++)
		printf(" %d", noleaf[i]);
}

//=========================================================================

int IsNoChild(int arr[], int n, int id)
{
	int i;
	for (i=1; i<=n; i++) {
		if (arr[i] == id)
			return 0;
	}
	return 1;
}

int GetLev(int vert[], int id)
{
	int t = id;
	int lev = 0;//start with 0
	while (t > 1) {
		lev++;
		t = vert[t];
	}
	return lev;
}

void fun3()
{
	int vert[MAX];//index:1~n;-1 not exist,value is father's index
	int vertlev[MAX];//index:1~n
	int noleafnum[MAX]={0};//index:0~maxdep
	int maxdep=-1;

	int n,m, id, num, id2;
	int i, j;

	scanf("%d %d", &n, &m);
	getchar();
	for (i=0; i<n; i++) {
		vert[i]=-1;
	}

	vert[1]=0;
	for (i=0; i<m; i++) {
		scanf("%d %d ", &id, &num);
		for (j=0; j<num; j++) {
			scanf("%d", &id2);
			vert[id2] = id;
		}
	}

	for (i=1; i<=n; i++) {
		if (vert[i] != -1) {
			vertlev[i] = GetLev(vert, i);
			maxdep = vertlev[i]>maxdep?vertlev[i]:maxdep;
		}
	}

	for (i=1; i<=n; i++) {
		if (IsNoChild(vert, n, i)) {
			++noleafnum[vertlev[i]];
		}
	}

#if DEBUG
	for (i=1; i<=n; i++)	printf("%d ", vert[i]);putchar('\n');
	for (i=1; i<=n; i++)	printf("%d ", vertlev[i]);putchar('\n');
	for (i=0; i<=maxdep; i++)	printf("%d ", noleafnum[i]);putchar('\n');
#endif

	if (maxdep>=0) printf("%d", noleafnum[0]);
	for (i=1; i<=maxdep; i++) printf(" %d", noleafnum[i]);
}
//=========================================================================

typedef struct stNode {
	int id;
	struct stNode *fstchd;
	struct stNode *nxtsib;
} Node;

Node *GetAddById(Node *p, int id)
{
	Node *tmp;
	if (!p) return NULL;
	if (p->id == id)
		return p;
	if (tmp=GetAddById(p->fstchd, id))
		return tmp;
	if (tmp=GetAddById(p->nxtsib, id))
		return tmp;
	return NULL;
}

int CreateTree(Node **proot)
{
	int n,m, id, num, id2;
	int i, j;
	int edge[MAX][MAX]={0};
	Node *root, *phead, *ptail, *p;
	Node* tmparr[MAX];//防止有些父节点没有提前生成
	int maxhead=0;
	
	scanf("%d %d", &n, &m);
	getchar();
	if (n<=0) return -1;
	
	root = (Node *)malloc(sizeof(Node));
	root->id = 1;
	root->fstchd = NULL;
	root->nxtsib = NULL;
	tmparr[maxhead++] = root;
	
	for (i=0; i<m; i++) {
		scanf("%d %d ", &id, &num);
		for (j=0; j<num; j++) {
			scanf("%d", &id2);
			edge[id-1][id2-1] = 1;
		}
	}

	for (i=0; i<n; i++) {
		phead = ptail = NULL;
		for (j=i+1; j<n; j++) {
			if (!edge[i][j]) continue;
			p = (Node *)malloc(sizeof(Node));
			p->id = j+1;
			p->fstchd = NULL;
			p->nxtsib = NULL;

			if (!ptail) {//first node
				phead = ptail = p;
			}
			else {
				ptail->nxtsib = p;
			}
		}
		if (phead)
			tmparr[maxhead++] = phead;
	}

	for (i=1; i<maxhead; i++) {
		id2 = tmparr[i]->id;
		p = NULL;
		for (j=0; j<n; j++) {
			if (edge[j][id2-1]) {
			    id=j+1;//father
			    break;
			}
		}
		for (j=0; j<maxhead; j++) {
			if (p=GetAddById(root, id)) {
				break;
			}
		}
		if (!p) {
			//printf("error..\n");
			//exit(0);
		}
		p->fstchd = tmparr[i];
	}

	*proot = root;
	return n;
}

int GetMaxDep(Node *p)
{
	int nchd, nsib;
	//if (!p) return 0;//maxdep:1~x
	if (!p) return -1;//so,maxdep:0~x
	nchd = GetMaxDep(p->fstchd);
	nsib = GetMaxDep(p->nxtsib);
	return nchd+1>nsib?nchd+1:nsib;
}

void SetInfo(Node *p, int noleaf[], int dep)
{
	if (!p) return;
	if (!p->fstchd) ++noleaf[dep];
	SetInfo(p->fstchd, noleaf, dep+1);
	SetInfo(p->nxtsib, noleaf, dep);
}

void fun4()
{//can not get all scores
	Node *root;
	int n, i;
	int noleaf[MAX]={0};
	int maxdep;
	n = CreateTree(&root);
	maxdep = GetMaxDep(root);
	SetInfo(root, noleaf, 0);
	if (maxdep>=0) printf("%d", noleaf[0]);
	for (i=1; i<=maxdep; i++) printf(" %d", noleaf[i]);
}

int main(int argc, char *argv[])
{
	//fun1();
	//fun2();
	//fun3();
	fun4();
}