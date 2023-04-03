#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char name[30];
    int use[20];
    int u;

} Node[200];

int main()
{
    int stack[200] = {0};
    int top = -1, op, rank = 0;
    scanf("%d", &op);
    scanf("%s", Node[rank].name);
    Node[rank].u = 0;
    stack[++top] = rank;
    for (int i = 0; i < 20; i++)
    {
        Node[rank].use[i] = -1;
    }
    rank++;
    while (top > -1)
    {
        scanf("%d", &op);
        switch (op)
        {
        case 0:
            top--;
            break;
        case 8:
            scanf("%s", Node[rank].name);
            for (int i = 0; i < 20; i++)
            {
                Node[rank].use[i] = -1;
            }
            int i = 0, flag = 1;
            for (; i < rank ; i++)
            {
                if (strcmp(Node[rank].name, Node[i].name) == 0)
                {
                    for (int j = 0; j < Node[stack[top]].u; j++)
                    {
                        if (i == Node[stack[top]].use[j])
                            flag = 0;
                    }
                    if (flag)
                        Node[stack[top]].use[Node[stack[top]].u++] = i;
                    stack[++top] = i;
                    break;
                }
            }
            if (i != rank )
                break;
            for (int j = 0; j < Node[stack[top]].u; j++)
            {
                if (rank == Node[stack[top]].use[j])
                    flag = 0;
            }
            if (flag)
                Node[stack[top]].use[Node[stack[top]].u++] = rank;
            stack[++top] = rank;
            Node[rank].u = 0;
            rank++;
            break;
        default:
            break;
        }
    }
    for (int i = 0; i < rank; i++)
    {
        int j = 0;
        for (; j < Node[i].u; j++)
        {
            if (j == 0)
            {
                printf("%s:", Node[i].name);
            }
            printf("%s", Node[Node[i].use[j]].name);
            if (j + 1 < Node[i].u)
                printf(",");
        }
        if (j != 0)
            printf("\n");
    }

    return 0;
}
/*
8 main
8 input
0
8 mysqrt
0
8 findA
0
8 findB
8 area
8 mysin
0
8 mycos
0
8 mysqrt
0
0
0
8 findC
8 area
8 mysin
0
0
8 mysqrt
8 max
0
0
0
8 output
0
0
*/