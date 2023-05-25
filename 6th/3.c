#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int Num = 0;
int adjust(int[], int, int);
int merge(int[], int[], int, int, int);
void SelectSort(int *a)
{
    int count = 0;
    for (int i = 0; i < Num; i++)
    {
        int min = i;
        for (int j = i + 1; j < Num; j++)
        {
            count++;
            if (a[j] < a[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            int temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
    for (int i = 0; i < Num; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n%d", count);
}

void BubbleSort(int *a)
{
    int count = 0;
    for (int i = 0; i < Num; i++)
    {
        int flag = 0;
        for (int j = 0; j < Num - i - 1; j++)
        {
            count++;
            if (a[j] > a[j + 1])
            {
                flag = 1;
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
        if (flag == 0)
        {
            break;
        }
    }
    for (int i = 0; i < Num; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n%d", count);
}
void HeapSort(int *a)
{
    int count = 0, s = 0;
    for (int i = Num / 2 - 1; i >= 0; i--)
    {
        s = adjust(a, i, Num);
        count += s;
    }
    for (int i = Num - 1; i > 0; i--)
    {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        s = adjust(a, 0, i);
        count += s;
    }
    for (int i = 0; i < Num; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n%d", count);
}

int adjust(int k[], int i, int n)
{
    int j, temp, count = 0;
    temp = k[i];
    j = 2 * i + 1;
    while (j < n)
    {
        if (j < n - 1 && k[j] < k[j + 1])
            j++;
        count++;
        if (temp >= k[j])
            break;
        k[(j - 1) / 2] = k[j];
        j = 2 * j + 1;
    }
    k[(j - 1) / 2] = temp;
    return count;
}
int MergeSort(int *a, int low, int high)
{
    int tmp[108];
    int s = 0;
    int count = 0;
    int mid = (low + high) / 2;
    if (high - low > 0)
    {
        s = MergeSort(a, low, mid);
        count += s;
        s = MergeSort(a, mid + 1, high);
        count += s;
        s = merge(a, tmp, low, mid, high);
        count += s;
        if (high - low == Num - 1)
        {
            for (int i = 0; i < Num; i++)
            {
                printf("%d ", a[i]);
            }
            printf("\n%d\n", count);
            return 0;
        }
        else
        {
            return count;
        }
    }
    return 0;
}
int merge(int x[], int tmp[], int left, int leftend, int rightend)
{
    int i = left, j = leftend + 1, q = left;
    int count = 0;
    while (i <= leftend && j <= rightend)
    {
        count++;
        if (x[i] <= x[j])
            tmp[q++] = x[i++];
        else
            tmp[q++] = x[j++];
    }
    while (i <= leftend)
        tmp[q++] = x[i++];
    while (j <= rightend)
        tmp[q++] = x[j++];
    for (i = left; i <= rightend; i++)
        x[i] = tmp[i];
    return count;
}
int QuickSort(int k[], int left, int right)
{
    int i, last, count = 0,s;
    if (left < right)
    {
        last = left;
        for (i = left + 1; i <= right; i++)
        {
            count++;
            if (k[i] < k[left])
            {
                last++;
                int temp = k[last];
                k[last] = k[i];
                k[i] = temp;
            }
        }
        int temp = k[left];
        k[left] = k[last];
        k[last] = temp;
        s=QuickSort(k, left, last - 1);
        count+=s;
        s=QuickSort(k, last + 1, right);
        count+=s;
    }
    if(right - left == Num - 1)
    {
    for (int i = 0; i < Num; i++)
    {
        printf("%d ", k[i]);
    }
    printf("\n%d", count);
    return 0;
    }
    else
    {
        return count;
    }
}

int main()
{
    int flag = 0;
    int a[108];
    scanf("%d %d", &Num, &flag);
    for (int i = 0; i < Num; i++)
    {
        scanf("%d", &a[i]);
    }
    switch (flag)
    {
    case 1:
        SelectSort(a);
        break;
    case 2:
        BubbleSort(a);
        break;
    case 3:
        HeapSort(a);
        break;
    case 4:
        MergeSort(a, 0, Num - 1);
        break;
    case 5:
        QuickSort(a, 0, Num - 1);
        break;
    default:
        break;
    }

    return 0;
}
