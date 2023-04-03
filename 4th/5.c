#include <stdio.h>
#include <stdlib.h>
#define MAX 1024
typedef struct Line
{
    int rank;
    int time;
    int waittime;
    struct Line *next;
} Queue;
int windows[10];
Queue *Add(Queue *p, int turn)
{
    int time;
    for (int i = 0; i < turn; i++)
    {
        scanf("%d", &time);
        Queue *q = (Queue *)malloc(sizeof(Queue));
        q->rank = p->rank + 1, q->time = time, q->waittime = 0, q->next = NULL;
        p->next = q, p = q;
    }
    return p;
}
int Deal(Queue *head, int rear_rank, int flag)
{
    Queue *rear = head;
    int last = 0;
    for (int i = 0; i < rear_rank; i++)
    {
        if (rear->next == NULL)
        {
            break;
        }
        rear = rear->next;
    }

    for (int i = 0; i < flag; i++)
    {
        if (windows[i] == 0)
        {
            windows[i] = rear->time;
            rear->time = 0;
            if (rear->next == NULL)
            {
                last = 1;
                break;
            }
            rear = rear->next;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (windows[i] > 0)
        {
            windows[i]--;
        }
    }

    return rear->rank + last;
}

void Plus(Queue *head, int rear_rank)
{
    Queue *rear = head;
    while (rear->next != NULL)
    {
        if (rear->time != 0)
            rear->waittime++;
        rear = rear->next;
    }
    if (rear->time != 0)
        rear->waittime++;
}

int main()
{
    int T, turn[MAX], sum = 0, flag = 3, RearRank = 1, wait = 0, winsum = 0;
    Queue *head = (Queue *)malloc(sizeof(Queue));
    head->next = NULL;
    head->rank = 0, head->time = 0;
    Queue *p = (Queue *)malloc(sizeof(Queue));
    p = head;
    scanf("%d", &T);
    for (int i = 0; i < T; i++)
    {
        scanf("%d", &turn[i]);
    }
    for (int i = 0; i < T || p->time != 0 || winsum != 0; i++)
    {
        winsum = 0;
        if (i < T)
        {
            sum += turn[i];
            p = Add(p, turn[i]);
            wait = sum - RearRank + 1;
            while (wait >= 7 * flag && flag < 5)
            {
                flag++;
                // printf("1.%d   %d\n", flag, wait);
            }
        }

        RearRank = Deal(head, RearRank, flag);
        Plus(head, RearRank);
        wait = sum - RearRank + 1;
        // printf("%d %d %d %d %d\n", windows[0], windows[1], windows[2], windows[3], windows[4]);

        while (flag > 3 && wait < 7 * (flag))
        {
            flag--;
            // printf("2.%d   %d\n", flag, wait);
        }
        for (int j = 0; j < 5; j++)
        {
            winsum += windows[j];
        }
    }
    head = head->next;
    while (head->next != NULL)
    {
        printf("%d : %d\n", head->rank, head->waittime);
        head = head->next;
    }
    printf("%d : %d\n", head->rank, head->waittime);
    return 0;
}
/*
4
2 5 13 11
1 3
2 2 1 3 2
1 1 1 1 3 3 2 2 1 2 3 1 1
3 3 2 1 3 1 1 3 1 3 3
*/