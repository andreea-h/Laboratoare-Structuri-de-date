#include <stdio.h>
#include <stdlib.h>

typedef struct node  
{ 
  int key; 
  struct node *left; 
  struct node *right; 
} node;

node* newNode(int data) 
{ 
  struct node* node = (struct node*)malloc(sizeof(struct node)); 
  
  node->key = data; 

  node->left = NULL; 
  node->right = NULL; 
  return(node); 
} 

void inorder(struct node *root) 
{ 
    if (root != NULL) 
    { 
        inorder(root->left); 
        printf("%d \n", root->key); 
        inorder(root->right); 
    } 
} 
   
node* insert(node* node, int key) 
{ 
    if (node == NULL) return newNode(key); 
  
    if (key < node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key);    
  
    return node; 
} 

// calculeaza diametru - 1.5P
/*
	HINT: diametrul e maximul dintre:
	- diametrul subarborelui stang
	- diametrul subarborelui drept
	- cel mai lung drum dintre frunze care trece prin radacina(acesta poate fi calculat folosind inaltimile subaroborilor)
*/

int height(node *root)
{
	if(root==NULL)
		return 0;
	else
		return 1+height(root->left)+height(root->right);
}

int maxim(int a,int b)
{
	if(a>=b)
		return a;
	return b;
}

int diameter(node *root)
{
	if(root==NULL)
		return 0;
	int st=height(root->left); 
  	int dr=height(root->right); 
  	int st_diam=diameter(root->left); 
  	int dr_diam=diameter(root->right); 
  	return maxim(1+st_diam+dr_diam,maxim(st,dr));
	return 0;
}

// Avand dat un arbore, sa se implementeze o functie care sa afiseze toate modurile in care se poate ajunge
// (pornind de la radacina si mergand spre frunze) prin insumarea valorilor nodurilor parcuse pe acea cale la o anumita valoare. - 1.5 P
/* puteti modifica antetul functiei */
void paths(node *tree, int sum) 
{
	
}


   

int main() 
{ 
    struct node *root = NULL; 
    root = insert(root, 50); 
    insert(root, 30); 
    insert(root, 75); 
    insert(root, 63); 
    insert(root, 23); 
    insert(root, 22); 
    insert(root, 24); 
    insert(root, 57); 
    insert(root, 77);
    insert(root, 27);
   
    inorder(root); 
    printf("Diametrul este %d \n", diameter(root));
   // printf("Rutele pana la 125 \n");
   // paths(root, 125);
    return 0; 
} 

