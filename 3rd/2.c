#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int location;
    int data;
    struct node *next;
} Node;

int main()
{
    int n, num;
    scanf("%d", &n);
    Node *head = NULL;
    Node *tail = NULL;
    for (int i = 1; i <= n; i++)
    {
        Node *p = (Node *)malloc(sizeof(Node));
        scanf("%d %d", &(p->location), &(p->data));
        if (head == NULL)
        {
            head = p;
            tail = p;
            tail->next = head;
        }
        else
        {
            tail->next = p;
            p->next = head;
            tail = p;
        }
    }
    Node *now = tail;

    while (scanf("%d", &num))
    {
        if(num==-1)
        break;
        int rest = -1, min = 2100000000, flag = 0;
        Node *save=now;
        while (1)
        {
            
            if (now->next->data == num)
            {
                now->next = now->next->next;
                flag = 0;
                n--;
                break;
            }
            else if (now->next->data < num)
            {
                now = now->next;
                flag++;
                if (flag == n && rest == -1)
                {
                    now = save;
                    break;
                }
            }
            else if (now->next->data > num)
            {
                rest = now->next->data - num;
                if (rest < min)
                {
                    min = rest;
                }
                if (flag >= n)
                    if (now->next->data - num == min)
                    {
                        now->next->data -= num;
                        break;
                    }
                now = now->next;
                flag++;
            }
        }
    }
    while (n--)
    {
        printf("%d %d\n", now->next->location, now->next->data);
        now = now->next;
    }

    return 0;
}