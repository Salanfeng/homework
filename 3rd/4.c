#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 1024

typedef struct node
{
    int ascii;
    struct node *next;
} Node;

int final[150] = {0};
void circle(Node *tail, int sum)
{
    Node *now = tail;
    int save = -1, first = 0;
    first = now->next->ascii;
    while (sum > 1)
    {
        save = now->next->ascii;
        now->next = now->next->next;
        sum--;
        int i = (save);
        for (; i > 1;i--)
        {
            now = now->next;
        }
        final[save] = now->next->ascii;
    }
    final[now->next->ascii] = first;
}

int main()
{
    char filename[] = "in.txt";
    char outFilename[] = "in_crpyt.txt";
    char str1[MAX];
    char buffer[MAX];
    char *p;
    int len1, pass[150] = {0}, flag[150] = {0};
    FILE *IN, *OUT;
    IN = fopen(filename, "r");
    OUT = fopen(outFilename, "w");
    gets(str1);
    len1 = strlen(str1);
    if ((IN = fopen(filename, "r")) == NULL)
    {
        printf("Can&rsquo;t open in.txt!");
        return -1;
    }
    for (int i = 0; i < 150; i++)
        flag[i] = 1;

    int d = 0;

    for (int i = 32; i < len1 + 32; i++)
    {
        pass[i - d] = str1[i - 32];
        for (int j = 32; j < i - d; j++)
        {
            if (pass[i - d] == pass[j])
            {
                d++;
                break;
            }
        }
        flag[pass[i - d]] = 0;
    }
    len1 -= d;
    for (int i = 32; i <= 126; i++)
    {
        if (flag[i] == 1)
            pass[32 + len1++] = i;
    }
    /*pass完成存入ascii码，然后输入链表*/
    Node *head = NULL;
    Node *tail = NULL;
    for (int i = 32; i <= 126; i++)
    {
        Node *p = (Node *)malloc(sizeof(Node));
        p->ascii = pass[i];
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
    int sum = 95;

    circle(tail, sum);

    while (fgets(buffer, MAX, IN) != NULL)
    {
        for (int i = 0; i < strlen(buffer); i++)
            if ((buffer[i]) >= 32 && (buffer[i]) <= 126)
                buffer[i] = final[buffer[i]];
        fputs(buffer, OUT);
    }
    fclose(IN);
    fclose(OUT);
    return 0;
}