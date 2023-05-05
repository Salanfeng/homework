#include <stdio.h>

int main()
{
    char hashvalue[10010][130];
    long long hash[40001];
    FILE *hashfile;
    hashfile = fopen("hashvalue.txt", "r");
    int count = 0;
    while (count < 10000)
    {
        fscanf(hashfile, "%s", hashvalue[count]);
        count++;
    }

    fclose(hashfile);
    for (int i = 0; i < 10000; i++)
    {
        hash[i] = 0;
    }
    printf("1\n");
    for (int i = 0; i < 10000; i++)
    {
        for (int j = 63; j > -1; j--)
        {
            hash[2 * i] = hash[2 * i] << 1;
            hash[2 * i] = hash[2 * i] | (hashvalue[i][j] - '0');
        }
    }
    printf("2\n");
    for (int i = 0; i < 10000; i++)
    {
        for (int j = 127; j > 63; j--)
        {
            hash[2 * i + 1] = hash[2 * i + 1] << 1;
            hash[2 * i + 1] = hash[2 * i + 1] | (hashvalue[i][j] - '0');
        }
    }
    FILE *hashv;
    hashv = fopen("hashv.txt", "w");
    fprintf(hashv, "{");
    int i;
    for (i = 0; i < 20000; i++)
    {
        fprintf(hashv, "%lld,", hash[i]);
        if(i%100==0)fprintf(hashv,"\n");
    }
    printf("%d", i);

    fprintf(hashv, "}");
    fclose(hashv);
}