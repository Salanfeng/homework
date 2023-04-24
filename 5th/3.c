#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode
{
    int n;
    struct TreeNode *left;
    struct TreeNode *right;
};

int stack[100];
int top = -1;
int mark = 0;
int toNum(char c)
{
    if (c == '+')
        return -mark - 1;
    else if (c == '-')
        return -mark - 2;
    else if (c == '*')
        return -mark - 3;
    else if (c == '/')
        return -mark - 4;
    return 0;
}

char toChar(int c)
{
    c = (-c) % 4;
    switch (c)
    {
    case 1:
        return '+';
    case 2:
        return '-';
    case 3:
        return '*';
    case 0:
        return '/';
    }
    return 0;
}

int getEquation(int equation[])
{
    int i = 0, j = 0;
    char c;
    while ((c = getchar()) != '=')
    {
        if (c >= '0' && c <= '9')
        {
            equation[i] = (c - '0') + equation[i] * 10;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            i++;
            j = toNum(c);
            while (top > -1 && (stack[top]-1)/2 <= (j-1)/2)
            {
                equation[i++] = stack[top--];
            }
            stack[++top] = j;
        }
        else if (c == '(')
        {
            mark += 4;
        }
        else if (c == ')')
        {
            mark -= 4;
        }
    }
    while (top > -1)
    {
        equation[++i] = stack[top--];
    }
    return i + 1;
}

void print(int n)
{
    if (n < 0)
    {
        printf("%c ", toChar(n));
    }
    else
    {
        printf("%d ", n);
    }
}

int calculate(struct TreeNode *p)
{
    if (p->left == NULL && p->right == NULL)
    {
        return p->n;
    }
    else
    {
        int a = calculate(p->left);
        int b = calculate(p->right);
        switch (-p->n%4)
        {
        case 1:
            return a + b;
        case 2:
            return a - b;
        case 3:
            return a * b;
        case 0:
            return a / b;
        }
    }
}

int main()
{
    int equation[200];
    int count = 0;
    for (int i = 0; i < 200; i++)
        equation[i] = 0;
    count = getEquation(equation); /*变成后缀表达*/

    
    /*for(int i=0;i<count;i++)
    {
        if(equation[i]<0)
        {
            printf("%c ",toChar(equation[i]));
        }
        else
        {
            printf("%d ",equation[i]);
        }
    }*/


    struct TreeNode *st[100];
    struct TreeNode *root = NULL;
    struct TreeNode *p, *q,*r;
    p = root;
    for (int i = 0; i < count; i++)
    {
        if (equation[i] >= 0)
        {
            p = (struct TreeNode *)malloc(sizeof(struct TreeNode));
            p->n = equation[i];
            p->left = NULL;
            p->right = NULL;
            st[++top] = p;
        }
        else
        {
            p = st[top--];
            q = st[top];
            r = (struct TreeNode *)malloc(sizeof(struct TreeNode));
            st[top] = r;
            st[top]->n = equation[i];
            st[top]->left = q;
            st[top]->right = p;
            root = st[top];
        }
    }
    p = root;
    print(p->n);
    print(p->left->n);
    print(p->right->n);
    printf("\n%d", calculate(root));
}
/*
12 * (15 + 12) /4=        * 12 / 
*/