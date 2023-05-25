#include<stdio.h>
#include<string.h>
int main()
{
    char word[100];
    scanf("%s", word);
    strlen(word);
    printf("%d\n", strlen(word));
    printf("%c", word[0]);
    printf("%c", word[1]);
    printf("%c", word[2]);
    printf("%c", word[3]);
    return 0;
}