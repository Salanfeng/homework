#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    char number[10];
    char name[20];
    int seat;
};
struct Student stu[108];
int Seat[1145] = {0};
int MaxSeat = 0;
int Compare(const void *a, const void *b)
{
    struct Student *c = (struct Student *)a;
    struct Student *d = (struct Student *)b;
    if (c->seat > d->seat)
    {
        return 1;
    }
    else if (c->seat < d->seat)
    {
        return -1;
    }
    else
    {
        return strcmp(c->number, d->number);
    }
}
int cmp(const void *a, const void *b)
{
    struct Student *c = (struct Student *)a;
    struct Student *d = (struct Student *)b;
    return strcmp(c->number, d->number);
}

void ReadData(int Num)
{
    FILE *fp = fopen("in.txt", "r");
    int i = 0;
    for (i = 0; i < Num; i++)
    {
        fscanf(fp, "%s %s %d", stu[i].number, stu[i].name, &stu[i].seat);
        Seat[stu[i].seat] = 1;
        if (stu[i].seat > MaxSeat)
        {
            MaxSeat = stu[i].seat;
        }
    }
    qsort(stu, Num, sizeof(stu[0]), Compare);

    fclose(fp);
}
int main()
{
    int Num = 0;
    scanf("%d", &Num);
    ReadData(Num);
    int last = Num - 1;
    if (MaxSeat > Num)
        MaxSeat = Num;
    for (int i = 1; i < MaxSeat; i++)
    {
        if (Seat[i] == 0 && stu[last].seat > i)
        {
            stu[last].seat = i;
            last--;
        }
    }

    MaxSeat = stu[last].seat;
    for (int i = 1; i < MaxSeat; i++)
    {
        Seat[i] = 0;
    }
    for (int i = 0; i < last; i++)
    {
        if (Seat[stu[i].seat] == 0)
        {
            Seat[stu[i].seat] = 1;
        }
        else
        {
            MaxSeat++;
            stu[i].seat = MaxSeat;
        }
    }

    qsort(stu, Num, sizeof(stu[0]), cmp);
    FILE *fp = fopen("out.txt", "w");
    for (int i = 0; i < Num; i++)
    {
        fprintf(fp, "%s %s %d\n", stu[i].number, stu[i].name, stu[i].seat);
    }
    fclose(fp);
}