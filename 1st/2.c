#include <stdio.h>
#include <string.h>
void removeSpace(char *str)
{
    int i;
    for (i = strlen(str) - 1; i >= 0; i--)
    {
        if (str[i] == ' ')
        {
            for (int j = i + 1; j <= strlen(str); j++)
                str[j - 1] = str[j];
        }
    }
}

int main()
{
    char str[1000];
    gets(str);
    removeSpace(str);
    int i = 0, num = 0, n[100] = {0}, result = 0, k = 0, m = 0;
    char c, op[100];
    while (str[i] != '\0')
    {
        c = str[i];
        if (c >= '0' && c <= '9')
        {
            num = num * 10 + (c - '0');
        }
        else
        {
            op[m++]= c;
            n[k++] = num;
            num = 0;
        }
        i++;
    }
    i = 0;
    while (op[i] != '=')
    {
        if (op[i] == '*')
        {
            n[i] = n[i] * n[i + 1];
            for (int j = i + 1; j < k; j++)
            {    n[j] = n[j + 1];
                op[j-1] = op[j];
            }
        }
        else if (op[i] == '/')
        {
            n[i] = n[i] / n[i + 1];
            for (int j = i + 1; j < k; j++)
            {    n[j] = n[j + 1];
                op[j-1] = op[j];
            }
        }
        else
        i++;
    }
    i = 0;
    int j = 1;
    result = n[0];
    while (op[i] != '=')
    {   
        if (op[i] == '+')
        {
            result += n[j++];
        }
        else if (op[i] == '-')
        {
            result-=n[j++];
        }
        i++;
    }
printf("%d", result);
return 0;
}