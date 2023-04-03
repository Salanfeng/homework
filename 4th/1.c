#include <stdio.h>
#include <stdlib.h>

int main()
{
    int stack[100], top = -1, i, n, choice, item;
    while (scanf("%d", &choice) != EOF)
    {
        switch (choice)
        {
        case 1:
            scanf("%d", &item);
            if (top == 99)
                printf("error");
            else
                stack[++top] = item;
            break;
        case 0:
            if (top == -1)
                printf("error ");
            else
            {
                printf("%d ", stack[top]);
                top--;
            }
            break;
        case -1:
            return 0;
        }
    }
}