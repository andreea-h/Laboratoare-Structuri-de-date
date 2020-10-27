#include <stdio.h>

typedef struct node 
{
    int val;
    struct node* left;
    struct node* right;
} node;


void printGivenLevel(struct node* root, int level);
int height(struct node* node);
void printTree(struct node* root);

void printTree(struct node* root)
{
    int h = height(root);
    int i;
    for (i=1; i<=h; i++)
    {	
	printf("nivel %d\n", i);
        printGivenLevel(root, i);
    }
    printf("\n");
}
 
/* Print nodes at a given level */
void printGivenLevel(struct node* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->val);
    else if (level > 1)
    {
        printGivenLevel(root->left, level-1);
        printGivenLevel(root->right, level-1);
    }
}
 
/* Compute the "height" of a tree -- the number of
    nodes along the longest path from the root node
    down to the farthest leaf node.*/
int height(struct node* node)
{
    if (node==NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);
 
        /* use the larger one */
        if (lheight > rheight)
            return(lheight+1);
        else return(rheight+1);
    }
}
