#include <stdio.h>
#include <string.h>
int main()
{
    int m = 0, n = 0, flag = 0;
    char in[666], ignore[55];
    gets(in);
    int i = 0, k = 0;
    while (in[i] < '0' || in[i] > '9')
    {
        if (in[i] == '-')
            flag = 1;
        ignore[k++] = in[i];
        i++;
    }
    while (in[i] >= '0' && in[i] <= '9')
    {
        m = m * 10 + (in[i] - '0');
        i++;
    }
    i++;
    while (in[i] >= '0' && in[i] <= '9')
    {
        n = n * 10 + (in[i] - '0');
        i++;
    }
    char ans[666];
    gets(ans);
    int len = strlen(ans);
    if (m < len)
        ans[m] = '\0';
    len = strlen(ans);
    if (n > len)
    {
        if (!flag)
        {
            int i = 0;
            while (ans[i] != '\0')
                printf("%c", ans[i++]);
            for (int j = 0; j < n - len; j++)
                printf("#");
        }
        else
        {
            for (int j = 0; j < n - len; j++)
                printf("#");
            int i = 0;
            while (ans[i] != '\0')
                printf("%c", ans[i++]);
        }
    }
    else
    {
        
            int i = 0;
            while (ans[i] != '\0')
                printf("%c", ans[i++]);
        
    }
    return 0;
}
