#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#define MAX 85
#define MAXN 4001
char stopwords[500][15];
int wordnum = 0, Stopnum = 0;
int N, M;
void Deal(int *);
void insert(char *);
int FindStop(char *);
int ReadStop(FILE *);
void ReadArticle(FILE *);
void FreeAll();
/*struct Word
{
    char word[MAX];
    int count;
    struct Word *next;
} WordNode;*/

struct Artical
{
    char fingerprint[130];
    char name[50];
    struct Artical *next;
};


struct Artical *ahead = NULL;
struct Artical *ap;

int hashstring(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    int result =(int)( hash % (MAXN+1));

    return result;
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

void ReadArticle(FILE *article)
{

    FILE *test;
    test = fopen("test.txt", "w");
    article = fopen("article.txt", "r");
    if (article == NULL)
    {
        printf("can not open article file\n");
        return;
    }

    char c;
    ahead = (struct Artical *)malloc(sizeof(struct Artical));
    fscanf(article, "%s", ahead->name);
    ap = ahead;

    c = fgetc(article);
    int pos = 0;
    int flag = 1;
    char word[MAX];

    unsigned int Hash[MAXN];
    for (int i = 0; i < MAXN; i++)
    {
        Hash[i] = 0;
    }
    while (c != EOF)
    {
        if (c == 12)
        {
            // Deal(Hash);
            fprintf(test, "%s\n", ap->name);
            for (int i = 0; i < MAXN; i++)
            {
                fprintf(test, "%d", Hash[i]);
            }
            fprintf(test, "\n\n\n\n");
            fgetc(article);
            ap->next = (struct Artical *)malloc(sizeof(struct Artical));
            ap = ap->next;
            fscanf(article, "%s", ap->name);
            for (int i = 0; i < MAXN; i++)
            {
                Hash[i] = 0;
            }
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
                    Hash[hashstring(word)]++;
                }
            }
            flag = 1;
            pos = 0;
        }
        c = fgetc(article);
    }
    fclose(article);
    fclose(test); 
}

void Deal(int *Hash)
{
    int *fingeprint = (int *)malloc(sizeof(int) * M);
    for (int i = 0; i < M; i++)
    {
        fingeprint[i] = 0;
    }
    FILE *hash;
    char buffer[130];
    hash = fopen("hashvalue.txt", "r");
    int *weight = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
    {
        weight[i] = 0;
    }
    for (int i = 0; i < MAXN; i++)
    {
        if (Hash[i] > weight[N - 1])
        {
            weight[N - 1] = Hash[i];
            for (int j = N - 1; j > 0; j--)
            {
                if (weight[j] > weight[j - 1])
                {
                    int temp = weight[j];
                    weight[j] = weight[j - 1];
                    weight[j - 1] = temp;
                }
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        fgets(buffer, 130, hash);
        for (int j = 0; j < M; j++)
        {
            if (buffer[j] == '1')
            {
                fingeprint[i] += weight[i];
            }
            else
            {
                fingeprint[i] -= weight[i];
            }
        }
    }
    fclose(hash);
    for (int i = 0; i < M; i++)
    {
        if (fingeprint[i] > 0)
        {
            ap->fingerprint[i] = 1;
        }
        else
        {
            ap->fingerprint[i] = 0;
        }
    }
    ap->fingerprint[M] = '\0';

    return;
}

int main(int argc, char *argv[])
{
    // N = atoi(argv[1]);
    // M = atoi(argv[2]);
    N = 1000;
    M = 16;

    FILE *article, *stop, *sample;

    // read the stopwords
    Stopnum = ReadStop(stop);

    // read the article
    ReadArticle(article);

    /*ap = ahead;
    FILE *test;
    test = fopen("test.txt", "w");
    while (ap != NULL)
    {
        for (int i = 0; i < M; i++)
        {
            fprintf(test, "%d", ap->fingerprint[i]);
        }
        fprintf(test, "\n");
        ap = ap->next;
    }
    fclose(test);*/
    return 0;
}
