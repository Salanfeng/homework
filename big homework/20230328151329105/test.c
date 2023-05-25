#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char stopwords[500][15];

int main(int argc, char *argv[])
{
    FILE *article, *test;
    article = fopen("article.txt", "r");
    test = fopen("test.txt", "w");
    char buffer[1024];
    int bufferlen = 0;
    char word[90];
    char c;
    int len;
    len = fread(buffer, 1, 1024, article);
    while (len > 0)
    {
        for (int bu = 0; bu < len; bu++)
        {
            c = buffer[bu];
            //printf("%c", c);
            if(c==12)
            {
                printf("%s",buffer);
                fseek(article, bu-len-1, SEEK_CUR);
                c=fgetc(article);
                printf("%c\n", c);
                len = fread(buffer, 1, 1024, article);
                bu = -1;
            }
            
        }
        len = fread(buffer, 1, 1024, article);
    }
    fclose(article);
}
