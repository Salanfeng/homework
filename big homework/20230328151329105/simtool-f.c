#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>
#define MAX 85
#define MAXN 10000
char stopwords[500][15];
int wordnum = 0, Stopnum = 0;
int N, M;
void Deal(int *);
void insert(char *);
int FindStop(char *);
int ReadStop(FILE *);
void ReadArticle(FILE *);
void FreeAll();
void Readsample();
void Dealsample(int *);

struct Article
{
    char fingerprint[130];
    char name[20];
    struct Article *next;
};

struct Hamming
{
    int dist;
    char name[20];
    struct Hamming *next;
};

struct Article *ahead = NULL;
struct Article *ap;

int hashstring(char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    int result = (int)(hash % (MAXN + 1));

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

    // FILE *test;
    // test = fopen("test.txt", "w");
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

    unsigned int Hash[MAXN];
    for (int i = 0; i < MAXN; i++)
    {
        Hash[i] = 0;
    }
    while (c != EOF)
    {
        if (c == 12)
        {
            Deal(Hash);
            /*fprintf(test, "%s\n", ap->name);
            for (int i = 0; i < MAXN; i++)
            {
                fprintf(test, "%d ", Hash[i]);
            }
            fprintf(test, "\n\n\n\n");
*/
            fgetc(article);
            ap->next = (struct Article *)malloc(sizeof(struct Article));
            ap = ap->next;
            ap->next = NULL;
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
    Deal(Hash);
    fclose(article);
    // fclose(test);
}

void Deal(int *Hash)
{
    int *fingeprint = (int *)malloc(sizeof(int) * M);
    for (int i = 0; i < M; i++)
    {
        fingeprint[i] = 0;
    }
    FILE *hashfile;
    char buffer[130];
    if (hashfile == NULL)
    {
        printf("can not open hash file\n");
        return;
    }
    hashfile = fopen("hashvalue.txt", "r");
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

    /*FILE *test;
    test = fopen("test.txt", "a+");
    for (int i = 0; i < N; i++)
        fprintf(test, "%d ", weight[i]);
    fprintf(test, "\n");
    fclose(test);*/
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

    unsigned int Hash[MAXN];
    for (int i = 0; i < MAXN; i++)
    {
        Hash[i] = 0;
    }
    while (c != EOF)
    {
        if (c == 12)
        {
            fprintf(sample, "%s\n", name);
            Dealsample(Hash);
            fgetc(sample);
            fscanf(sample, "%s", name);
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
        c = fgetc(sample);
    }
    Dealsample(Hash);
    fclose(sample);
}

void Dealsample(int *Hash)
{
    int *fingeprint = (int *)malloc(sizeof(int) * M);
    for (int i = 0; i < M; i++)
    {
        fingeprint[i] = 0;
    }
    FILE *hashfile;
    hashfile = fopen("hashvalue.txt", "r");
    char buffer[130];
    if (hashfile == NULL)
    {
        printf("can not open hash file\n");
        return;
    }
    hashfile = fopen("hashvalue.txt", "r");
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
    FILE *test;
    test = fopen("test.txt", "w");
    fprintf(test, "%s\n", samplefinger);
    struct Article *temp;
    struct Hamming *hamming, *hamminghead;
    hamminghead = (struct Hamming *)malloc(sizeof(struct Hamming));
    hamming = hamminghead;
    hamming->next = NULL;
    temp = ahead;
    int pagenum = 0;
    while (temp != NULL)
    {

        int dist = 0;
        char *tempfinger = (char *)malloc(sizeof(char) * M);
        strcpy(tempfinger, temp->fingerprint);
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
            pagenum++;
            hamming->next = (struct Hamming *)malloc(sizeof(struct Hamming));
            hamming = hamming->next;
            strcpy(hamming->name, temp->name);
            hamming->dist = dist;
            hamming->next = NULL;
        }
        temp = temp->next;
    }
    FILE *result;
    result = fopen("result.txt", "w");
    int dist = 0;
    while (dist < 4)
    {
        int flag = 0;
        hamming = hamminghead->next;
        while (hamminghead != NULL)
        {
            if (hamminghead->dist == dist)
            {
                if (flag == 0)
                {
                    fprintf(result, "%d:", dist);
                    flag == 1;
                }
                printf("%s ", hamminghead->name);
            }
            hamming = hamming->next;
        }
        fprintf(result, "\n");
    }
    fclose(hashfile);
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

    FILE *article, *stop, *sample;

    // read the stopwords
    Stopnum = ReadStop(stop);

    // read the article
    ReadArticle(article);

    // test code
    int pagenum = 0;
    ap = ahead;
    FILE *test;
    test = fopen("test.txt", "w");
    while (ap != NULL)
    {
        pagenum++;
        //fprintf(test, "%s\n", ap->name);
        fputs(ap->fingerprint, test);
        fprintf(test, "\n");
        ap = ap->next;
    }
    //printf("pagenum = %d", pagenum);
    fclose(test);
    // Readsample();
    end = clock();
    printf("time = %f", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
