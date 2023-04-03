#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 1024
int len1, len2;
void strcopy(int place, char * buffer2, char *str2)
{
    int differ=len1-len2,len=strlen(buffer2);
    if(differ==0)
        ;
    else if (differ<0)
    for (int i = len, j = i - differ; i > place+len2-3;i--,j--)
        buffer2[j] = buffer2[i];
    else
    for (int i = place+len1, j = i - differ; i <=len ;i++)
        buffer2[j++] = buffer2[i];
    for (int i = 0; i < len2; i++)
        buffer2[i+place] = str2[i];
}

int main()
{
    char filename[] = "filein.txt";
    char outFilename[] = "fileout.txt";
    char str1[MAX], str2[MAX];
    char buffer[MAX], buffer2[MAX];
    char *p,*bp2;
    FILE *IN, *OUT;
    IN=fopen(filename,"r");
    OUT=fopen(outFilename,"w");


    gets(str1);
    gets(str2);
    len1 = strlen(str1);
    len2 = strlen(str2);
if((IN=fopen(filename,"r"))==NULL)

    {

       printf("Can&rsquo;t open in.txt!");

       return -1;

    }

    for (int i = 0; i < len1; i++)
        str1[i] = tolower(str1[i]);

    while (fgets(buffer, MAX, IN) != NULL)
    {
        for (int i = 0; i < strlen(buffer); i++)
        buffer2[i] = tolower(buffer[i]);
        bp2=buffer2;
        p = strstr(buffer2, str1);
        while (p != NULL)
        {
            strcopy(p-bp2, buffer2, str2);
            strcopy(p-bp2, buffer, str2);
            p = strstr(p + len2, str1);
        }
        fputs(buffer, OUT);
    }
    fclose(IN);
    fclose(OUT);
    return 0;
}