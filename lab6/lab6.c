#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lab6helper.h"

node *createNode(int key)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->val = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/* functia insereaza un node in arbore 
   puteti apela functia createNode care returneaza un struct node
   alocat */

// ex1 - 1p
/* functia insereaza un nod in arbore */
void addnode(node** tree, int val)
{
	if(*tree==NULL)
		*tree=createNode(val);
	else if((*tree)->val>val)
			addnode(&(*tree)->left,val);
	else if((*tree)->val<val)
		addnode(&(*tree)->right,val);
}

/* cautati o valoare v intr-un arbore binar de cautare, se va intoarce 
	nodul daca exista un nod cu valoarea cautata,
	NULL daca nu exista */
// ex2 - 1p
node* search(node *tree, int val)
{
	if(tree==NULL || tree->val==val)
		return tree;
	if(tree->val<val)
		return search(tree->right,val);
	else if(tree->val>val)
		return search(tree->left,val);
}


/* parcurgerea în preordine a arborelui creat, cu afișarea valorilor din noduri*/
// ex3.1 - 0.5p
void preorder(node* tree) //rsd
{
	if(tree==NULL)
		return;
	printf("%d ",tree->val);
	preorder(tree->left);
	preorder(tree->right);
}

/* parcurgerea în inordine a arborelui creat, cu afișarea valorilor din noduri*/
// ex3.2 - 0.5p
void inorder(node* tree) //srd
{
    if(tree==NULL)
		return;
	inorder(tree->left);
	printf("%d ",tree->val);
	inorder(tree->right);
}

/* parcurgerea in postnordine a arborelui creat, cu afișarea valorilor din noduri*/
// ex3.3 - 0.5p
void postorder(node* tree) //sdr
{
	if(tree!=NULL)
	{
		postorder(tree->left); 
		postorder(tree->right);  
		printf("%d ",tree->val);  
	}     
}

/* functia implementeaza
ștergerea subarborelui unui node oarecare,
prin setarea adreselor de legatură ale fiilor la valoarea NULL 
(doar sub arborele, nu si nodul) */
//  1p
void deleteSubTree(node** tree, int value)
{
	if(*tree!=NULL)
	{
		if((*tree)->val==value) //s-a ajuns la radacina subarborelui care trebuie sters
		{
			deleteSubTree(&(*tree)->left,value);
			deleteSubTree(&(*tree)->right,value);
			(*tree)->left=(*tree)->right=NULL;
		}
		else
		{
			if(value>(*tree)->val)
				deleteSubTree(&(*tree)->right,value);
			else if(value<(*tree)->val)
					deleteSubTree(&(*tree)->left,value);
		}
	}
}

/*
	functia va fi de ajutor pentru stergeri
*/
int isLeaf(node* nod)
{
	if(nod->left==NULL && nod->right==NULL) //daca nodul este frunza
		return 1;
	return 0;
}
node* getParent(node* tree, node* child);

void deleteLeaf(node** tree, int value)
{
	node *tmp=search(*tree, value);
	if(tmp!=NULL)
	{
		node *p=getParent(*tree,tmp);
		if(isLeaf(tmp)==1)
		{
			if(p->left==tmp)
			{	
				//free(p->left);
				p->left=NULL;
			}
			else if(p->right==tmp)
			{
				//free(p->right);
				p->right=NULL;
			}
		}
	}
}

/* 
	functia primeste arborele si un nod si intoarce parintele nodului
	functia va fi de ajutor pentru stergerea unui nod din arbore	
 */
node* getParent(node* tree, node* child) //child este nodul pentru care se cauta parintele
{
	if(tree!=NULL)
	{
		if(tree->left==child || tree->right==child)
			return tree;
		else
		{
			if(tree->val<child->val)
				return getParent(tree->right,child);
			else
				if(tree->val>child->val)
					return getParent(tree->left,child);
		}
	}
}

/* 
	functia gaseste succesorul inordine al radacinii
	si salveaza acest succesor in q
	va fi de folos pentru stererea unui nod
*/
void find_succesor(node** q, node* tree)
{
	while(tree->left!=NULL)
		tree=tree->left;
	*q=tree;	
}

/* 2p --- functia sterge un node din arbore */
void deleteNode(node** tree, int value)
{
	if((*tree)->val<value)
		deleteNode(&(*tree)->right,value);
	else if((*tree)->val>value)
		deleteNode(&(*tree)->left,value);
	else
	{
		if((*tree)->left!=NULL && (*tree)->right!=NULL) ///nodul eliminat are 2 copii
		{
			node *aux=NULL;
			find_succesor(&aux,(*tree)->right); //aux va fi succesorul in inordine al nodului de eliminat
			(*tree)->val=aux->val;
			deleteLeaf(&(*tree)->right,aux->val);
		}
		else if((*tree)->left!=NULL || (*tree)->right!=NULL) //nodul de eliminat are cel putin un copil
		{
			node *tmp=*tree;
			if((*tree)->left!=NULL)
				*tree=(*tree)->left;
			else if((*tree)->right!=NULL)
				*tree=(*tree)->right;
			free(tmp);
			tmp=NULL;
		}
	}
}
/* Compute the "height" of a tree -- the number of
    nodes along the longest path from the root node
    down to the farthest leaf node. - 0.5p*/
int leaf_number(node* tree) 
{
    if(tree==NULL)
    	return 0;
    else
    {
    	int l1=leaf_number(tree->right);
    	int l2=leaf_number(tree->left);
    	if(l1>l2)
    		return 1+l1;
    	else
    		return 1+l2;
    }
}

int vMax(node *tree) 
{
	node *aux=tree;
	aux=aux->right;
	while(aux->right!=NULL)
		aux=aux->right;
	return aux->val;
}

int vMin(node *tree)
{
	node *aux=tree;
	aux=aux->left;
	while(aux->left!=NULL)
		aux=aux->left;
	return aux->val;
}

/* scrieti o functie care verifica daca un arbore binar este un 
arbore binar de cautare --- 2P */

int is_binary_search_tree(node *tree) 
{
	if(tree==NULL)	 
		return 1;
	if(tree->left!=NULL && vMax(tree->left)>tree->val)
		return 0;
	if(tree->right!=NULL && vMin(tree->right)<tree->val);
		return 0;
	if(is_binary_search_tree(tree->left)==0 || is_binary_search_tree(tree->right)==0)
		return 0;
	return 1;
}

/*
    BONUS
    scrieti o functie care primeste 2 valori si calculeaza cel mai mic stramos
    comun al acestor 2 valori din arbore(se considera ca valorile se gasesc in arbore)
    Exemplu:
    pentru
            20
         /      \
        8       22
      /  \
    4     12
        /    \
        10  14    
    LCA pt 10 si 14 este 12
    LCA pt 14 si 8 este 8
    LCA pt 10 si 22 este 20 
    ---- 2P
*/
int lowest_common_ancestor(node* tree, int val1, int val2)
{
	if(tree==NULL)
		return -1;
    if(tree->val>val1 && tree->val>val2)
   		return lowest_common_ancestor(tree->left,val1,val2);
    if(tree->val<val1 && tree->val<val2)
   		return lowest_common_ancestor(tree->right,val1,val2);
   	return tree->val;
}


int main()
{
    node* tree = NULL;
    addnode(&tree, 14);
    addnode(&tree, 10);
    addnode(&tree, 2);
    addnode(&tree, 3);
    addnode(&tree, 4);
    addnode(&tree, 1);
    addnode(&tree, 13);
    addnode(&tree, 12);
    addnode(&tree, 22);
    addnode(&tree, 16);
    addnode(&tree, 35);
    addnode(&tree, 30);
    addnode(&tree, 40);
    addnode(&tree, 28);

    printTree(tree);
    
    node* searchedNode = search(tree, 16);
    assert(searchedNode != NULL);
    assert(searchedNode -> val == 16);
    printf("Nodul cu valoarea 16 exista \n"); 

    searchedNode = search(tree, 12);
    assert(searchedNode != NULL);
    assert(searchedNode -> val == 12);
    printf("Nodul cu valoarea 12 exista \n"); 

    searchedNode = search(tree, 14);
    assert(searchedNode != NULL);
    assert(searchedNode -> val == 14);
    printf("Nodul cu valoarea 14 exista \n"); 

    searchedNode = search(tree, 100);
    assert(searchedNode == NULL);
    printf("Nodul cu valoarea 100 nu exista\n");


    preorder(tree);
    printf("\n"); 

    inorder(tree);
    printf("\n");

    postorder(tree);
    printf("\n");


    printf("deleteSubTree 35\n");
    deleteSubTree(&tree, 35);
    printTree(tree);


    printf("deleteLeaf 10\n");
    deleteLeaf(&tree, 10);
    printTree(tree);
    printf("deleteLeaf 35\n");
    deleteLeaf(&tree, 35);
    printTree(tree);

    printf("deleteLeaf 28\n");
    deleteLeaf(&tree, 28);
    printTree(tree);

    printf("deleteNode 3\n");
    deleteNode(&tree, 3);
    printTree(tree);
    printf("deleteNode 10\n");
    deleteNode(&tree, 10);
    printTree(tree);
   
    printf("leafNumber %d \n", leaf_number(tree));
    printf("%d\n",is_binary_search_tree(tree));
    printf("Minimul din arbore %d\n",vMin(tree));
    printf("Maximul din arbore %d\n",vMax(tree));
    printf("stramosul comun  %d\n",lowest_common_ancestor(tree,1,22));
   
    return 0;
}
