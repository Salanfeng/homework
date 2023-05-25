#include <stdio.h>
#include <stdlib.h>
#define MAX 105

void DFS(int Graph[MAX][MAX])
{
    int visited[MAX] = {0};
    int stack[MAX];
    int top = -1;
    int current;
    stack[++top] = 0;
    while (top != -1)
    {
        /*for (int k = 0; k <= top; k++)
        {
            printf("%d ", stack[k]);
        }
        printf("\n");*/
        current = stack[top--];
        if (visited[current] == 0)
        {
            visited[current] = 1;
            printf("%d ", current);
            for (int i = MAX - 1; i >= 0; i--)
            {
                if (Graph[current][i] == 1 && visited[i] == 0)
                {
                    stack[++top] = i;
                }
            }
        }
        
    }
    printf("\n");
}
void BFS(int Graph[MAX][MAX])
{
    int visited[MAX] = {0};
    int queue[MAX];
    int front = 0;
    int rear = 0;
    int current;
    queue[rear++] = 0;
    while (front != rear)
    {
        current = queue[front++];
        if (visited[current] == 0)
        {
            visited[current] = 1;
            printf("%d ", current);
            for (int i = 0; i < MAX; i++)
            {
                if (Graph[current][i] == 1 && visited[i] == 0)
                {
                    queue[rear++] = i;
                }
            }
        }
        
    }
    printf("\n");
}
int main()
{
    int Graph[MAX][MAX];
    int n, m;
    int delete=-1;
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            Graph[i][j] = 0;
        }
    }

    while (scanf("%d", &n) != EOF)
    {
        if (scanf("%d", &m) != EOF)
        {
            Graph[n][m] = 1;
            Graph[m][n] = 1;
        }
        else
        {
            delete = n;
        }
    }
    DFS(Graph);
    BFS(Graph);
    for (int i = 0; i < MAX; i++)
    {
        Graph[delete][i] = 0;
        Graph[i][delete] = 0;
    }
    DFS(Graph);
    BFS(Graph);
}
