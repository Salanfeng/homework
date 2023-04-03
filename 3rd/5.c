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

int n = 0;
struct Word *head = NULL;
struct Word *p;
void insert(char *word)
{
//    printf("%s %d\n", word, n);
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
    FILE *fp;
    
    int len;

    fp = fopen("article.txt", "r");
    if (fp == NULL)
    {
        printf("can not open file\n");
        return 1;
    }
    char c;
    c=fgetc(fp);
    int pos=0;
    int flag=1;
    char word[MAX];
    while(c!=EOF){
        if(isalpha(c)){
            flag=0;
            c=tolower(c);
            word[pos]=c;
            pos++;
        }
        else{
            if(flag!=1)
            {
                word[pos]='\0';
                insert(word);
            }
            flag=1;
            pos=0;
        }
        c=fgetc(fp);
    }
    while(head->next !=NULL)
    {
        printf("%s %d\n", head->next->word, head->next->count);
        head = head->next;
    }
    free(head);
    fclose(fp);
    return 0;
}


