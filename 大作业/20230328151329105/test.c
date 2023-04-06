#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 500
int n = 0,len=0;
char MW[MAX];
void insert(char *);
void ReadArticle(FILE *);
struct Word
{
    char word[MAX];
    int count;
    struct Word *next;
} WordNode;

struct Word *head = NULL;
struct Word *p;
void ReadArticle(FILE *article)
{
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
                //insert(word);
                if(len<strlen(word))
                {
                    len=strlen(word);
                    strcpy(MW, word);
                }
            }
            flag = 1;
            pos = 0;
        }
        c = fgetc(article);
    }
    fclose(article);
}

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

int main()
{
    FILE *article;
    ReadArticle(article);
    printf("%d\n%s",len,MW);
    return 0;
}
