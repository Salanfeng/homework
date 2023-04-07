#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *article,*test;
    char name[50];
    article = fopen("article.txt", "r");
    test = fopen("test.txt", "w");
    fscanf(article, "%s", name);
    fprintf(test, "%s", name);
}
