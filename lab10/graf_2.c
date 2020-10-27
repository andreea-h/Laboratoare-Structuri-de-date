#include <stdio.h>
#include <stdlib.h>

typedef struct nod
{
    struct nod* next;
    int val;
    int end;
} nod;

typedef struct graf {
    nod** vect;
    int n;
} graf;

typedef struct graf_mat {
    int **mat;
    int n;
} graf_mat;

/* functie auxiliara folositoare pentru add_edge */
void add_to_list(nod** list, int val, int end)
{
	nod* nou=(nod *)malloc(sizeof(nod));
	nou->val=val;
	nou->end=end;
	nou->next=NULL;
	if(*list==NULL)
		*list=nou;
	else
	{
		nod *aux=*list;
		while(aux->next!=NULL)
			aux=aux->next;
		aux->next=nou;
	}
}

/* functie auxiliara folositoare pentru delete_edge */
void delete_from_list(nod** list, int end)
{
	nod *aux=*list;
    nod *aux1=aux;
    if((*list)->end==end)
    	(*list)=(*list)->next;
    while(aux->next!=NULL && aux->end!=end)
    {
     	aux1=aux;
        aux=aux->next;
    }
    aux1->next=aux->next;
}

/* functie auxiliara folositoare pentru print_graf */
void print_list(nod* list)
{
	nod *aux=list;
	while(aux!=NULL)
	{
		printf("%d-%d\n",aux->val,aux->end);
		aux=aux->next;
	}
}

/* functia aloca memorie pentru graful g (pentru vectorul de n noduri ale grafului)
    si intializaeaza dimensiunea n a vectorului grafului 0.5P*/
void init_graf(graf* g, int n)
{
	g->vect=(nod **)malloc(n*sizeof(nod*));
	int i;
	for(i=0;i<n;i++)
		g->vect[i]=NULL;
	g->n=n;
}

/* adauga muchia cu valoarea val de la a la b in graf 
    se va insera practic muchia in lista de adiacenta a lui a, pentru nodul b
    folositi-va daca considerati ca va ajuta de functia add_to_list, unde
    lista este lista de adiacenta a lui a,
    valoarea este val, iar end este b 1P*/
void add_edge(graf g, int a, int b, int val)
{
	add_to_list(&g.vect[a],val,b);
}

/* sterge muchia cu valoarea val de la a la b in graf 
    se va sterge muchia din lista de adeiacenta a lui a, pentru nodul b
    folosti-va de delete_from_list 1P*/
void delete_edge(graf g, int a, int b)
{
	delete_from_list(&g.vect[a],b);
}

/* afiseaza graful (prin lista de adiacenta a fiecarui nod)
    puteti folosi functia auxiliara print_list  0.5 P*/
void print_graf(graf g)
{
	int i;
	for(i=0;i<g.n;i++)
		print_list(g.vect[i]);
}

/* 
    functia primeste un graf reprezentat prin liste de adiacenta
    si returneaza un graf reprezentat prin matrice de adiacenta - 1p
    */
graf_mat convert_to_matrix(graf g, int n)
{
    int i;
    graf_mat g2;
    g2.n = g.n;
    g2.mat = (int**) malloc (sizeof(int*) * n);
    for(i = 0; i < n; i++)
        g2.mat[i] = (int*) malloc (sizeof(int) * n);
    for(i=0;i<g.n;i++)
    {
    	nod *list=g.vect[i];
    	while(list!=NULL)
    	{
    		g2.mat[i][list->end]=g.vect[i]->val;
    		list=list->next;
    	}
    }
    // TODO - trebuie doar sa parcurgeti listele din g, si sa adaugati muchiile respective in g2
    
   // g2.n = 0; // linia asta se va sterge - este pusa doar ca pana la exercitiu asta sa nu aveti probleme in main
    return g2;
}


/* 
3p - 
    Implementati algoritmul Floyd-Warshall pentru aflarea cailor de lungime
    minima dintre oricare doua noduri ale unui graf orientat ponderat.
    functia va returna matricea cu distantele
    Algorithm 2 FloydWarshall(w, n)
    {w = matricea ponderilor, dist = matricea distantelor}
    initializati matricea dist cu infinit
    for each muchie (u, v) do
        dist(u,v) = w(u,v)
    end for
    for k = 1 : n do
        for i = 1 : n do
            for j = 1 : n do
                if dist(i, j) > dist(i, k) + dist(k, j) then
                    dist(i, j) = dist(i, k) + dist(k, j)
                end if
            end for
        end for
    end for
*/

int** floyd_warshall(graf_mat g)
{
	int **dist;
	dist=(int **)malloc(g.n*sizeof(int *));
	for(int i=0;i<g.n;i++)
		dist[i]=(int *)malloc(g.n*sizeof(int));
	int i,j,k;
	for(i=0;i<g.n;i++)
		for(j=0;j<g.n;j++)
		{
			if(g.mat[i][j]!=0)
				dist[i][j]=g.mat[i][j]; 
			if(g.mat[i][j]==0)
				dist[i][j]=10000000;
		}
	for(k=0;k<g.n;k++)
		for(i=0;i<g.n;i++)
			for(j=0;j<g.n;j++)
				if(dist[i][j]>dist[i][k]+dist[k][j])
					dist[i][j]=dist[i][k]+dist[k][j];
	return dist;
}




/*
 3P - Implementati algoritmul lui dijsktra pentru aflarea  costului minim de la o sursa
    Explicatii:
	Initialization of all nodes with distance "infinite"; initialization of the starting node with 0
	Marking of the distance of the starting node as permanent, all other distances as temporarily.
	Setting of starting node as active.
	Calculation of the temporary distances of all neighbour nodes of the active node by summing up its distance with the weights of the edges.
	If such a calculated distance of a node is smaller as the current one, update the distance and set the current node as antecessor. This step is also called update and is Dijkstra's central 	idea.
	Setting of the node with the minimal temporary distance as active. Mark its distance as permanent.
	Repeating of steps 4 to 7 until there aren't any nodes left with a permanent distance, which neighbours still have temporary distances.

    Pseudocod:
1:	function Dijkstra(Graph, source):
2:		for each vertex v in Graph:	// Initialization
3:			dist[v] := infinity	// initial distance from source to vertex v is set to infinite
4:			previous[v] := undefined	// Previous node in optimal path from source
5:			dist[source] := 0	// Distance from source to source
6:			Q := the set of all nodes in Graph	// all nodes in the graph are unvisited - thus are in Q
7:			while Q is not empty:	// main loop
8:				u := node in Q with smallest dist[ ]
9:				remove u from Q
10:				for each neighbor v of u:	// where v has not yet been removed from Q.
11:					alt := dist[u] + dist_between(u, v)
12:					if alt < dist[v]	// Relax (u,v)
13:						dist[v] := alt
14:						previous[v] := u


*/
void dijkstra(graf_mat g, int *dist, int *prev,int source)
{
	int i;
    for(i=0;i<g.n;i++)
    {

    }
}


int main()
{
    graf g;
    graf_mat g2;
    int n = 7;
    int i, j;
    init_graf(&g, n);
    add_edge(g, 0, 1, 6);
    add_edge(g, 1, 2, 10);
    add_edge(g, 1, 3, 11);
    add_edge(g, 2, 4, 33);
    add_edge(g, 4, 1, 7);
    add_edge(g, 4, 5, 20);
    add_edge(g, 4, 6, 55);
    add_edge(g, 6, 0, 22);
    print_graf(g);
    printf("\n");
    delete_edge(g, 6, 0);
    print_graf(g);
    printf("\n");
    g2 = convert_to_matrix(g, n);
    if(g2.n != 0)
    {
        for(i = 0; i < g2.n; i++) {
            for(j = 0; j < g2.n; j++)
                printf("%d ", g2.mat[i][j]);
            printf("\n");
        }
    }
    int **dist = floyd_warshall(g2);
    printf("\n");
    if( dist != NULL )
    {
        for(i = 0; i < g2.n; i++) {
            for(j = 0; j < g2.n; j++) 
            {
                printf("%d ", dist[i][j]);
            }
            printf("\n");
        }
    }
/*    int *dist2 = (int*) malloc (sizeof(int) * n);
    int *prev = (int*) malloc (sizeof(int) * n);
    dijkstra(g2, dist2, prev, 0);
    printf("\n");
    for(i = 0; i < n; i++)
        printf(" %d -> %d \n", i, dist2[i]);
    printf("\n");
    for(i = 0; i < n; i++)
        printf(" %d -> %d \n", i, prev[i]);
    printf("\n");

   */
    return 0;
}

