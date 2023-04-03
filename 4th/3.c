#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1024

int opnum;
int nump[MAX];
int getEquation(double num[], char op[])
{
    int i = 0, j = 0, mark = 0, max = 0;
    char c;
    num[0] = 0;
    while ((c = getchar()) != '=')
    {
        if (c >= '0' && c <= '9')
        {
            num[i] = (c - '0') + num[i] * 10;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            nump[j] = mark;
            op[j++] = c;
            i++;
            num[i] = 0;
        }
        else if (c == '(')
        {
            mark++;
            if (max < mark)
                max = mark;
        }
        else if (c == ')')
        {
            mark--;
        }
    }
    op[j] = '=';
    opnum = j + 1;
    num[i + 1] = -114514;

    return max;
}

void divide(double *n, char *op, int priority)
{
    int i = 0, mark = 0;
    while (priority >= 0)
    {
        int i = 0, k = opnum;
        while (op[i] != '=')
        {
            if (op[i] == '*' && nump[i] == priority)
            {
                n[i] = n[i] * n[i + 1];
                for (int j = i + 1; j < k; j++)
                {
                    n[j] = n[j + 1];
                    op[j - 1] = op[j];
                    nump[j - 1] = nump[j];
                }
                opnum--;
            }
            else if (op[i] == '/' && nump[i] == priority)
            {
                n[i] = n[i] / n[i + 1];
                for (int j = i + 1; j < k; j++)
                {
                    n[j] = n[j + 1];
                    op[j - 1] = op[j];
                    nump[j - 1] = nump[j];
                }
                opnum--;
            }
            else
                i++;
        }
        i = 0;
        while (op[i] != '=')
        {
            if (op[i] == '+' && nump[i] == priority)
            {
                n[i] = n[i] + n[i + 1];
                for (int j = i + 1; j < k; j++)
                {
                    n[j] = n[j + 1];
                    op[j - 1] = op[j];
                    nump[j - 1] = nump[j];
                }
                opnum--;
            }
            else if (op[i] == '-' && nump[i] == priority)
            {
                n[i] = n[i] - n[i + 1];
                for (int j = i + 1; j < k; j++)
                {
                    n[j] = n[j + 1];
                    op[j - 1] = op[j];
                    nump[j - 1] = nump[j];
                }
                opnum--;
            }
            else
                i++;
        }
        priority--;
    }
    return;
}

int main()
{
    int b;
    double num[MAX];
    char op[MAX];
    b = getEquation(num, op);
    divide(num, op, b);
    printf("%.2lf", num[0]);
    return 0;
}