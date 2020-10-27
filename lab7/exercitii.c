#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 26

typedef struct node 
{
	struct node *children[SIZE];
	int end;
}node;

node *initNode()
{
	node *nou=NULL;
	nou=(node *)malloc(sizeof(node));
	nou->end=0;
		for(int i=0;i<SIZE;i++)
			nou->children[i]=NULL;
	return nou;
}

//returneaza la ce index trebuie sa ne aflam in vector pt litera curenta current
int computeIndex(char current)
{
	return ((int)current-(int)'a');
}

void addWord(node **trie, char *word)
{
	node *aux=*trie;
	for(int i=0;i<strlen(word);i++)
	{
		int index=computeIndex(word[i]);
		if(!aux->children[index])
			aux->children[index]=initNode();
		aux=aux->children[index];
	}
	aux->end=1;
}

int search(node *trie, char *word)
{
	node *aux=trie;
	for(int i=0;i<strlen(word);i++)
	{
		int index=computeIndex(word[i]);
		if(aux->children[index]==NULL)
			return 0;
		aux=aux->children[index];
	}
	if(aux->end==1) //daca am ajuns la sf de cuvant si acesta este setat in trie
		return 1;
	return 0;
}

void printContent(node *trie, char *s, int n)
{
	if(trie->end==1)
	{
		s[n]='\0';
		printf("%s\n",s);
	}
	int i;
	for(i=0;i<SIZE;i++)
		if(trie->children[i]) //este gasit un copil nenul
		{
			s[n]=i+'a';
			printContent(trie->children[i],s,n+1);
		}
}

void deleteWord(node *trie, char *word,int depth)
{
	if(trie==NULL)
		return NULL;
	if(depth==sizeof(word))
	{
		if(trie->end)
			trie->end=0;
		if()
	}
}


int main()
{
	node *root=initNode();
	char keys[][8] = {"the", "a", "there", "answer", "any", 
                     "by", "bye", "their"}; 
    int i; 
    for (i = 0; i <8; i++) 
        addWord(&root,keys[i]);
    printf("%d\n", search(root, "the") ); 
    printf("%d\n",  search(root, "these") ); 
    printf("%d\n",  search(root, "their") ); 
    printf("%d\n",  search(root, "thaw") ); 
    int level=0;
    char str[20];
    printContent(root,str,level);
    return 0;
}