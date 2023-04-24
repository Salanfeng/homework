#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};





int LRD(struct TreeNode *root,int depth)
{
    if(root == NULL) return 1;
    int l, r;
    l=LRD(root->left, depth + 1);
    r=LRD(root->right, depth + 1);
    if(r&&l)
    {
        printf("%d %d\n", root->val,depth);
    }
    return 0;
}


int main()
{
    int N,num;
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    struct TreeNode *p=root;
    scanf("%d", &N);
    scanf("%d", &num);
    root->val = num;
    root->left = NULL;
    root->right = NULL;
    N--;
    while(N--)
    {
        scanf("%d", &num);
        p=root;
        while(1)
        {
            if(num < p->val)
            {
                if(p->left == NULL)
                {
                    p->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                    p->left->val = num;
                    p->left->left = NULL;
                    p->left->right = NULL;
                    break;
                }
                else
                {
                    p = p->left;
                }
            }
            else
            {
                if(p->right == NULL)
                {
                    p->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                    p->right->val = num;
                    p->right->left = NULL;
                    p->right->right = NULL;
                    break;
                }
                else
                {
                    p = p->right;
                }
            }
        }
    }
    LRD(root,1);

    return 0;
}