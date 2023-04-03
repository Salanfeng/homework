#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define maxn 100005
char s[maxn];
char ans[maxn];
int pnum;
int lineNum[maxn];
int sta[maxn];
int top;
int ban;
char fType[6];

int getType(char c)
{
	if (c == '(')
		return 2;
	if (c == ')')
		return 3;
	if (c == '{')
		return 4;
	if (c == '}')
		return 5;
	return 0;
}

void pre()
{
	fType[2] = '(';
	fType[3] = ')';
	fType[4] = '{';
	fType[5] = '}';
}

int tryPush(int x, int line)
{
	if (top && sta[top] < x)
	{
		printf("without maching \'%c\' at line %d\n", fType[sta[top]], lineNum[top]);
		return -1;
	}
	sta[++top] = x;
	lineNum[top] = line;
	return 0;
}

int tryPop(int x, int line)
{
	if (!top || (sta[top] ^ 1) != x)
	{
		printf("without maching \'%c\' at line %d\n", fType[x], line);
		return -1;
	}
	--top;
	return 0;
}

void changeBan(int *pos)
{
	if (!ban)
	{
		if (s[*pos] == '\"')
		{
			ban = 1;
			return;
		}
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
	}
	else
	{
		if (ban == 1 && s[*pos] == '\"')
		{
			ban = 0;
			return;
		}
		if (ban == 2 && s[*pos] == '\'')
		{
			ban = 0;
			return;
		}
		if (ban == 3 && s[*pos] == '*' && s[(*pos) + 1] == '/')
		{
			ban = 0;
			++(*pos);
			return;
		}
	}
}

int main()
{
	pre();
	FILE *IN = fopen("example.c", "r");
	int line = 0;
	while (fgets(s, maxn - 5, IN) != NULL)
	{
		++line;
		int len = strlen(s);
		int i;
		int temp;
		for (i = 0; i < len; ++i)
		{
			if (!ban && (temp = getType(s[i])))
			{
				if (temp & 1)
				{
					if (tryPop(temp, line) < 0)
					{
						return 0;
					}
				}
				else
				{
					if (tryPush(temp, line) < 0)
					{
						return 0;
					}
				}
				ans[++pnum] = s[i];
			}
			else
			{
				changeBan(&i);
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
		printf("without maching \'%c\' at line %d\n", fType[sta[top]], lineNum[top]);
	}
	else
	{
		for (i = 1; i <= pnum; ++i)
		{
			printf("%c", ans[i]);
		}
	}
	return 0;
}