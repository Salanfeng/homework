#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1005

char StationName[500][20];
int Namecount = 0;

struct ArcNode
{
    int adjvex;
    int line;
    struct ArcNode *nextarc;
};

struct VNode
{
    struct ArcNode *first;
    int flag;
};

struct VNode G[MAX];

int Find(char *name)
{
    for (int i = 0; i < Namecount; i++)
    {
        if (strcmp(StationName[i], name) == 0)
        {
            return i;
        }
    }
    strcpy(StationName[Namecount], name);
    return Namecount++;
}

void Insert(int e, int adj, int line)
{
    struct ArcNode *temp = (struct ArcNode *)malloc(sizeof(struct ArcNode));
    temp->nextarc = G[e].first;
    G[e].first = temp;
    G[e].first->adjvex = adj;
    G[e].first->line = line;
    return;
}

void CreatNode()
{
    FILE *fp = fopen("bgstations.txt", "r");
    for (int i = 0; i < MAX; i++)
    {
        G[i].first = (struct ArcNode *)malloc(sizeof(struct ArcNode));
        G[i].first->nextarc = NULL;
        G[i].first->line = -1;
    }
    int NLines, NStations, Line;
    char name[20];
    int flag;
    fscanf(fp, "%d", &NLines);
    for (int i = 0; i < NLines; i++)
    {
        fscanf(fp, "%d %d", &Line, &NStations);

        int prev, cur;

        fscanf(fp, "%s %d", name, &flag);
        prev = Find(name);
        G[prev].flag = flag;
        for (int j = 1; j < NStations; j++)
        {
            fscanf(fp, "%s %d", name, &flag);
            cur = Find(name);
            G[cur].flag = flag;
            Insert(prev, cur, Line);
            Insert(cur, prev, Line);
            prev = cur;
        }
    }
    fclose(fp);
}

void Dijkstra(int start, int end)
{
    int dist[MAX];
    int path[MAX];
    int visited[MAX];
    int line[MAX];
    int count = 0;
    for (int i = 0; i < Namecount; i++)
    {
        dist[i] = 100000;
        path[i] = -1;
        visited[i] = 0;
    }
    dist[start] = 0;
    int min;
    int minindex;
    while (1)
    {
        min = 100000;
        minindex = -1;
        for (int i = 0; i < Namecount; i++)
        {
            if (visited[i] == 0 && dist[i] < min)
            {
                min = dist[i];
                minindex = i;
            }
        }
        if (minindex == -1)
        {
            break;
        }
        visited[minindex] = 1;
        struct ArcNode *temp = G[minindex].first;
        while (temp->line != -1)
        {
            if (visited[temp->adjvex] == 0 && dist[temp->adjvex] > dist[minindex] + 1)
            {
                dist[temp->adjvex] = dist[minindex] + 1;
                path[temp->adjvex] = minindex;
                line[temp->adjvex] = temp->line;
            }
            temp = temp->nextarc;
        }
    }
    int temp = end;
    int ans[MAX];
    int ansline[MAX];
    while (temp != start)
    {
        ansline[count] = line[temp];
        ans[count++] = temp;
        temp = path[temp];
    }
    ansline[count] = ansline[count - 1];
    ans[count] = start;
    int Number;
    int change = ansline[count];
    int interval = 0;
    for (int i = count; i >= 0; i--)
    {
        Number = ansline[i];
        if (interval && Number != change)
        {
            printf("-%d(%d)-", change, interval);
            interval = 0;
            printf("%s", StationName[ans[i + 1]]);
            interval++;
            if (i == 0)
            {
                if (interval)
                    printf("-%d(%d)-", Number, interval);
                printf("%s", StationName[ans[i]]);
            }
        }
        else if (i == count)
        {
            printf("%s", StationName[ans[i]]);
        }
        else if (i == 0)
        {
            interval++;
            if (interval)
                printf("-%d(%d)-", change, interval);
            printf("%s", StationName[ans[i]]);
        }
        else
        {
            interval++;
        }
        change = Number;
    }
    return;
}
int main()
{
    CreatNode();
    char s1[20], s2[20];
    scanf("%s %s", s1, s2);
    Dijkstra(Find(s1), Find(s2));
    return 0;
}
