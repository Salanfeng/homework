#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int a;
    int exp;
    struct Node *next;
} *Num;

Num newNode(int a, int exp)
{
    Num p = (Num)malloc(sizeof(struct Node));
    p->a = a;
    p->exp = exp;
    p->next = NULL;
    return p;
}

void insert(int a, int exp, Num *p)
{
    Num newNode = (Num)malloc(sizeof(struct Node));
    newNode->a = a;
    newNode->exp = exp;
    newNode->next = NULL;

    Num prev = NULL;
    Num curr = *p;
    while (curr && curr->exp > exp)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr && curr->exp == exp)
    {
        curr->a += a;
        free(newNode);
    }
    else
    {
        if (!prev)
        {
            newNode->next = *p;
            *p = newNode;
        }
        else
        {
            newNode->next = curr;
            prev->next = newNode;
        }
    }
}

Num multi(Num p1, Num p2)
{
    Num result = NULL;

    for (Num i = p1; i; i = i->next)
    {
        for (Num j = p2; j; j = j->next)
        {
            int a = i->a * j->a;
            int exp = i->exp + j->exp;
            insert(a, exp, &result);
        }
    }

    return result;
}

int main()
{
    char c;
    Num p1 = NULL;
    Num p2 = NULL;
    int a, exp;
    do
    {
        scanf("%d %d", &a, &exp);
        insert(a, exp, &p1);
    } while ((c = getchar()) != '\n');
    do
    {
        scanf("%d %d", &a, &exp);
        insert(a, exp, &p2);
    } while ((c = getchar()) != '\n');

    Num result = multi(p1, p2);
    {

        while (result)
        {
            printf("%d %d ", result->a, result->exp);
            result = result->next;
        }
        printf("\n");
    }
    return 0;
}
