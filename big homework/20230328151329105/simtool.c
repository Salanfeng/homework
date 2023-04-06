#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#define MAX 500
char stopwords[500][15];
int wordnum = 0,Stopnum=0;
int N, M,filenum=0;
void Deal();
void insert(char *);
int FindStop(char *);
int ReadStop(FILE *);
void ReadArticle(FILE *);
void FreeAll();
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
    if (wordnum == 0)
    {
        head = (struct Word *)malloc(sizeof(struct Word));
        head->next = (struct Word *)malloc(sizeof(struct Word));
        strcpy(head->next->word, word);
        head->next->count = 1;
        head->next->next = NULL;
        wordnum++;
        return;
    }
    else
    {
        p = head;
        for (int i = 0; i < wordnum; i++)
        {
            if (strcmp(p->next->word, word) == 0)
            {
                p->next->count++;
                return;
            }
            else if (i == wordnum - 1)
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
                wordnum++;
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
                wordnum++;
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

void ReadArticle(FILE *article)
{
    FILE *test;
    test = fopen("test.txt", "w");
    article = fopen("article.txt", "r");
    if (article == NULL)
    {
        printf("can not open article file\n");
        return ;
    }
    char c;
    c = fgetc(article);
    int pos = 0;
    int flag = 1;
    char word[MAX];
    while (c != EOF)
    {
        fprintf(test, "%c", c);
        if(c==12)
        {
            Deal();
            filenum++;
            FreeAll();
        }
        else if (isalpha(c))
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
                if (FindStop(word) == 1)
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
void FreeAll()
{
    struct Word *q;
    p = head;
    while(p!=NULL)
    {
        q= p;
        p = p->next;
        free(q);
    }
    wordnum = 0;
    head = NULL;
}

void Deal()
{
    return;
}


int main(int argc, char *argv[])
{
    //N = atoi(argv[1]);
    //M = atoi(argv[2]);
    N = 1000;
    M = 16;

    FILE *article, *stop, *hash, *sample;
    
    // read the stopwords
    Stopnum=ReadStop(stop);
    
    // read the article
    ReadArticle(article);
    printf("%d",filenum);
    return 0;
}
