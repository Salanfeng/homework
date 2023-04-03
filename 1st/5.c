#include<stdio.h>
int a[11]={0},ok;
void print(int ,int);

int main() 
{
	int n;
	scanf("%d", &n);
	print(n, 0);
	return 0;
}

void print(int n, int num) 
{
	if (num == n) 
	{
		for (int i = 0; i < n; i++) 
		printf("%d ", a[i]);
		printf("\n");
	}
	else 
	{
		for (int i = 1; i <= n; i++) 
		{
			ok = 1;
			for (int j = 0; j < num; j++) 
			{
				if (i == a[j])
				ok = 0;
			}
			if (ok) 
			{
				a[num] = i;
				print(n, num + 1);
			}
		}
	}
}