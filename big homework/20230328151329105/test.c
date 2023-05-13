#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char stopwords[500][15];

int main(int argc, char *argv[])
{

    FILE *stop;
    stop = fopen("stopwords.txt", "r");
    int i = 0, Snum = 0;
    while (fscanf(stop, "%s", stopwords[i]) != EOF)
    {
        i++;
    }
    Snum = i;
    fclose(stop);
    FILE *test;
    test=fopen("test6.txt","w");
    for (int i = 0;i<Snum;i++)
    {
        fprintf(test,"\"%s\",",stopwords[i]);
    }
    fclose(test);
    return Snum;
}

