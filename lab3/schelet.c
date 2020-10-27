#include <stdio.h>
#include <stdlib.h>

typedef struct nod {
    struct nod* next;
    int val;
} nod;

/* functia printeaza elementele unei liste simplu inlantuite 0.5p */
void printList(nod* cap)  
{
    nod *aux;
    aux=cap;
    while(aux!=NULL)
    {
        printf("%d ",aux->val);
        aux=aux->next;
    }
}

/* functia afla lungimea unei liste simplu inlantuite 0.5p */
int length(nod* cap)
{
    int k=0;
    nod *aux=cap;
    while(aux!=NULL)
    {
        k++;
        aux=aux->next;
    }
    return k;
}

/* functia insereaza un element la inceputul listei simplu inlantuite 1p*/
void insertFirst(nod** cap, int val) 
{
    nod *nou=(nod *)malloc(sizeof(nod));
    nou->val=val;
    nou->next=*cap;
    *cap=nou;
}

/* functia insereaza un element la sfarsitul listei simplu inlantuite 1p*/
void insertLast(nod** cap, int val) 
{
    nod *nou=(nod *)malloc(sizeof(nod));
    nou->val=val;
    nod *aux=*cap;//se parcurge lista
    while(aux->next!=NULL)
      aux=aux->next;
    aux->next=nou;
    nou->next=NULL;
}


/* functia insereaza un element la pozitia p 
numerotarea pozitilor va incepe la 0
a listei simplu inlantuite - sau la final daca aceasta pozitie nu exista 1p*/
void insertMiddle(nod** cap, int val, int p) 
{
    nod *nou=(nod *)malloc(sizeof(nod));
    nou->val=val;
    nod *aux=*cap;//se parcurge lista
    nod *aux1=aux;
    int i=0;
    while(aux->next!=NULL&&i!=p)
    {
        aux1=aux;
        aux=aux->next;
        i++;
    }
    if(aux->next==NULL)
        insertLast(cap,val);
    else
    { 
        aux1->next=nou;
        nou->next=aux;
    }
}


/* sterge un element de la inceputul unei liste simplu inlantuite 1p*/
void deleteHead(nod** cap) 
{
   //*cap=(*cap)->next;
	nod *aux;
	aux=*cap;
	*cap=(*cap)->next;
	free(aux);
}


/* sterge element de la sfarsitul unei liste simplu inlantuite  1p*/
void deleteLast(nod** cap) 
{
    nod *aux=*cap;
    nod *aux1=aux;
    while(aux->next!=NULL)
    {
        aux1=aux;
        aux=aux->next;
    }
    aux1->next=NULL;
}

/* sterge un element de la pozitia p 
numerotarea pozitilor va incepe la 0
a unei liste simplu inlantuite 1p*/
void deleteMiddle(nod** cap, int p) 
{
    nod *aux=*cap;
    nod *aux1=aux;
    int i=0;
    while(aux->next!=NULL&&i!=p)
    {
        aux1=aux;
        aux=aux->next;
        i++;
    }
    aux1->next=aux->next;
}

/* 
1 p
Scrieti o functie care primeste 2 liste simplu inlantuite ce sunt sortate crescator
si face ”merge” celor doua liste in o lista sortata crescator. Functia trebuie sa
returneze noua lista.
*/

nod *merge(nod *a,nod *b)
{
    nod *rez=NULL;
    if(a==NULL)
        return b;
    if(b==NULL)
        return a;
    if(a->val<=b->val)  
    { 
        rez=a; 
        rez->next=merge(a->next,b); 
    } 
    else 
    { 
        rez=b; 
        rez->next=merge(a,b->next); 
    } 
    return(rez);
}


/*
1 p
Transformati functia de la exercitiu 6 astfel incat sa nu se creeze noduri noi ci
sa se schimbe legaturile intre nodurile dintre cele 2 liste.
*/


/*

2 p
Avand o lista simplu inlantuita, rotiti lista cu k elemente in sensul acelor de
ceasornic. Exemplu: daca avem 10->20->30->40->50->60 si k = 4 atunci
output-ul ar trebui sa fie 50->60->10->20->30->40. Puteti prespune ca k este
mai mic decat numarul de noduri din lista.
*/

void rotire(nod **l3,int k)
{
    for(int i=1;i<=k;i++)
    {
    	int x=(*l3)->val;
    	deleteHead(l3);
    	insertLast(l3,x);
	}
}

int main()
{
    nod *cap = NULL;
    
    insertFirst(&cap, 2);
    insertFirst(&cap, 3);
    printList(cap);
    printf("Lungimea %d\n",length(cap));
    
    insertMiddle(&cap, 1, 1);
    printList(cap);
    printf("Lungimea %d\n",length(cap));
   
    insertLast(&cap,4);
    insertLast(&cap, 1000);
    printList(cap);
    printf("Lungimea %d\n",length(cap));
    
    insertMiddle(&cap, 1222, 7);
    printList(cap);
    printf("Lungimea %d\n",length(cap));

    deleteHead(&cap);
    printList(cap);
    printf("Lungimea %d\n",length(cap));

    deleteMiddle(&cap, 1);
    deleteMiddle(&cap, 1);
    printList(cap);
    printf("Lungimea %d\n",length(cap));
   
    deleteLast(&cap);
    printList(cap);
    printf("Lungimea %d\n",length(cap));

    nod *l1=NULL;
    nod *l2=NULL;
    insertFirst(&l1,9);
    insertFirst(&l1,7);
    insertFirst(&l1,4);
    insertFirst(&l2,20);
    insertFirst(&l2,16);
    insertFirst(&l2,0);
    printList(l1);
    printf("\n");
    printList(l2);
    printf("\n");
    nod *mergeLst=NULL;
    mergeLst=merge(l1,l2);
    printList(mergeLst);
    printf("\n");
   	printf("****************************\n");
    //nod *rez=rotire(mergeLst,3);
    //printList(rez);
    nod *l3=NULL;
    insertFirst(&l3,9);
    insertFirst(&l3,7);
    insertFirst(&l3,4);
    insertFirst(&l3,20);
    insertFirst(&l3,16);
    printList(l3);
/*    printf("\n");
    for(int i=0;i<4;i++)
    {
    	int x=l3->val;
    	deleteHead(&l3);
    	insertLast(&l3,x);
    	printList(l3);
    	printf("\n");
	}
*/
    int k;
    scanf("%d",&k);
	rotire(&l3,k); 
	printList(l3);
    printf("\n");
    return 0;
}
