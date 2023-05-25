#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int N, E, count1 = 0;
char path[30][30];
int visit[1005];
int site = 0;
int imPath[1005];

typedef struct ArcNode
{
	int adjvex;
	int no;
	struct ArcNode *nextarc;
} ArcNode;

typedef struct VNode
{
	ArcNode *first;
} VNode;

VNode G[1005];

int CMP(const void *a, const void *b)
{
	return strcmp((char *)a, (char *)b);
}

void Insert(int e, int no, int adj)
{
	ArcNode *temp;
	if (G[e].first == NULL)
	{
		G[e].first = (ArcNode *)malloc(sizeof(ArcNode));
		temp = G[e].first;
		temp->adjvex = adj;
		temp->no = no;
		temp->nextarc = NULL;
		return;
	}
	else
	{
		struct ArcNode *temp = (struct ArcNode *)malloc(sizeof(struct ArcNode));
		temp->nextarc = G[e].first;
		G[e].first = temp;
		G[e].first->adjvex = adj;
		G[e].first->no = no;
		return;
	}
}

void CreatNode()
{
	scanf("%d %d", &N, &E);
	for (int i = 0; i < N; i++)
	{
		G[i].first = NULL;
	}
	for (int i = 0; i < E; i++)
	{
		int no, e1, e2;
		scanf("%d %d %d", &no, &e1, &e2);
		Insert(e1, no, e2);
		Insert(e2, no, e1);
	}
}

void FindPath(int p)
{
	if (p == N - 1)
	{
		for (int i = 0; i < site; i++)
			path[count1][i] = imPath[i] + '0';
		path[count1][site] = '\0';
		count1++;
		return;
	}
	ArcNode *temp = G[p].first;
	while (temp)
	{
		if (visit[temp->adjvex] == 0)
		{
			visit[temp->adjvex] = 1;
			imPath[site++] = temp->no;
			FindPath(temp->adjvex);
			site--;
			visit[temp->adjvex] = 0;
		}
		temp = temp->nextarc;
	}
}

void PrintPath()
{
	for (int i = 0; i < count1; i++)
	{
		for (int j = 0; path[i][j] != '\0'; j++)
			printf("%d ", path[i][j]-'0');
		printf("\n");
	}
}

int main()
{
	CreatNode();
	visit[0] = 1;
	FindPath(0);
	qsort(path, count1, sizeof(path[0]), CMP);
	PrintPath();
	return 0;
}
