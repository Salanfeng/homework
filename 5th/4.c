#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void ReadGate();
struct TreeNode
{
    int n;
    struct TreeNode *cross;
    struct TreeNode *left;
    struct TreeNode *right;
};
struct TreeNode *root = NULL;
struct TreeNode *Search(struct TreeNode *, int);

struct Gate
{
    int n;
    int count;
};
void SortGate(struct Gate *);
void LevelTraversal(struct TreeNode *, struct Gate *);
int cmp(const void *a, const void *b)
{
    int x = ((struct Gate *)b)->count - ((struct Gate *)a)->count;
    if (x > 0)
        return 1;
    else if (x < 0)
        return -1;
    else
        return ((struct Gate *)a)->n - ((struct Gate *)b)->n;
}

void ReadGate()
{
    int r, s[5], top = -1;
    struct TreeNode *p;
    scanf("%d", &r);
    while (r != -1)
    {
        scanf("%d", &s[++top]);
        while (s[top] != -1)
        {
            scanf("%d", &s[++top]);
        }
        p = Search(root, r);
        p->n = r;
        for (int i = 0; i < top; i++)
            if (s[i] >= 0)
            {
                if (p->left == NULL)
                {
                    p->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                    p->left->n = s[i];
                    p->left->left = NULL;
                    p->left->right = NULL;
                    p->left->cross = NULL;
                    s[i] = -1;
                    break;
                }
            }
        for (int i = 0; i < top; i++)
            if (s[i] >= 100)
            {
                p->cross = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                p->cross->n = s[i];
                p->cross->left = NULL;
                p->cross->right = NULL;
                p->cross->cross = NULL;
                s[i] = -1;
                break;
            }
        for (int i = 0; i < top; i++)
            if (s[i] >= 0)
            {
                if (p->cross == NULL)
                {
                    p->cross = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                    p->cross->n = s[i];
                    p->cross->left = NULL;
                    p->cross->right = NULL;
                    p->cross->cross = NULL;
                    s[i] = -1;
                    break;
                }
            }
        for (int i = 0; i < top; i++)
            if (s[i] >= 0)
            {
                if (p->right == NULL)
                {
                    p->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                    p->right->n = s[i];
                    p->right->left = NULL;
                    p->right->right = NULL;
                    p->right->cross = NULL;
                    s[i] = -1;
                    break;
                }
            }
        scanf("%d", &r);
        top = -1;
    }
    return;
}

struct TreeNode *Search(struct TreeNode *q, int r)
{
    if (root == NULL)
    {
        root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        root->left = NULL;
        root->right = NULL;
        root->cross = NULL;
        return root;
    }
    else
    {
        struct TreeNode *ans;
        if (q != NULL)
        {
            if (q->n == r)
            {
                return q;
            }
            if (q->cross != NULL)
            {
                ans = Search(q->cross, r);
                if (ans)
                    return ans;
            }
            if (q->left != NULL && q->left->n >= 100)
            {
                ans = Search(q->left, r);
                if (ans)
                    return ans;
            }
            if (q->right != NULL && q->right->n >= 100)
            {
                ans = Search(q->right, r);
                if (ans)
                    return ans;
            }
        }
        return NULL;
    }
}
void SortGate(struct Gate *gate)
{
    int count = 0;
    while (scanf("%d", &gate[count].n) != EOF)
    {
        scanf("%d", &gate[count].count);
        count++;
    }
    qsort(gate, count, sizeof(struct Gate), cmp);
    return;
}

void LevelTraversal(struct TreeNode *q, struct Gate *gate)
{
    struct TreeNode *queue[1000];
    int front = 0, rear = 0;
    int count = 0;
    if (q != NULL)
    {
        queue[rear++] = q;
        while (front != rear)
        {
            q = queue[front++];
            if (q->left != NULL)
            {
                if (q->left->n >= 100)
                    queue[rear++] = q->left;
                else
                    printf("%d->%d\n", gate[count++].n, q->left->n);
            }
            if (q->cross != NULL)
            {
                if (q->cross->n >= 100)
                    queue[rear++] = q->cross;
                else
                    printf("%d->%d\n", gate[count++].n, q->cross->n);
            }
            if (q->right != NULL)
            {
                if (q->right->n >= 100)
                    queue[rear++] = q->right;
                else
                    printf("%d->%d\n", gate[count++].n, q->right->n);
            }
        }
    }
}
int main()
{
    ReadGate();
    struct Gate *gate = (struct Gate *)malloc(sizeof(struct Gate) * 105);
    SortGate(gate);
    LevelTraversal(root, gate);
    return 0;
}
