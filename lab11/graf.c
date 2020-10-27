#include <stdio.h>
#include <stdlib.h>

typedef struct graf
{
    int n;
    int **mat;
} graf;


typedef struct nod
{
    struct nod* next;
    int val;
} nod;


/* initializeaza graf 
    se aloca memorie pentru matricea de adiacenta(care va avea n elemente)
    se initializeaza cu 0 matricea deoarece momentan nu exista muchii
    0.5 P
*/
void init(graf *gr, int n) 
{
	int i,j;
    gr->mat=(int **)malloc(n*sizeof(int*));
    for(i=0;i<n;i++)
        gr->mat[i]=(int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            gr->mat[i][j]=0;
    gr->n=n;
}

/* adauga muchie
    se va adauga muchie in graful orientat de la a la b
    costul muchiei va fi primit parametru - valoarea v
    0.5 P
*/
void add_edge(graf g, int a, int b, int v)
{
	int i,j;
    for(i=0;i<g.n;i++)
        for(j=0;j<g.n;j++)
        {
            if(i==a && j==b)
                g.mat[i][j]=v;
        }
}

/* sterge muchie
    se va sterge muchia din graf de la a la b
    0.5 P
*/
void del_edge(graf g, int a, int b)
{
	int i,j;
    for(i=0;i<g.n;i++)
        for(j=0;j<g.n;j++)
            if(i==a && j==b)
                g.mat[i][j]=0;
}

/*
    se va afisa matricea de adiacenta a grafului
    0.5 P
*/
void print_graph(graf g)
{
	int i,j;
	for(i=0;i<g.n;i++)
	{
		for(j=0;j<g.n;j++)
			printf("%d ",g.mat[i][j]);
		printf("\n");
	}
}

/*
    functia adauga element in lista
    
*/
void add_head(nod** q, int val)
{
	nod* nou=(nod*)malloc(sizeof(nod));
	nou->val=val;
	nou->next=NULL;
	if(*q==NULL)
	{
		*q=nou;
		return;
	}
	nou->next=(*q);
	*q=nou;
}

/*
    functia scoate element din lista
*/
int delete(nod **q)
{
    nod* aux=*q;
    while(aux->next!=NULL)
    	aux=aux->next;
    free(aux);
    aux=NULL;
}

/*
    functia printeaza elementele dintr-o lista
*/
void print_list(nod *q)
{
	nod* aux=q;
	while(aux!=NULL)
	{
		printf("%d ",aux->val);
		aux=aux->next;
	}
	printf("\n");
}

/* 
    Implementati sortarea topologica conform pseudocodului de mai jos
    
        1P - implementare corecta functii liste
        2P - implementare corecta algoritmi
        Total = 3P
    L ← Empty list that will contain the sorted nodes
    while there are unmarked nodes do
        select an unmarked node n
        visit(n) 
    print(L)


    function visit(node n)
        if n has a permanent mark then return
        if n has a temporary mark then stop (not a DAG)
        mark n temporarily
        for each node m with an edge from n to m do
            visit(m)
        mark n permanently
        add n to head of L
*/

void visit(int aux,int* marks,graf g,nod** list)
{
	if(marks[aux]==1) //permanent mark
		return;
	if(marks[aux]==2)
	{
		printf("Cicluri\n");
		return;
	}
	marks[aux]=2;
	for(int i=0;i<g.n;i++)
		if(g.mat[aux][i]!=0)
			visit(i,marks,g,list);
	marks[aux]=1;
	add_head(list,aux);
	print_list(*list);
}

void topological(graf g)
{
	int* marks=(int* )calloc(g.n,sizeof(int));
	nod* list=NULL;
	int i,k=0,next;
	do
	{k=0;
	for(i=0;i<g.n;i++)
		if(marks[i]==0)
		{
			k++;
			next=i;
		}
	if(k!=0) //exista noduri care nu au fost marcate
		visit(next,marks,g,&list);
	}while(k!=0);
	print_list(list);
}


int check_compl(int v[], int n)
{
}

/*
    Implementati algoritmul lui Primm 
    conform pseudocodului de mai jos - 4P
    
   Algorithm 1 Prim(V, E)
    {V = setul de noduri, U = setul de muchii}
    init, initializeaza un arbore V1 cu un singur nod arbitrar din V
    while V ! = V1 do
        alege muchia (u, v), u din V1, v din V/V1 cu ponderea minima
        adauga v la V1 si (u, v) la E1
    end while
    return (V 1, E1)
*/

#define M 20
#define M2 100001
void primm(graf g,int* x,int* y,int c[])
{
	int cmin;
	int p[g.n],i,j,k;
	for(i=1;i<g.n;i++)
	{
		p[i]=0;
		c[i]=g.mat[0][i]; //costuri initiale, nodul initial este 0
	}
	for(i=1;i<g.n;i++)
	{	//se cauta nodul k cel mai apropiat de un nod din arbore
		cmin=c[1];
		k=1;
		for(j=1;j<g.n;j++)
			if(c[j]<cmin)
			{
				cmin=c[j];
				k=j; 
			}
		x[i-1]=p[k];
		y[i-1]=k;
		c[k]=M2;
		for(j=1;j<g.n;j++)
			if(g.mat[k][j]<c[j] && c[j]<M2)
			{
				c[j]=g.mat[k][j];
				p[j]=k;
			}
	}
}

int main()
{
    graf g;
    int n = 10;
    init(&g, n);
    add_edge(g, 0, 2, 3);
    add_edge(g, 0, 3, 5);
    add_edge(g, 1, 2, 1);
    add_edge(g, 3, 4, 7);
    add_edge(g, 4, 2, 4);
    add_edge(g, 4, 5, 10);
    add_edge(g, 4, 6, 100);
    add_edge(g, 4, 7, 4);
    add_edge(g, 7, 8, 1);
    add_edge(g, 7, 9, 7);
    add_edge(g, 9, 1, 4);
    printf("Print graf\n");
    print_graph(g);
    del_edge(g, 4, 2);
    printf("Print graf dupa delete\n");
    print_graph(g);
    printf("Sortare topologica\n");
    topological(g);
    add_edge(g, 4, 2, 4);
    add_edge(g, 5, 6, 22);
 
  	printf("Muchii adaugate \n");
    print_graph(g);
    printf("Arborele minim de acoperire\n");
    int* x,*y;
    int* c=(int*)malloc(g.n*sizeof(int));
    for(int i=0;i<g.n;i++)
    	c[i]=M;
    x=(int* )calloc(g.n,sizeof(int));
    y=(int* )calloc(g.n,sizeof(int));
    primm(g,x,y,c);
    int i;
    for(i=0;i<g.n-1;i++)
    	printf("%d - %d\n",x[i],y[i]);
    printf("\n");

    return 0;
}
