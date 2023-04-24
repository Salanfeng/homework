#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

struct TreeNode
{
    char word[100];
    int count;
    struct TreeNode *left;
    struct TreeNode *right;
};
struct TreeNode *root = NULL;
struct TreeNode *p;
void insert(char *word)
{
    p = root;
    if (p == NULL)
    {
        p = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        strcpy(p->word, word);
        p->count = 1;
        p->left = NULL;
        p->right = NULL;
        root = p;
        return;
    }
    else
        while (1)
        {
            if (strcmp(word, p->word) == 0)
            {
                p->count++;
                return;
            }
            else if (strcmp(word, p->word) < 0)
            {
                if (p->left == NULL)
                {
                    p->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                    strcpy(p->left->word, word);
                    p->left->count = 1;
                    p->left->left = NULL;
                    p->left->right = NULL;
                    return;
                }
                else
                {
                    p = p->left;
                }
            }
            else
            {
                if (p->right == NULL)
                {
                    p->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                    strcpy(p->right->word, word);
                    p->right->count = 1;
                    p->right->left = NULL;
                    p->right->right = NULL;
                    return;
                }
                else
                {
                    p = p->right;
                }
            }
        }
}

void LRD(struct TreeNode *root)
{
    if (root == NULL)
        return;
    LRD(root->left);
    printf("%s %d\n", root->word, root->count);
    LRD(root->right);
    return;
}

int main()
{
    FILE *article;
    article = fopen("article.txt", "r");
    int N, num;
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
                insert(word);
            }
            flag = 1;
            pos = 0;
        }
        c = fgetc(article);
    }
    if (root != NULL)
        printf("%s ", root->word);
    if (root->right != NULL)
        printf("%s ", root->right->word);
    if (root->right->right != NULL)
        printf("%s ", root->right->right->word);
    printf("\n");
    LRD(root);
    return 0;
}