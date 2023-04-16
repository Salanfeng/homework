#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define MAX 500
struct Word
{
    char word[MAX];
    int count;
    struct Word *next;
} WordNode;

int n = 0, Stopnum = 0;
char stopwords[500][MAX];
struct Word *head = NULL;
struct Word *p;


int cmp(const void *a, const void *b)
{
    return *(int *)b - *(int *)a;
}
int ReadStop(FILE *stop)
{
    stop = fopen("stopwords.txt", "r");
    if (stop == NULL)
    {
        printf("can not open stop file\n");
        return 1;
    }

    int i = 0, Stopnum = 0;
    while (fscanf(stop, "%s", stopwords[i]) != EOF)
    {
        i++;
    }
    Stopnum = i;
    fclose(stop);
    return Stopnum;
}
int FindStop(char *word)
{
    int head = 0, num = Stopnum;
    while (head <= num)
    {
        if (strcmp(word, stopwords[head + (num - head) / 2]) == 0)
        {
            return 0;
        }
        else if (strcmp(word, stopwords[head + (num - head) / 2]) > 0)
        {
            head = head + (num - head) / 2 + 1;
        }
        else
        {
            num = head + (num - head) / 2 - 1;
        }
    }
    return 1;
}
void insert(char *word)
{
    //printf("%s %d\n", word, n);
    if (n == 0)
    {
        head = (struct Word *)malloc(sizeof(struct Word));
        head->next = (struct Word *)malloc(sizeof(struct Word));
        strcpy(head->next->word, word);
        head->next->count = 1;
        head->next->next = NULL;
        n++;
        return;
    }
    else
    {
        p = head;
        for (int i = 0; i < n; i++)
        {
            if (strcmp(p->next->word, word) == 0)
            {
                p->next->count++;
                return;
            }
            else if (i == n - 1)
            {
                struct Word *temp = (struct Word *)malloc(sizeof(struct Word));
                strcpy(temp->word, word);
                temp->count = 1;
                if (strcmp(p->next->word, word) < 0)
                {
                    temp->next = NULL;
                    p->next->next = temp;
                }
                else
                {
                    temp->next = p->next;
                    p->next = temp;
                }
                n++;
                return;
            }
            else if (strcmp(p->next->word, word) < 0)
            {
                p = p->next;
            }
            else if (strcmp(p->next->word, word) > 0)
            {
                struct Word *temp = (struct Word *)malloc(sizeof(struct Word));
                strcpy(temp->word, word);
                temp->count = 1;
                temp->next = p->next;
                p->next = temp;
                n++;
                return;
            }
        }
    }
}

int main()
{
    FILE *fp,*stop;
    stop = fopen("stopwords.txt", "r");
    Stopnum = ReadStop(stop);
    fclose(stop);

    int len;

    fp = fopen("article.txt", "r");
    if (fp == NULL)
    {
        printf("can not open file\n");
        return 1;
    }
    char c;
    c = fgetc(fp);
    int pos = 0;
    int flag = 1;
    char word[MAX];
    while (c != EOF)
    {
        if (isalpha(c))
        {
            flag = 0;
            c = tolower(c);
            word[pos] = c;
            pos++;
        }
        else
        {
            if (flag != 1)
            {
                word[pos] = '\0';
                if (FindStop(word))
                    insert(word);
            }
            flag = 1;
            pos = 0;
        }
        c = fgetc(fp);
    }
    int count[1000] = {0};
    FILE *out;
    out = fopen("in.txt", "a+");
    int k = 0;
    while (head->next != NULL)
    {
        //fprintf(out, "%s %d\n", head->next->word, head->next->count);
        count[k++] = head->next->count;
        head = head->next;
    }
    qsort(count, k, sizeof(int), cmp);
    for (int i = 0;i<k;i++)
    {
        fprintf(out, "%d\n", count[i]);
    }
        free(head);
    fclose(fp);
    return 0;
}
