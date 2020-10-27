#include <stdio.h>
#include <stdlib.h>

typedef struct nod {
    struct nod* next;
    struct nod* prev;
    int val;
} nod;

/* functia printeaza elementele unei liste dublu inlantuite 0.5p */
void printList(nod* cap)  
{
	nod *aux=cap;
	while(aux!=NULL)
	{
		printf("%d ",aux->val);
		aux=aux->next;
	}
	printf("\n");
}

/* functia printeaza elementele unei liste dublu inlantuite in ordine inversa 0.5p */
void reversePrintList(nod* cap) 
{
	nod *aux=cap;
	nod *aux1=cap;
	while(aux1->next!=NULL)  //se trece prin lista
		aux1=aux1->next;
	while(aux1!=NULL)
	{
		printf("%d ",aux1->val);
		aux1=aux1->prev;
	}
	printf("\n");
}

/* functia afla lungimea unei liste dublu inlantuite 0.5p */
int length(nod* cap)
{
	nod *aux=cap;
	int k=0;
	while(aux!=NULL)
	{
		k++;
		aux=aux->next;
	}
	return k;
}

/* functia insereaza un element la inceputul listei dublu inlantuite 1p*/
void insertFirst(nod** cap, int val) 
{
	nod *nou=(nod *)malloc(sizeof(nod));
	nou->val=val;
	if(*cap==NULL)
	{
		nou->next=NULL;
		nou->prev=NULL;
		*cap=nou;
	}
	else
	{
		(*cap)->prev=nou;
		nou->next=*cap;
		nou->prev=NULL;
		*cap=nou;
	}
}

/* functia insereaza un element la jumatea listei dublu inlantuite 1p*/
void insertMiddle(nod** cap, int val) 
{
	nod *nou=(nod *)malloc(sizeof(nod));
	nou->val=val;
	int n=length(*cap)/2;
	int i=0;
	nod *aux=*cap;
	while(aux!=NULL&&i<n)
	{
		i++;
		aux=aux->next;
	}
	nou->prev=aux;
	nou->next=aux->next;
	if(aux->next!=NULL)
	{
		aux->next->prev=nou;
	}
	aux->next=nou;
}

/* functia insereaza un element la sfarsitul listei dublu inlantuite 1p*/
void insertLast(nod** cap, int val) 
{
	nod *nou=(nod *)malloc(sizeof(nod));
	nou->val=val;
	if(*cap==NULL)
	{
		nou->next=NULL;
		nou->prev=nou;
		*cap=nou;
	}
	else
	{
		nod *aux=*cap;
		while(aux->next!=NULL)
			aux=aux->next;
		aux->next=nou;
		nou->prev=aux;
		nou->next=NULL;
	}
}

/* sterge un element de la inceputul unei liste dublu inlantuite 1p*/
void deleteHead(nod** cap) 
{
	nod *aux=*cap;
	*cap=(*cap)->next;
	(*cap)->prev=NULL;
	free(aux);
}

/* sterge un element de la jumatea unei liste dublu inlantuite 1p*/
void deleteMiddle(nod** cap) 
{
	int n=length(*cap)/2;
	int i=0;
	nod *aux=*cap;
	while(aux->next!=NULL&&i<n)
	{
		i++;
		aux=aux->next;
	}
	aux->prev->next=aux->next;
	aux->next->prev=aux->prev;
}

/* sterge element de la sfarsitul unei liste dublu inlantuite  1p*/
void deleteLast(nod** cap) 
{
	nod *aux=*cap;
	while(aux->next!=NULL)
		aux=aux->next;
	aux->prev->next=aux->next;
}

/* 1.5p - 
	Se dau doua liste dublu inlantuite prin pointerii cap1 si cap2, si un nod oarecare din prima lista.
	Scrieti o functie care insereaza a doua lista intre acest nod si urmatorul nod al primei liste. Nodul poate fi oricare
	dintre nodurile primei liste. Listele vor avea o lungime cel putin egala cu 3.
	Se consideră două liste dublu înlănțuite, specificate prin pointerii

	Indicații: Este necesar să se modifice nodul specificat din prima listă, astfel incât să
	indice către primul element din a doua listă, iar ultimul nod din a doua listă să indice către
	elementul care urmează nodului dat din prima listă.
*/


void insert(nod **lst1,nod **lst2,nod *el)
{
	nod *aux=*lst1;
	while(aux!=el)
		aux=aux->next;
	(*lst2)->prev=aux;
	nod *aux2=*lst2;
	while(aux2->next!=NULL)
		aux2=aux2->next;
	if(aux->next!=NULL)
		aux->next->prev=aux2;
	aux2->next=aux->next;
	aux->next=*lst2;
}

/* 2p -
	Avand o lista dublu inlantuita cu n noduri, inversati fiecare grupuri de k noduri are listei
	
	Ex:
	Input:
		k = 2
		Lista: 10 <-> 8 <-> 4 <-> 2
	Output:
		8<->10<->2<->4
		
	Input:
		k = 3
		Lista: 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6 <-> 7 <-> 8
	Output:
		3 <-> 2 <-> 1 <-> 6 <-> 5 <-> 4 <-> 8 <-> 7
*/

void inversare(nod **cap,int k)
{
	int i;
	nod *aux=(*cap)->next;
	nod *temp;
	while(aux!=NULL)
	{
		for(i=0;i<k;i++)
		{
			temp=aux->prev;
			aux->prev=aux->next;
			aux->next=temp;
			aux=aux->next;
		}
		aux=aux->next;
	}
}

int main()
{
    nod *cap = NULL;
    
    insertFirst(&cap, 2);
    insertFirst(&cap, 3);
    printList(cap);
    reversePrintList(cap);
   	printf("Lungimea %d\n",length(cap));
    
    insertMiddle(&cap, 1);
    printList(cap);
   	reversePrintList(cap);
    printf("Lungimea %d\n",length(cap));
   
    insertLast(&cap,4);
    insertLast(&cap, 1000);
    printList(cap);
    reversePrintList(cap);
    printf("Lungimea %d\n",length(cap));
    
    insertMiddle(&cap, 10);
    //insertMiddle(&cap, 20);
    printList(cap);
    reversePrintList(cap);
    printf("Lungimea %d\n",length(cap));
    //printList(cap);

	deleteHead(&cap);
    printList(cap);
    reversePrintList(cap);
    printf("Lungimea %d\n",length(cap));
    
    deleteMiddle(&cap);
    //printList(cap);
    deleteMiddle(&cap);
    printList(cap);
    reversePrintList(cap);
    printf("Lungimea %d\n",length(cap));
    
    deleteLast(&cap);
    printList(cap);
    reversePrintList(cap);
    printf("Lungimea %d\n",length(cap));
   
    printf("\n");
    nod *lst1=NULL;
    nod *lst2=NULL;
    insertLast(&lst1,1);
    insertLast(&lst1,2);
    insertLast(&lst1,3);
    insertLast(&lst1,4);
    printList(lst1);
    insertLast(&lst2,10);
    insertLast(&lst2,15);
    insertLast(&lst2,20);
   	printList(lst2);
   	insert(&lst1,&lst2,lst1->next->next);
   	printList(lst1);

  // 	inversare(&lst1,2);
  // 	printList(lst1);
  // 	//reversePrintList(lst1);
    return 0;
}
