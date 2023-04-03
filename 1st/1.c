#include <stdio.h>
int main()
{
    char str[1000];
    scanf("%s", str);
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '-' && i > 0)
        {
            char last = str[i - 1];
            char next = str[i + 1];
            if ((last >= 'a' && last <= 'z' && next >= 'a' && next <= 'z' && next > last) ||
                (last >= 'A' && last <= 'Z' && next >= 'A' && next <= 'Z' && next > last) ||
                (last >= '0' && last <= '9' && next >= '0' && next <= '9' && next > last))
            {
                for (char c = last + 1; c < next; c++)
                {
                    printf("%c", c);
                }
            }
            else
            {
                printf("%c", str[i]);
            }
        }
        else
        {
            printf("%c", str[i]);
        }
        i++;
    }

    return 0;
}
