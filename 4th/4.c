#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1024

typedef struct Opertor
{
    int op;
    int pos;
    char string[500];
    struct Opertor *next;
    struct Opertor *prev;
} OP;

void Change(OP *p, char *str)
{
    int op, pos, n, len;
    char buffer[MAX];
    OP *del;
    scanf("%d", &op);
    while (op != -1)
    {

        switch (op)
        {
        case 1:
        {
            // insert string
            scanf("%d %s", &pos, buffer);
            OP *op = (OP *)malloc(sizeof(OP));
            op->op = 1, op->pos = pos, strcpy(op->string, buffer);
            p->next = op, op->prev = p, p = op;
            len = strlen(buffer);
            for (int i = strlen(str); i >= pos; i--)
            {
                str[i + len] = str[i];
            }
            for (int i = 0; i < len; i++)
            {
                str[pos + i] = buffer[i];
            }
            break;
        }
        case 2:
        {
            // delete string
            scanf("%d %d", &pos, &n);
            if (pos + n > strlen(str))
            {
                n = strlen(str) - pos;
            }
            for (int i = pos; i <= (pos + n); i++)
            {
                buffer[i - pos] = str[i];
            }
            buffer[n] = '\0';
            OP *op = (OP *)malloc(sizeof(OP));
            op->op = 2, op->pos = pos, strcpy(op->string, buffer);
            p->next = op, op->prev = p, p = op;
            for (int i = pos + n; i <= strlen(str); i++)
            {
                str[i - n] = str[i];
            }
            break;
        }
        case 3:
        {
            // undo the last operation
            if (p->prev != NULL)
            {
                if (p->op == 1)
                {
                    int lenth = strlen(p->string);
                    for (int i = p->pos; i < strlen(str); i++)
                    {
                        str[i] = str[i + lenth];
                    }
                }
                else if (p->op == 2)
                {
                    for (int i = strlen(str); i >= p->pos; i--)
                    {
                        str[i + strlen(p->string)] = str[i];
                    }
                    for (int i = 0; i < strlen(p->string); i++)
                    {
                        str[p->pos + i] = p->string[i];
                    }
                }
                del = p;
                p = p->prev;
                free(del);
            }
            break;
        }
        }
        scanf("%d", &op);
    }

    return;
}
int main()
{
    int n;
    char str[MAX], save[MAX];
    gets(str);
    scanf("%d", &n);
    OP *head = (OP *)malloc(sizeof(OP));
    OP *p = head;
    while (n--)
    {
        OP *op = (OP *)malloc(sizeof(OP));
        scanf("%d %d %s", &op->op, &op->pos, op->string);
        op->next = NULL;
        op->prev = p;
        p->next = op;
        p = op;
    }
    Change(p, str);
    puts(str);
    return 0;
}