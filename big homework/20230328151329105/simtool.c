#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>
#define MAX 85
char stopwords[500][15];
int wordnum = 0, Stopnum = 0;
int N, M;
void Deal();
void insert(char *);
int FindStop(char *);
int ReadStop(FILE *);
void ReadArticle(FILE *);
void FreeAll();
void FreeHam();
void Dealsample(char *);
struct Word
{
    char word[MAX];
    int count;
    struct Word *next;
} WordNode;

struct Article
{
    char fingerprint[130];
    char name[50];
    struct Article *next;
};
struct Hamming
{
    int diff;
    char name[20];
    struct Hamming *next;
};
struct Word *head = NULL;
struct Word *p;
struct Hamming *hamminghead = NULL;

struct Article *ahead = NULL;
struct Article *ap;

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

    article = fopen("article.txt", "r");
    if (article == NULL)
    {
        printf("can not open article file\n");
        return;
    }
    char c;
    ahead = (struct Article *)malloc(sizeof(struct Article));
    fscanf(article, "%s", ahead->name);
    ap = ahead;

    c = fgetc(article);
    int pos = 0;
    int flag = 1;
    char word[MAX];
    while (c != EOF)
    {
        if (c == 12)
        {
            Deal();
            FreeAll();
            fgetc(article);
            ap->next = (struct Article *)malloc(sizeof(struct Article));
            ap = ap->next;
            ap->next = NULL;
            fscanf(article, "%s", ap->name);
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
    Deal();
    FreeAll();
    fclose(article);
}
void FreeAll()
{
    struct Word *q;
    p = head->next;
    while (p != NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }
    wordnum = 0;
    head = NULL;
}
void FreeHam()
{
    struct Hamming *q;
    struct Hamming *p = hamminghead->next;
    while (p != NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }
    hamminghead = NULL;
}
void Deal()
{
    struct Word *temp = head->next;
    int *weight = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
    {
        weight[i] = 0;
    }
    // FILE *test;
    // test = fopen("test.txt", "a+");
    while (temp != NULL)
    {
        // fprintf(test, "%s %d\n", temp->word, temp->count);
        if (temp->count > weight[N - 1])
        {

            int k = N - 1;
            while (weight[k] == 0 && k > 0)
                k--;
            k++;
            weight[k] = temp->count;
            for (int j = k; j > 0; j--)
            {
                if (weight[j] > weight[j - 1])
                {
                    int temp = weight[j];
                    weight[j] = weight[j - 1];
                    weight[j - 1] = temp;
                }
            }
        }
        temp = temp->next;
    }
    // fclose(test);

    /*FILE *test;
    test = fopen("test.txt", "a+");
    int SSum = 0;
    for (int i = 0; i < N; i++)
    {
        fprintf(test, "%d ", weight[i]);
        SSum += weight[i];
    }
    fprintf(test, "%d\n", SSum);
    fclose(test);*/

    int fingeprint[130];
    for (int i = 0; i < M; i++)
    {
        fingeprint[i] = 0;
    }
    FILE *hashfile;
    char buffer[130];
    hashfile = fopen("hashvalue.txt", "r");
    FILE *test;
    test = fopen("test3.txt", "a+");
    for (int i = 0; i < N && weight[i] != 0; i++)
    {
        fgets(buffer, 130, hashfile);
        for (int j = 0; j < M; j++)
        {
            if (buffer[j] == '1')
            {
                fingeprint[j] += weight[i];
                if (j == 1)
                fprintf(test, "%d ",weight[i]);
            }
            else
            {
                fingeprint[j] -= weight[i];
                if (j == 1)
                fprintf(test, "-%d ",weight[i]);
            }
        }
    }
    fprintf(test, "%d\n",fingeprint[1]);
    fclose(test);

    for (int i = 0; i < M; i++)
    {
        if (fingeprint[i] > 0)
        {
            ap->fingerprint[i] = '1';
            
        }
        else
        {
            ap->fingerprint[i] = '0';
            
        }
    }
    ap->fingerprint[M] = '\0';



    fclose(hashfile);
    free(weight);
    return;
}

void Readsample()
{
    FILE *sample;
    sample = fopen("sample.txt", "r");
    if (sample == NULL)
    {
        printf("can not open sample file\n");
        return;
    }

    char name[20], c;

    fscanf(sample, "%s", name);
    fgetc(sample);

    int pos = 0;
    int flag = 1;
    char word[MAX];

    while (c != EOF)
    {
        if (c == 12)
        {
            Dealsample(name);
            FreeAll();
            fgetc(sample);
            fscanf(sample, "%s", name);
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
        c = fgetc(sample);
    }
    fclose(sample);
}

void Dealsample(char *name)
{
    struct Word *temp = head->next;
    int *weight = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
    {
        weight[i] = 0;
    }
    while (temp != NULL)
    {

        if (temp->count > weight[N - 1])
        {

            int k = N - 1;
            while (weight[k] == 0 && k > 0)
                k--;
            k++;
            weight[k] = temp->count;
            for (int j = k; j > 0; j--)
            {
                if (weight[j] > weight[j - 1])
                {
                    int temp = weight[j];
                    weight[j] = weight[j - 1];
                    weight[j - 1] = temp;
                }
            }
        }
        temp = temp->next;
    }

    /*FILE *test;
    test = fopen("test.txt", "a+");
    int SSum = 0;
    for (int i = 0; i < N; i++)
    {
        fprintf(test, "%d ", weight[i]);
        SSum += weight[i];
    }
    fprintf(test, "%d\n", SSum);
    fclose(test);*/

    int fingeprint[130];
    for (int i = 0; i < M; i++)
    {
        fingeprint[i] = 0;
    }
    FILE *hashfile;
    char buffer[130];
    hashfile = fopen("hashvalue.txt", "r");

    for (int i = 0; i < N; i++)
    {
        fgets(buffer, 130, hashfile);
        for (int j = 0; j < M; j++)
        {
            if (buffer[j] == '1')
            {
                fingeprint[j] += weight[i];
            }
            else
            {
                fingeprint[j] -= weight[i];
            }
        }
    }
    char samplefinger[130];
    for (int i = 0; i < M; i++)
    {
        samplefinger[i] = fingeprint[i] > 0 ? '1' : '0';
    }
    samplefinger[M] = '\0';

    /*FILE *test;
    test = fopen("test.txt", "a+");
    fprintf(test, "%s", samplefinger);
    fprintf(test, "\n");
    fclose(test);*/

    struct Article *rank;
    struct Hamming *hamming;
    hamminghead = (struct Hamming *)malloc(sizeof(struct Hamming));
    hamminghead->next = (struct Hamming *)malloc(sizeof(struct Hamming));
    hamming = hamminghead->next;
    rank = ahead;
    while (rank != NULL)
    {
        int dist = 0;
        char tempfinger[130];
        strcpy(tempfinger, rank->fingerprint);
        int j = 0;
        while (j < M)
        {
            if (tempfinger[j] != samplefinger[j])
            {
                dist++;
            }
            j++;
        }
        if (dist <= 3)
        {
            hamming->diff = dist;
            strcpy(hamming->name, rank->name);
            hamming->next = (struct Hamming *)malloc(sizeof(struct Hamming));
            hamming = hamming->next;
        }
        rank = rank->next;
    }
    struct Hamming *stophamming;
    stophamming = hamming;
    FILE *result;
    result = fopen("result.txt", "a+");
    fprintf(result, "%s", name);
    int dist = 0;
    while (dist < 4)
    {
        int flag = 0;
        hamming = hamminghead->next;
        while (hamming != stophamming)
        {
            if (hamming->diff == dist)
            {
                if (flag == 0)
                {
                    fprintf(result, "\n");
                    fprintf(result, "%d:", dist);
                    flag = 1;
                }
                fprintf(result, "%s ", hamming->name);
            }
            hamming = hamming->next;
        }

        dist++;
    }
    hamming->next = NULL;
    FreeHam();
    fprintf(result, "\n");
    fclose(hashfile);
    fclose(result);
    free(weight);
    return;
}
int main(int argc, char *argv[])
{
    time_t start, end;
    start = clock();
    // N = atoi(argv[1]);
    // M = atoi(argv[2]);
    N = 1000;
    M = 16;

    FILE *article, *stop;

    // read the stopwords
    Stopnum = ReadStop(stop);

    // read the article
    ReadArticle(article);
    Readsample();

    /*ap = ahead;
    FILE *test;
    test = fopen("test.txt", "w");
    while (ap != NULL)
    {
        fprintf(test, "%s\n", ap->fingerprint);
        ap = ap->next;
    }
    fclose(test);*/
    end = clock();
    printf("time = %f", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
