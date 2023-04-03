#include <stdio.h>
#include <string.h>

#define MAX_LEN 81
void removeZero(char *str)
{
    int i = 0;
    while (str[i] == '0')
        i++;
    if (str[i] == '\0')
    {
        str[0] = '0';
        str[1] = '\0';
    }
    else
    {
        int j = 0;
        while (str[i] != '\0')
        {
            str[j] = str[i];
            i++;
            j++;
        }
        str[j] = '\0';
    }
}

int main()
{
    char num1[MAX_LEN], num2[MAX_LEN];
    int result[MAX_LEN];
    int len1, len2, i, j, borrow,flag=0;

    gets(num1);
    gets(num2);
    removeZero(num1);
    removeZero(num2);
    len1 = strlen(num1);
    len2 = strlen(num2);
    if(len1 < len2)
        flag = 1;
    else if(len1 == len2)
    {
        for(i=0;i<len1;i++)
        {
            if(num1[i] < num2[i])
            {
                flag = 1;
                break;
            }
            else if(num1[i] > num2[i])
                break;
        }
    }

    if(flag==1)
    {
        char temp[MAX_LEN];
        strcpy(temp,num1);
        strcpy(num1,num2);
        strcpy(num2,temp);
        int temp2 = len1;
        len1 = len2;
        len2 = temp2;
    }
    borrow = 0;
    for (i = len1 - 1, j = len2 - 1; i >= 0 || j >= 0; i--, j--)
    {
        int digit1 = i >= 0 ? num1[i] - '0' : 0;
        int digit2 = j >= 0 ? num2[j] - '0' : 0;
        int diff = digit1 - digit2 - borrow;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        result[i] = diff;
    }
    if(flag==1)
        printf("-");
    flag = 0;
    for (i = 0; i < len1; i++)
    {   if(result[i]==0&&flag==0)
        {
            continue;
        }
        printf("%d", result[i]);
        flag = 1;
    }
    if(flag==0)
        printf("0");
    printf("\n");

    return 0;
}
