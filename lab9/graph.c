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
    se initializeaza cu -1 matricea deoarece momentan nu exista muchii
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
            gr->mat[i][j]=-1;
    gr->n=n;
}

/* adauga muchie
    se va adauga muchie in graf de la a la b
    (fiind graf neorientat se va adauga AB dar si BA)
    0.5 P
*/
void add_edge(graf g, int a, int b)
{
    int i,j;
    for(i=0;i<g.n;i++)
        for(j=0;j<g.n;j++)
        {
            if(i==a&&j==b)
                g.mat[i][j]=1;
            else
                if(i==b&&j==a)
                    g.mat[i][j]=1;
        }
}

/* sterge muchie
    se va sterge muchia din graf de la a la b
    (fiind graf neorientat se va sterge AB dar si BA)
    0.5 P
*/
void del_edge(graf g, int a, int b)
{
    int i,j;
    for(i=0;i<g.n;i++)
        for(j=0;j<g.n;j++)
            if(i==a && j==b)
                g.mat[i][j]=-1;
            else
                if(i==b && j==a)
                    g.mat[i][j]=-1;
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
        {
            if(g.mat[i][j]==1)
                printf("1 ");
            else
                printf("0 ");
        }
        printf("\n");
    }
}


/* 
    parcurgere graf in adancime
    - 3 P
    PseudoCod:
    creeaza un vector visited cu valori 0
    marcheaza in vectorul visited nodul x ca fiind vizitat
    for each u adiacent cu x do
        if u nu e vizitat then
            dfs(graf, u)
        end if
    end for
*/

void DFS(graf g, int x,int *visited)
{
    int i,j;
    visited[x]=1;
    for(j=0;j<g.n;j++)
        if(g.mat[x][j]==1)
            {   
            if(visited[j]==0)
                 DFS(g,j,visited); 
            else
                    printf("%d ",x);
            }
}

/*
    functia adauga element intr-o coada
    REMINDER - Coada = First In First Out
    
*/
void push(nod** q, int val)
{
    nod *nou=(nod *)malloc(sizeof(nod));
    nou->val=val;
    nod *aux=*q;
    if(*q==NULL)
    {
       nou->next=NULL;
       *q=nou;
    }
    else
    {
       while(aux->next!=NULL)
        aux=aux->next;
    aux->next=nou;
    nou->next=NULL;
    }   
}

/*
    functia scoate element dintr-o coada
    REMINDER - Coada = First In First Out
    
*/
int pop(nod **q)
{
    nod *el=*q;
    *q=(*q)->next;
    int rez=el->val;
    free(el);
    return rez;
}


/*
    parcurgere graf in latime
    1. completati push si pop pentru coada si verificati intai ca acestea
    sa functioneze bine(vor fi necesare pt BFS) - 1P
    2. implementati BFS-ul - 3P
    
    PseudoCod:
    creeaza o coada Q
    creeaza un vector visited cu valori 0
    adauga x in coada Q
    marcheaza in vectorul visited nodul x ca fiind vizitat
    while coada Q nu e goala do
        t ← dequeue(Q)
        for each u adiacent cu t do
            if u nu e vizitat then
                marcheaza u ca vizitat
                adauga u in coada Q
            end if
        end for
    end while
*/
void BFS(graf g, int x,int *visited1)
{
    int i;
    nod *q=NULL;
    push(&q,x);
    visited1[x]=1;
    while(q!=NULL)
    {
        int t=pop(&q);
        printf("%d ",t);
        for(i=0;i<g.n;i++)
            if(visited1[i]==0 && (g.mat[i][t]==1 || g.mat[t][i]==1))
            {
                visited1[i]=1;
                push(&q,i);
            }
    }
}

/* numarul de componente conexe - 1P*/
int nr_comp_conexe(graf g,int visited1)
{
    

}

int main()
{
    int visited[100]={0};
    graf g;
    int n = 10;
    init(&g, n);
    add_edge(g, 0, 2);
    add_edge(g, 0, 3);
    add_edge(g, 1, 2);
    add_edge(g, 3, 4);
    add_edge(g, 4, 2);
    add_edge(g, 0, 3);
    add_edge(g, 4, 5);
    add_edge(g, 4, 6);
    add_edge(g, 4, 7);
    add_edge(g, 7, 8);
    add_edge(g, 7, 9);
    print_graph(g);
    del_edge(g, 0, 3);
    printf("\n");
    print_graph(g);
    printf("0 ");
    DFS(g, 0,visited);
    printf("\n");
    int visited1[100]={0};
    BFS(g, 0,visited1);
//    del_edge(g, 7, 9);
//    printf("Comp conexe -> %d\n", nr_comp_conexe(g));
    return 0;
}
