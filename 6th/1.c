#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
#define NHASH 3001
#define MULT 37
char Dict[4000][MAX];
int IndexDict[26][2];
int Sum = 0;

struct HashDict
{
    char word[MAX];
    struct HashDict *next;
};
struct HashDict *HashDict[NHASH]={NULL};
unsigned int hash(char *str)
{
    unsigned int h = 0;
    char *p;
    for (p = str; *p != '\0'; p++)
        h = MULT * h + *p;
    return h % NHASH;
}
void InsertHash(char *word)
{
    unsigned int h = hash(word);
    struct HashDict *p = HashDict[h];
    if (HashDict[h] == NULL)
    {
        HashDict[h] = (struct HashDict *)malloc(sizeof(struct HashDict));
        strcpy(HashDict[h]->word, word);
        HashDict[h]->next = NULL;
        return;
    }
    else
    {
        struct HashDict *q;
        while (p != NULL)
        {
            if (strcmp(p->word, word) < 0)
            {
                q = p;
                p = p->next;
            }
            else
            {
                break;
            }
        }
        if (p == NULL)
        {
            q->next = (struct HashDict *)malloc(sizeof(struct HashDict));
            strcpy(q->next->word, word);
            q->next->next = NULL;
            return;
        }
        else
        {
            struct HashDict *temp = (struct HashDict *)malloc(sizeof(struct HashDict));
            strcpy(temp->word, word);
            temp->next = p;
            q->next = temp;
            return;
        }
    }
}
void ReadWord()
{
    FILE *fp;
    int i = 0;
    fp = fopen("dictionary3000.txt", "r");
    char ch = 'a';
    IndexDict[0][0] = 0;
    while (fscanf(fp, "%s", Dict[i]) != EOF)
    {
        InsertHash(Dict[i]);
        if (ch != Dict[i][0])
        {
            IndexDict[ch - 'a'][1] = i - 1;
            IndexDict[Dict[i][0] - 'a'][0] = i;
        }
        ch = Dict[i][0];
        i++;
    }
    IndexDict[ch - 'a'][1] = i - 1;
    Sum = i;
    fclose(fp);
}
void Sequence(char *word)
{
    int count = 0;
    int find = 0;
    for (int i = 0; i < Sum; i++)
    {
        count++;
        if (strcmp(word, Dict[i]) == 0)
        {
            find = 1;
            break;
        }
        else if (strcmp(word, Dict[i]) < 0)
        {
            break;
        }
    }
    printf("%d %d\n", find, count);
}

void Half(char *word)
{
    int head = 0, num = Sum - 1;
    int count = 0;
    while (head <= num)
    {
        count++;
        int mid = head + (num - head) / 2;
        if (strcmp(word, Dict[mid]) == 0)
        {
            printf("1 %d\n", count);
            return;
        }
        else if (strcmp(word, Dict[mid]) > 0)
        {
            head = mid + 1;
        }
        else
        {
            num = mid - 1;
        }
    }
    printf("0 %d\n", count);
    return;
}
void Index(char *word)
{
    int head = IndexDict[word[0] - 'a'][0], num = IndexDict[word[0] - 'a'][1];
    int count = 0;
    while (head < num)
    {
        count++;
        int mid = head + (num - head) / 2;
        if (strcmp(word, Dict[mid]) == 0)
        {
            printf("1 %d\n", count);
            return;
        }
        else if (strcmp(word, Dict[mid]) > 0)
        {
            head = mid + 1;
        }
        else
        {
            num = mid - 1;
        }
    }
    printf("0 %d\n", count);
    return;
}
void Hash(char *word)
{
    unsigned int h = hash(word);
    struct HashDict *p = HashDict[h];
    int count = 0;
    while (p != NULL)
    {
        count++;
        if (strcmp(p->word, word) == 0)
        {
            printf("1 %d\n", count);
            return;
        }
        else if (strcmp(p->word, word) < 0)
        {
            p = p->next;
        }
        else
        {
            printf("0 %d\n", count);
            return;
        }
    }
    printf("0 %d\n", count);
}
int main()
{
    char word[MAX];
    int flag = 0;
    ReadWord();
    while (scanf(" %s", word) != EOF)
    {
        scanf("%d", &flag);
        switch (flag)
        {
        case 1:
            Sequence(word);
            break;
        case 2:
            Half(word);
            break;
        case 3:
            Index(word);
            break;
        case 4:
            Hash(word);
            break;
        default:
            break;
        }
    }
    return 0;
}