#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char stopwords[330][15];

int mainint argc,char* argv[])
{
    FILE *article, *stop, *hash, *sample;
    stop=fopen("stopwords.txt","r");
    //read the stopwords
    int i = 0;
    while(fscanf(stop,"%s",stopwords[i])!=EOF)
    {
        i++;
    }
    fclose(stop);    
    //read the article
    article=fopen("article.txt","r");


    return 0;
}
