#include <stdio.h>
#define MAX 19
int isWin(int **chess, int who, int *x, int *y)
{
    int i, j, flag = 0;
    for (i = 0; i < MAX; i++)
    {
        for (j = 0; j < MAX; j++)
        {
            if (chess[i][j] == who)
            {
                flag = 0;
                for (int k = 1; k < 4; k++)
                {
                    if (chess[i][j + k] != who)
                    {
                        break;
                    }
                    if (k == 3 && chess[i][j + k + 1] == 0)
                        flag = 1;
                }
                for (int k = 1; k < 4; k++)
                {
                    if (chess[i + k][j] != who)
                    {
                        break;
                    }
                    if (k == 3 && chess[i + k + 1][j] == 0)
                        flag = 1;
                }
                for (int k = 1; k < 4; k++)
                {
                    if (chess[i + k][j + k] != who)
                    {
                        break;
                    }
                    if (k == 3 && chess[i + k + 1][j + k + 1] == 0)
                        flag = 1;
                }
                for (int k = 1; k < 4 && j - k - 1 >= 0; k++)
                {
                    if (chess[i + k][j - k] != who)
                    {
                        break;
                    }
                    if (k == 3 && chess[i + k + 1][j - k - 1] == 0)
                        flag = 1;
                }
            }
            if (flag)
            {
                *x = i;
                *y = j;
                return flag;
            }
        }
    }
    return flag;
}
int main()
{
    int chess[25][25] = {0}, x, y;
    int *pchess[25], *px = &x, *py = &y;
    for (int i = 0; i < 25; i++)
    {
        pchess[i] = chess[i];
    }
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            scanf(" %d", &chess[i][j]);
        }
    }
    /*    for (int i = 0; i < MAX; i++)
        {
            for (int j = 0; j < MAX; j++)
            {
                printf(" %d", chess[i][j]);
            }
            printf("\n");
        }*/
    if (isWin(pchess, 1, px, py))
    {
        printf("1:%d,%d\n", x + 1, y + 1);
    }
    else if (isWin(pchess, 2, px, py))
    {
        printf("2:%d,%d\n", x + 1, y + 1);
    }
    else
    {
        printf("No\n");
    }

    return 0;
}