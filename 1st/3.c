#include <stdio.h>
#include <string.h>
int main()
{
    char input[200];
    double num;
    int exp = 0, flag = 0;
    int pointPos, noneZero;
    gets(input);
    for (int i = 0;; i++)
    {
        if (input[i] == '.')
        {
            pointPos = i;
            break;
        }
    }
    for (int i = 0;; i++)
    {
        if (input[i] != '0' && input[i] != '.')
        {
            noneZero = i;
            break;
        }
    }

    exp = pointPos - noneZero - 1;
    if (pointPos < noneZero)
        exp++;
    int i = 0;
    while (input[i] == '0' || input[i] == '.')
        i++;
    for (; i < strlen(input); i++)
    {
        if (input[i] != '.')
            printf("%c", input[i]);
        if (flag == 0 && noneZero != strlen(input) - 1)
        {
            printf(".");
            flag = 1;
        }
    }
    printf("e%d", exp);

    return 0;
}
