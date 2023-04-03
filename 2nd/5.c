#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 200
typedef struct
{
    char *bookname;
    char *author;
    char *press;
    int date;
    int del;
} Library;

int compare(const void *p1, const void *p2)
{
    const Library *book1 = (const Library *)p1;
    const Library *book2 = (const Library *)p2;
    return strcmp(book1->bookname, book2->bookname);
}

int main()
{
    char filename[] = "books.txt";
    char outFilename[] = "ordered.txt";
    char buffer[MAX];
    int number = 0;
    FILE *fp, *fc;
    fp = fopen(filename, "r");
    fc = fopen(outFilename, "w+");
    Library *L = (Library *)malloc(505 * sizeof(Library));
    while (fgets(buffer, MAX, fp) != NULL)
    {
        Library Book;
        int n;
        char a[55], b[22], c[33];
        sscanf(buffer, "%s %s %s %d", a, b, c, &n);
        Book.date = n;
        Book.bookname = strdup(a);
        Book.author = strdup(b);
        Book.press = strdup(c);
        Book.del = 0;
        L[number] = Book;
        number++;
    }
    qsort(L, number, sizeof(Library), compare);

    int op;
    scanf("%d", &op);
    while (op != 0)
    {
        char option[200];
        gets(option);
        gets(option);
        if (op == 1)
        {
            Library Book;
            int n;
            char a[55], b[22], c[33];
            sscanf(option, "%s %s %s %d", a, b, c, &n);
            Book.date = n;
            Book.bookname = strdup(a);
            Book.author = strdup(b);
            Book.press = strdup(c);
            Book.del = 0;
            L[number] = Book;
            number++;
            qsort(L, number, sizeof(Library), compare);
        }
        else if (op == 2)
        {
            int i;
            for (i = 0; i < number; i++)
            {
                if (strstr(L[i].bookname, option) != NULL)
                {
                    if (L[i].del == 0)
                        printf("%s %s %s %d\n", L[i].bookname, L[i].author, L[i].press, L[i].date);
                }
            }
        }
        else if (op == 3)
        {
            int i;
            for (i = 0; i < number; i++)
            {
                if (strstr(L[i].bookname, option) != NULL)
                {
                    L[i].del = 1;
                }
            }
        }
        scanf("%d", &op);
    }
    qsort(L, number, sizeof(Library), compare);
    for (int i = 0; i < number; i++)
    {
        if (L[i].del == 0)
        {
            fprintf(fc, "%-49s %-19s %-29s %-9d\n", L[i].bookname, L[i].author, L[i].press, L[i].date);
        }
    }

    return 0;
}
