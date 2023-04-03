#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 1024

int main()
{
    char filename[] = "encrypt.txt";
    char outFilename[] = "output.txt";
    char str1[MAX];
    char buffer[MAX];
    char *p;
    int len1, pass[26] = {0}, flag[26] = {0};
    FILE *IN, *OUT;
    IN = fopen(filename, "r");
    OUT = fopen(outFilename, "w");
    gets(str1);
    len1 = strlen(str1);
    if ((IN = fopen(filename, "r")) == NULL)
    {
        printf("Can&rsquo;t open in.txt!");
        return -1;
    }
    for (int i = 0; i < 26; i++)
        flag[i] = 1;

    int d = 0;

    for (int i = 0; i < len1; i++)
    {
        pass[i-d] = str1[i] - 'a';
        for (int j = 0; j < i-d; j++)
        {
            if (pass[i-d] == pass[j])
                d++;
        }
        flag[pass[i-d]] = 0;
    }
    len1 -= d;
    for (int i = 25; i >= 0; i--)
    {
        if (flag[i] == 1)
            pass[len1++] = i;
    }
    while (fgets(buffer, MAX, IN) != NULL)
    {
        for (int i = 0; i < strlen(buffer); i++)
            if (islower(buffer[i]))
                buffer[i] = 'a' + pass[buffer[i] - 'a'];
        fputs(buffer, OUT);
    }
    fclose(IN);
    fclose(OUT);
    return 0;
}