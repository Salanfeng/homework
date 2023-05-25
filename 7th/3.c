#include <stdio.h>
#include <stdlib.h>
#define MAX 105

int cmp(const void *a,const void *b)
{
    return *(int *)a-*(int *)b;
}

void Prim(int Graph[MAX][MAX][3], int N, int Visit[MAX])
{
    int sum = 0;
    int ans[MAX],pos=0;
    while(1)
    {
        int min = 0x7fffffff;
        int n, m;
        for (int i = 0; i < N; i++)
        {
            if (Visit[i] == 1)
            {
                for (int j = 0; j < N; j++)
                {
                    if (Graph[i][j][0] != 0 && Visit[j] == 0 && Graph[i][j][1] < min)
                    {
                        min = Graph[i][j][1];
                        n = i;
                        m = j;
                    }
                }
            }
        }
        if (min == 0x7fffffff)
        {
            break;
        }
        else
        {
            sum+=min;
            ans[pos++] = Graph[n][m][0];
            Visit[m] = 1;
        }
    }
    printf("%d\n", sum);
    qsort(ans,pos,sizeof(int),cmp);
    for(int i=0;i<pos;i++)
    {
        printf("%d ",ans[i]);
    }
}

int main()
{
    int Graph[MAX][MAX][3];
    int N, E;
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            Graph[i][j][0] = 0;
            Graph[i][j][1] = 0;
        }
    }
    scanf("%d %d", &N, &E);
    int id, n, m, weight;
    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d %d", &id, &n, &m, &weight);
        Graph[n][m][0] = id;
        Graph[n][m][1] = weight;
        Graph[m][n][0] = id;
        Graph[m][n][1] = weight;
    }
    int Visit[MAX];
    for (int i = 1; i < N; i++)
    {
        Visit[i] = 0;
    }
    Visit[0] = 1;
    Prim(Graph, N, Visit);
}
