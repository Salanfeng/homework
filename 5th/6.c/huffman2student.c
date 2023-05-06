// �ļ�ѹ��-Huffmanʵ��
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode
{ // Huffman���ṹ
	char c;
	int weight; // ���ڵ�Ȩ�أ�Ҷ�ڵ�Ϊ�ַ������ĳ��ִ���
	struct tnode *left, *right;
};
int Ccount[128] = {0};			  // ���ÿ���ַ��ĳ��ִ�������Ccount[i]��ʾASCIIֵΪi���ַ����ִ���
struct tnode *Root = NULL;		  // Huffman���ĸ��ڵ�
char HCode[128][MAXSIZE] = {{0}}; // �ַ���Huffman���룬��HCode['a']Ϊ�ַ�a��Huffman���루�ַ�����ʽ��
int Step = 0;					  // ʵ�鲽��
FILE *Src, *Obj;

void statCount();	// ����1��ͳ���ļ����ַ�Ƶ��
void createHTree(); // ����2������һ��Huffman�������ڵ�ΪRoot
void makeHCode();	// ����3������Huffman������Huffman����
void atoHZIP();		// ����4������Huffman���뽫ָ��ASCII���ı��ļ�ת����Huffman���ļ�
void visitHTree(int, char *, struct tnode *);

void print1();				  // �������1�Ľ��
void print2(struct tnode *p); // �������2�Ľ��
void print3();				  // �������3�Ľ��
void print4();				  // �������4�Ľ��

int main()
{
	if ((Src = fopen("input.txt", "r")) == NULL)
	{
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if ((Obj = fopen("output.txt", "w")) == NULL)
	{
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d", &Step); // ���뵱ǰʵ�鲽��

	statCount();						   // ʵ�鲽��1��ͳ���ļ����ַ����ִ�����Ƶ�ʣ�
	(Step == 1) ? print1() : 1;			   // ���ʵ�鲽��1���
	createHTree();						   // ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
	(Step == 2) ? print2(Root) : 2;		   // ���ʵ�鲽��2���
	makeHCode();						   // ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
	(Step == 3) ? print3() : 3;			   // ���ʵ�鲽��3���
	(Step >= 4) ? atoHZIP(), print4() : 4; // ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��4���

	fclose(Src);
	fclose(Obj);

	return 0;
}

// ��ʵ�鲽��1����ʼ

void statCount()
{
	char ch;
	while (fscanf(Src, "%c", &ch) != EOF)
	{
		Ccount[ch]++;
	}
	Ccount[0]++;
	Ccount[10] = 0;
}

// ��ʵ�鲽��1������

// ��ʵ�鲽��2����ʼ

void createHTree()
{
	struct tnode *F[256], *p, *t0, *t1;
	int front = 0, rear = 0;
	for (int i = 0; i < 128; i++)
		if (Ccount[i] > 0)
		{
			p = (struct tnode *)malloc(sizeof(struct tnode));
			p->c = i;
			p->weight = Ccount[i];
			p->left = p->right = NULL;
			F[rear++] = p;
		}
	// Bubble sort
	for (int i = 0; i < rear - 1; i++)
		for (int j = 0; j < rear - 1 - i; j++)
			if (F[j]->weight > F[j + 1]->weight || (F[j]->weight == F[j + 1]->weight && F[j]->c > F[j + 1]->c))
			{
				p = F[j];
				F[j] = F[j + 1];
				F[j + 1] = p;
			}
	while (rear - front > 1)
	{
		int j;
		p = NULL;
		p = (struct tnode *)malloc(sizeof(struct tnode));
		t0 = F[front++];
		t1 = F[front++];
		p->left = t0;
		p->right = t1;
		p->weight = t0->weight + t1->weight;
		for (j = front; j < rear; j++)
			if (p->weight < F[j]->weight)
			{
				for (int k = rear; k > j; k--)
					F[k] = F[k - 1];
				break;
			}
		F[j] = p;
		rear++;
	}
	Root = F[front];
}

// ��ʵ�鲽��2������

// ��ʵ�鲽��3����ʼ

void makeHCode()
{
	char str[30];
	visitHTree(0, str, Root);
}

// ��ʵ�鲽��3������

// ��ʵ�鲽��4����ʼ
void visitHTree(int count, char *str, struct tnode *p)
{
	if (p->left == NULL && p->right == NULL)
	{
		str[count] = '\0';
		strcpy(HCode[p->c], str);
	}
	else
	{
		str[count] = '0';
		visitHTree(count + 1, str, p->left);
		str[count] = '1';
		visitHTree(count + 1, str, p->right);
	}
}

void atoHZIP()
{
	fclose(Src);
	Src = fopen("input.txt", "r");
	char ch;
	unsigned char hc;
	char buffer[128];
	int i = 0, j = 0;
	while (fscanf(Src, "%c", &ch) != EOF)
	{
		strcpy(buffer, HCode[ch]);
		for (j = 0; buffer[j] != '\0'; j++)
		{
			hc = (hc << 1) | (buffer[j] - '0');
			i++;
			if (i % 8 == 0)
			{
				fputc(hc, Obj);
				printf("%x", hc);
				i = 0;
			}
		}
	}
	strcpy(buffer, HCode[0]);
	for (j = 0; buffer[j] != '\0'; j++)
	{
		hc = (hc << 1) | (buffer[j] - '0');
		i++;
		if (i % 8 == 0)
		{
			fputc(hc, Obj);
			printf("%x", hc);
			i = 0;
		}
	}
	if (i != 0)
	{
		while (i < 8)
		{
			hc = hc << 1;
			i++;
		}
		fputc(hc, Obj);
		printf("%x", hc);
	}
}

// ��ʵ�鲽��4������

void print1()
{
	int i;
	printf("NUL:1\n");
	for (i = 1; i < 128; i++)
		if (Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if (p != NULL)
	{
		if ((p->left == NULL) && (p->right == NULL))
			switch (p->c)
			{
			case 0:
				printf("NUL ");
				break;
			case ' ':
				printf("SP ");
				break;
			case '\t':
				printf("TAB ");
				break;
			case '\n':
				printf("CR ");
				break;
			default:
				printf("%c ", p->c);
				break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;

	for (i = 0; i < 128; i++)
	{
		if (HCode[i][0] != 0)
		{
			switch (i)
			{
			case 0:
				printf("NUL:");
				break;
			case ' ':
				printf("SP:");
				break;
			case '\t':
				printf("TAB:");
				break;
			case '\n':
				printf("CR:");
				break;
			default:
				printf("%c:", i);
				break;
			}
			printf("%s\n", HCode[i]);
		}
	}
}

void print4()
{
	long int in_size, out_size;

	fseek(Src, 0, SEEK_END);
	fseek(Obj, 0, SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);

	printf("\nԭ�ļ���С��%ldB\n", in_size);
	printf("ѹ�����ļ���С��%ldB\n", out_size);
	printf("ѹ���ʣ�%.2f%%\n", (float)(in_size - out_size) * 100 / in_size);
}
