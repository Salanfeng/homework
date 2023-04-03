#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char filename[] = "example.c";
#define MAX 1024
int top = -1;
typedef struct
{
    int line;
    char cc;
} Data;


int main()
{
    Data stack[250];
    int i, line = 0,s=0;
    int flag = 0;
    char buffer[MAX];
    char save[MAX];
    FILE *fp;
    fp = fopen(filename, "r");
    while (fgets(buffer, MAX, fp) != NULL)
    {
        line++;
        i = 0;
        while (buffer[i] != '\0')
        {
            if (buffer[i] == '/' && buffer[i + 1] == '/')
            {
                break;
            }
            if (buffer[i] == '/' && buffer[i + 1] == '*')
            {
                flag = 1;
            }
            else if (buffer[i] == '*' && buffer[i + 1] == '/'&&flag==1)
            {
                flag = 0;
            }
            if (buffer[i] == '\"' && flag==0)
            {
                flag = 2;
            }
            else if (buffer[i] == '\"' && flag==2)
            {
                flag = 0;
            }
            if (buffer[i] == '\'' && flag==0)
            {
                flag = 3;
            }
            else if (buffer[i] == '\'' && flag==3)
            {
                flag = 0;
            }
            if (flag >0)
            {
                i++;
                continue;
            }
            if (buffer[i] == '{'||buffer[i] == '('||buffer[i] == ')'||buffer[i] == '}')
            {
                save[s++] = buffer[i];
                stack[++top].cc = buffer[i];
                stack[top].line = line;
            }
            i++;
        }
    }
    fclose(fp);
    save[s] = '\0';
    flag = 1;  
   while(flag==1)
    {
        flag=0;
        for (int i = 0; i <= top;i++)
        {
            if (stack[i].cc == '(')
            {
                if (stack[i + 1].cc == ')')
                {
                    for (int j = i; j < top;j++)
                    {
                        stack[j] = stack[j + 2];
                    }
                    top -= 2;
                    flag = 1;
                    break;
                }
            }
            if (stack[i].cc == '{')
            {
                if (stack[i + 1].cc == '}')
                {
                    for (int j = i; j < top;j++)
                    {
                        stack[j] = stack[j + 2];
                    }
                    top -= 2;
                    flag = 1;
                    break;
                }
            }
        }
    }
    if (top == -1)
    puts(save);
    else
    {
    printf("without maching '%c' at line %d\n", stack[top].cc, stack[top].line);
    }
    return 0;
}
