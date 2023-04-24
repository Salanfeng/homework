#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>
#define MAX 100

char stopwords[500][15];
int wordnum = 0, Stopnum = 0, Hashnum = 0;
int N, M;

int printnum = 0;

int CompareWordCount(const void *, const void *);
int Findhash();
int ReadStop();
int FindStop(char *);
void ReadArticle();
void insert(char *);
void Deal();

void Readsample();
void Dealsample(char *);

void FreeAll();
void FreeHam();

struct HashWord
{
    char word[MAX];
    int count;
};

struct HashWord hashword[60000];
char hashvalue[10010][130];

struct Word
{
    char word[MAX];
    int count;
    struct Word *next;
};

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

inline int CompareWordCount(const void *a, const void *b)
{
    const struct HashWord *word1 = (const struct HashWord *)a;
    const struct HashWord *word2 = (const struct HashWord *)b;
    if (word1->count < word2->count)
        return 1;
    else if (word1->count > word2->count)
        return -1;
    else if (strcmp(word1->word, word2->word) > 0)
        return 1;
    else
        return -1;
}
int Findhash()
{
    FILE *article;
    article = fopen("article.txt", "r");
    char c;
    c = fgetc(article);
    int pos = 0;
    int flag = 1;
    for (int i = 0; i < 60000; i++)
    {
        hashword[i].word[0] = '\0';
        hashword[i].count = 0;
    }
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
                int found = 0;
                int j;
                word[pos] = '\0';
                if (FindStop(word) == 1)
                {
                    for (j = 0; j < 60000 && (hashword[j].count > 0); j++)
                    {
                        if (strcmp(hashword[j].word, word) == 0)
                        {
                            hashword[j].count++;
                            found = 1;
                            break;
                        }
                    }

                    if (!found)
                    {
                        strcpy(hashword[j].word, word);
                        hashword[j].count = 1;
                        Hashnum = j;
                    }
                }
            }
            flag = 1;
            pos = 0;
        }
        c = fgetc(article);
    }
    qsort(hashword, Hashnum + 1, sizeof(struct HashWord), CompareWordCount);
    fclose(article);
    FILE *hashfile;
    hashfile = fopen("hashvalue.txt", "r");
    int count = 0;
    while (count < N)
    {
        fscanf(hashfile, "%s", hashvalue[count]);
        count++;
    }
    return 0;
}

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
int ReadStop()
{
    FILE *stop;
    stop = fopen("stopwords.txt", "r");
    if (stop == NULL)
    {
        printf("can not open stop file\n");
        return 1;
    }

    int i = 0, Snum = 0;
    while (fscanf(stop, "%s", stopwords[i]) != EOF)
    {
        i++;
    }
    Snum = i;
    fclose(stop);
    return Snum;
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

void ReadArticle()
{
    FILE *article;
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
    p = head;
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
    struct Word *p;
    int fingerprint[130];
    for (int i = 0; i < M; i++)
    {
        fingerprint[i] = 0;
    }
    struct Word *resort = (struct Word *)malloc(sizeof(struct Word) * wordnum);
    p = temp;

    for (int i = 0; i < wordnum; i++)
    {
        resort[i].count = p->count;
        strcpy(resort[i].word, p->word);

        p = p->next;
    }
    qsort(resort, wordnum, sizeof(struct Word), CompareWordCount);
    p = temp;
    for (int i = 0; i < wordnum; i++)
    {
        p->count = resort[i].count;
        strcpy(p->word, resort[i].word);
        p = p->next;
    }
    // FILE *test;
    // test = fopen("test.txt", "a+");
    for (int i = 0; i < N && temp != NULL; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (strcmp(temp->word, hashword[j].word) == 0)
            {

                for (int k = 0; k < M; k++)
                {
                    if (hashvalue[j][k] == '1')
                    {
                        fingerprint[k] += temp->count;
                    }
                    else
                    {
                        fingerprint[k] -= temp->count;
                    }
                }
                break;
            }
        }
        temp = temp->next;
    }
    // fclose(test);

    for (int i = 0; i < M; i++)
    {
        if (fingerprint[i] > 0)
        {
            ap->fingerprint[i] = '1';
        }
        else
        {
            ap->fingerprint[i] = '0';
        }
    }
    ap->fingerprint[M] = '\0';
    // free(weight);
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
    c = fgetc(sample);

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
    int fingerprint[130];
    for (int i = 0; i < M; i++)
    {
        fingerprint[i] = 0;
    }
    for (int i = 0; i < N && temp != NULL; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (strcmp(temp->word, hashword[j].word) == 0)
            {

                for (int k = 0; k < M; k++)
                {
                    if (hashvalue[j][k] == '1')
                        fingerprint[k] += temp->count;
                    else
                        fingerprint[k] -= temp->count;
                }
                break;
            }
        }
        temp = temp->next;
    }
    char samplefinger[130];
    for (int i = 0; i < M; i++)
    {
        samplefinger[i] = fingerprint[i] > 0 ? '1' : '0';
    }
    samplefinger[M] = '\0';

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
    result = fopen("result.txt", "a");
    if (printnum == 0)
        printf("%s", name);
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
                    if (printnum == 0)
                    {
                        printf("\n");
                        printf("%d:", dist);
                    }
                    fprintf(result, "\n");
                    fprintf(result, "%d:", dist);
                    flag = 1;
                }
                if (printnum == 0)
                    printf("%s ", hamming->name);
                fprintf(result, "%s ", hamming->name);
            }
            hamming = hamming->next;
        }

        dist++;
    }
    hamming->next = NULL;
    FreeHam();
    fprintf(result, "\n");
    fclose(result);
    printnum = 1;
    return;
}
int main(int argc, char *argv[])
{
    // time_t start, end;
    // start = clock();
    //  传参太麻烦，先写死
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    // N = 1000;
    // M = 16;
    Stopnum = ReadStop();

    Findhash();
    ReadArticle();
    Readsample();

    // article每篇文章的指纹输出到test文件
    /*ap = ahead;
    FILE *test;
    test = fopen("test4.txt", "w");
    while (ap != NULL)
    {
        fprintf(test, "%s\n", ap->fingerprint);
        ap = ap->next;
    }
    for (int i = 0; i < N; i++)
        fprintf(test, "%s %d\n", hashword[i].word, hashword[i].count);
    fclose(test);*/

    // end = clock();
    // printf("\ntime = %f", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
