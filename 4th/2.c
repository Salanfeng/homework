#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char s[10000];
char s2[10000];
int s3[10000];
int s4[10000];
int p, ban, top;
char save[6];

int change(char c)
{
	if (c == '{')
		return 4;
	if (c == '}')
		return 5;
	if (c == '(')
		return 2;
	if (c == ')')
		return 3;

	return 0;
}

int Push(int x, int line)
{
	if (top && s4[top] < x)
	{
		printf("without maching \'%c\' at line %d\n", save[s4[top]], s3[top]);
		return -1;
	}
	s4[++top] = x;
	s3[top] = line;
	return 0;
}

int Pop(int x, int line)
{
	if (!top || (s4[top] ^ 1) != x)
	{
		printf("without maching \'%c\' at line %d\n", save[x], line);
		return -1;
	}
	--top;
	return 0;
}

void Ban(int *pos)
{
	if (!ban)
	{
		if (s[*pos] == '\'')
		{
			ban = 2;
			return;
		}
		if (s[*pos] == '/' && s[(*pos) + 1] == '*')
		{
			ban = 3;
			++(*pos);
			return;
		}
		if (s[*pos] == '/' && s[(*pos) + 1] == '/')
		{
			ban = 4;
			++(*pos);
			return;
		}
		if (s[*pos] == '\"')
		{
			ban = 1;
			return;
		}
	}
	else
	{
		if (ban == 1 && s[*pos] == '\"')
		{
			ban = 0;
			return;
		}
		else if (ban == 2 && s[*pos] == '\'')
		{
			ban = 0;
			return;
		}
		else if (ban == 3 && s[*pos] == '*' && s[(*pos) + 1] == '/')
		{
			ban = 0;
			++(*pos);
			return;
		}
	}
}

int main()
{
	save[2] = '(';
	save[3] = ')';
	save[4] = '{';
	save[5] = '}';
	int line = 0;
	FILE *fp = fopen("example.c", "r");
	while (fgets(s, 9999, fp) != NULL)
	{
		line++;
		int i;
		int c;
		int len = strlen(s);
		for (i = 0; i < len; ++i)
		{
			if (ban || !(c = change(s[i])))
			{
				Ban(&i);
						}
			else
			{
				if (!(1 & c))
				{
					if (Push(c, line) < 0)
					{
						return 0;
					}
				}
				else
				{
					if (Pop(c, line) < 0)
					{
						return 0;
					}
				}
				s2[++p] = s[i];
			}
		}
		if (ban == 4)
		{
			ban = 0;
		}
	}
	int i;
	if (top)
	{
		printf("without maching \'%c\' at line %d\n", save[s4[top]], s3[top]);
	}
	else
	{
		for (i = 1; i <= p; ++i)
		{
			printf("%c", s2[i]);
		}
	}
	return 0;
}