#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX 500
char stopwords[500][15];
int n = 0,Stopnum=0;

void insert(char *);
int FindStop(char *);
int ReadStop(FILE *);
void ReadArticle(FILE *);
struct Word
{
    char word[MAX];
    int count;
    struct Word *next;
} WordNode;

struct Word *head = NULL;
struct Word *p;


void insert(char *word)
{
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
    int head = 0,num=Stopnum;
    while (head <= num)
    {
        if (strcmp(word, stopwords[head + (num - head) / 2]) == 0)
        {
            return 1;
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
    return 0;
}

void ReadArticle(FILE *article)
{
    article = fopen("article.txt", "r");
    if (article == NULL)
    {
        printf("can not open article file\n");
        return 1;
    }
    char c;
    c = fgetc(article);
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
                if (FindStop(word) == 0)
                {
                    insert(word);
                }
            }
            flag = 1;
            pos = 0;
        }
        c = fgetc(article);
    }
    fclose(article);
}

int main(int argc, char *argv[])
{
    int N, M;
    N = atoi(argv[1]);
    M = atoi(argv[2]);

    FILE *article, *stop, *hash, *sample;
    
    // read the stopwords
    Stopnum=ReadStop(stop);
    
    // read the article
    ReadArticle(article);
    
    return 0;
}
