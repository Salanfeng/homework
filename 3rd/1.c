#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int x;
    int y;
    struct node *next;
    struct node *prev;
} *Point;

int main()
{
    int n, d = 0,count=0,max=0,start=0;
    scanf("%d", &n);
    Point xy = (Point)malloc(2 * n * sizeof(struct node));
    for (int i = 0; i < 2 * n - d; i += 2)
    {
        int fx, fy, lx, ly, fs = -1, ls = -1, first=0, last=0;
        scanf("%d %d %d %d", &fx, &fy, &lx, &ly);
        for (int j = 0; j < i; j ++)
        {
            if (fx == xy[j].x && fy == xy[j].y)
            {
                first = 1;
                fs = j;
            }
            if (lx == xy[j].x && ly == xy[j].y)
            {
                last = 1;
                ls = j;
            }
        }
        if (first + last == 0)
        {
            xy[i].x = fx;
            xy[i].y = fy;
            xy[i].next = &xy[i + 1];
            xy[i].prev = NULL;
            xy[i + 1].x = lx;
            xy[i + 1].y = ly;
            xy[i + 1].next = NULL;
            xy[i + 1].prev = &xy[i];
        }
        else if (first + last == 1)
        {
            if (first == 1)
            {
                xy[i].x = lx;
                xy[i].y = ly;
                xy[i].next = NULL;
                xy[i].prev = &xy[fs];
                xy[fs].next = &xy[i];
                i--;
                d++;
            }
            else
            {
                xy[i].x = fx;
                xy[i].y = fy;
                xy[i].next = &xy[ls];
                xy[i].prev = NULL;
                xy[ls].prev = &xy[i];
                i--;
                d++;
            }
        }
        else
        {
            xy[fs].next = &xy[ls];
            xy[ls].prev = &xy[fs];
            i -= 2;
            d += 2;
        }
    }
        for (int i = 0; i < 2 * n - d; i++)
        {
            Point p = xy[i].next;
            while (p != NULL)
            {
                count++;
                p = p->next;
            }
            if (count > max)
            {
                max = count;
                start = i;
            }
            count = 0;
        }
    printf("%d %d %d",max,xy[start].x,xy[start].y);
    free(xy);
    return 0;
}
