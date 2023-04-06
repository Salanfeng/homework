#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char hashwords[500][15];

int main()
{
    FILE  *stop;
    stop=fopen("stopwords.txt","r");
    //read the stopwords with hash table
    int i = 0,sum=0;
    char temp[15];
    while(fscanf(stop,"%s",temp)!=EOF)
    {
        int j = 0;
        int hash = 0;
        while(temp[j]!='\0')
        {
            hash = hash + temp[j]*temp[j];
            j++;
        }
        hash = hash % 500;
        strcpy(hashwords[hash],temp);
        i++;
    }
    fclose(stop);
    int hsum = 0;
    for (int i = 0; i < 500; i++)
    {
        if(hashwords[i][0]!='\0')
        {
            hsum++;
        }
    }
    printf("%d", hsum);
    return 0;
}
