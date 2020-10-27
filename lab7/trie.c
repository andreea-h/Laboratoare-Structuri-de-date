#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 26

typedef struct node
{
     struct node *kids[SIZE];
     int end;
} node;

// functia initializeaza un nod nou si il salveaza in new_node
// 1p
// functia trebuie sa aloce memorie,
// sa initializeze toti copiii nodului cu NULL 
// si sa seteze faptul ca momentan nodul nu e cuvant
void initNode(node **new_node)
{
	node *nou=NULL;
	nou=(node *)malloc(sizeof(node));
	nou->end=0;
		for(int i=0;i<SIZE;i++)
			nou->kids[i]=NULL;
	*new_node=nou;
}

/* functia calculeaza la ce index ar trebui sa ne aflam in vector pentru litera curenta */
int computeIndex(char current)
{
	return current - 'a';
}

// functia stocheaza cuvantul word primit ca parametru in trie
// functia va parcurge cuvantul litera cu litera si se va plimba prin trie pornind de la radacina
// daca litera nu exista in trie, va insera litera curenta a cuvantului, mutandu-se pe copilul literei respective
// daca litera exista in trie, atunci doar ne mutam pe copilul literei respective
// daca am ajuns la ultima litera din cuvant, avem grija sa setam acest nod ca fiind end petrnu un cuvant
// 1p
void addWord(node *trie, char *word)
{
	node *aux=trie;
	for (int i=0;i<strlen(word);i++)
	{
		int index=computeIndex(word[i]);
		if(!aux->kids[index])
			initNode(&aux->kids[index]);
		aux=aux->kids[index];
	}
	aux->end=1;
}

// functia cauta cuvantul word primit ca parametru 
// in trie
// 1p
// functia parcurge practic trie-ul de la radacina si literele din cuvant
// si ne mutam mereu pe copilul al carei litere o prelucram
// daca la un momentan copilul pentru litera respectiva e NULL, inseamna ca cuvantul nu se gaseste in trie
// daca am terminat literele din cuvant, verificam daca ultimul este sau nu setat ca sfarsit de cuvant
// daca este sfarsit de cuvant, atunci cuvantul se afla in trie
// altfel intoarcem faptul ca cuvantul nu se afla in trie
int search(node *trie, char *word)
{
	node *aux=trie;
	for(int i=0;i<strlen(word);i++)
	{
		int index=computeIndex(word[i]);
		if(aux->kids[index]==NULL)
			return 0;
		aux=aux->kids[index];
	}
	if(aux->end==1) //daca am ajuns la sf de cuvant si acesta este setat in trie
		return 1;
	return 0;
}

// functia afiseaza toate cuvintele stocate in trie
// puteti modifica parametrii functiei daca considerati necesar
// 1.5p
void printContent(node *trie, char *s, int *n)
{
	if(trie->end==1)
	{
		s[*n]='\0';
		printf("%s\n",s);
	}
	int i;
	for(i=0;i<SIZE;i++)
		if(trie->kids[i]) //este gasit un copil nenul
		{
			s[*n]=i+'a';
			*n=*n+1;
			printContent(trie->kids[i],s,n);
		}
}

int Empty(node *root)
{
	for (int i=0;i<SIZE;i++)
		if(root->kids[i])
			return 0;
	return 1;
}

// functia sterge un cuvant din trie-ul dat
// 1.5p
// cazuri
// Key may not be there in trie. Delete operation should not modify trie.
// Key present as unique key (no part of key contains another key (prefix), nor the key itself is prefix of another key in trie). Delete all the nodes.
// Key is prefix key of another long key in trie. Unmark the leaf node.
// Key present in trie, having at least one other key as prefix key. Delete nodes from end of key until first leaf node of longest prefix key.
void deleteWord(node *trie, char *word,int depth)
{
	if(!trie)
		return;
	if(depth==sizeof(word)) //ultimul caracter din cuvant
	{
		if(trie->end)
			trie->end=0;
		if(Empty(trie))
		{
			free(trie);
			trie=NULL;
		}
	}
	int index=computeIndex(word[depth]);
	deleteWord(trie->kids[index],word,depth+1);
	if(Empty(trie) && trie->end==0)
	{
		free(trie);
		trie=NULL;
	}
}

// functia primeste un string fiind un prefix bagat de user la tastaura
// si afiseaza ca raspuns toate sugestiile care incep cu acel prefix
// adica toate cuvintele din trie care au acel prefix
// in cazul in care prefixul nu se afla in trie se va afisa un mesaj de eroare si functia va intoarce 0
// daca avem macar un cuvant ca sugestie pentru prefixul respectiv functia intoarce 1
// 1p

void printWord(char *str)
{
	printf("\n");
	for (int i=0;i<strlen(str);i++)
		printf("%c",str[i]);
}

int printSuggestion(node* root, char *prefix) 
{
	if(root==NULL)
		return 0;
	if(root->end==1)
		printWord(prefix);
	for (int i=0;i<SIZE;i++)
		if(root->kids[i]!=NULL)
		{
			
			printSuggestion(root->kids[i],prefix);
		}
}

int main()
{
	FILE *fp;
	char buff[255];
	char **words;
	int nr, i;
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &nr);
	words = (char**) malloc (sizeof(char*) * nr);
	for(i = 0; i <= nr; i++)
	{
		memset(&buff[0], '\0', sizeof(buff));
		fgets(buff, 255, (FILE*)fp);
		if(i==0) 
		{	
			continue;
		}
		words[i-1] = (char*) malloc (sizeof(char) * (strlen(buff)));
		strncpy(words[i-1], buff, strlen(buff)-1);
	}
  	fclose(fp);

	node *trie;

	initNode(&trie);

	for(i = 0; i < nr; i++)
	{
		addWord(trie, words[i]);
	}

	printf("should print 1 %d \n", search(trie, "bye"));
	printf("should print 0 %d \n", search(trie, "byer"));
	printf("should print 1 %d \n", search(trie, "there"));
    	printf("should print 0 %d \n", search(trie, "these"));
	printf("should print 0 %d \n", search(trie, "b"));
	printf("should print 1 %d \n", search(trie, "a"));

	char s[50];
	int n = 0;
	printf("Print content\n");
	printContent(trie, s, &n);

	deleteWord(trie, "bye",0);
	printf("should print 0 %d \n", search(trie, "bye"));
	n = 0;
	memset(s, '\0', 50);
	printf("Print content dupa delete\n");
	printContent(trie, s, &n);

	printf("Print suggestions--> th \n");
	printSuggestion(trie, "th");
	printf("Print suggestions--> them \n");
	printSuggestion(trie, "them");
	printf("Print suggestions--> cuvantul \n");
	printSuggestion(trie, "cuvantul");
	
	return 0;
}
