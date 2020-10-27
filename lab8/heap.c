#include <stdio.h>
#include<stdlib.h>
typedef struct heap
{
    char *v;
    int n;
} heap;

/*
    Un heap este reprezentat printr-un array (v) in care numerotarea pozitiilor
    incepe de la 1. Pentru a accesa parintele, respectiv fiul din stanga si pe cel din
    dreapta ai nodului de pe pozitia i se folosesc urmatoarele formule:
    Parent(i) = v[i/2]
    Left(i) = v[2 * i]
    Right(i) = v[2 * i + 1]
    Intr-un max-heap fiecare nod trebuie sa fie mai mare decat ambii fii si
    ambii subarbori trebuie sa fie max-heapuri.
*/
void init_heap(heap* h) 
{
   	h->v=(char*)malloc(20*sizeof(char));
   	h->n=1;
}

// adauga un elemen t in max−heap ( 1 . 5 p )
/*
    Explicatii:
    Valoarea care se doreste sa fie adaugata la heap va fi inserata la sfarsitul vectorului.
    Inserarea ei va pastra prima proprietate a unui heap (cea care spune ca
    este un arbore aproape complet, iar ultimul nivel e completat de la stanga la
    dreapta), dar nu o va pastra pe cea de a doua care spune ca parintele trebuie
    sa fie mai mare decat ambii fii, iar subarorii sai trebuie sa fie tot max-heapuri.
    Pentru a reface heapul, se va implementa o functie recursiva moveUp care
    porneste de la noua valoare si o compara cu parintele sau. Daca aceasta e mai
    mare decat parintele, atunci va intershimba cele 2 valori si va repeta procesul
    pentru nodul parinte si parintele acestuia, pana cand nu mai e nevoie de
    interchimbare.
*/
void swap(char *a,char *b)
{
	char temp=*a;
	*a=*b;
	*b=temp;
}

void add(heap *h, char c)
{
    int i;
    i=h->n;
    h->v[i]=c;
    h->n=h->n+1;
    while(i>1&&h->v[i/2]<h->v[i])
    {
    	swap(&h->v[i],&h->v[i/2]);
    	i=i/2;
    }
}

void moveUp(heap h, int index)
{
    
}

// returneaza si elimina maximul dintr−un max−heap ( 1 . 5 p )
/*  Cand se elimina valoarea maxima dintr-un max-heap se va sterge valoarea de pe
    prima pozitie (radacina arborelui), dar vor ramane doua heapuri. Este nevoie sa
    se reuneasca cele doua heapuri intr-unul singur. Valoarea de pe ultima pozitie
    se va pune pe prima pozitie, iar apoi se va raface ordinea valorilor astfel incat
    acestea sa indeplineasca in continuare proprietatea de max-heap.
    Pentru aceasta se va face operatia inversa de la inserare, adica se va porni
    de la radacina, iar daca unul dintre fii este mai mare decat radacina, aceasta se
    va inlocui cu valoarea maxima dintre cei doi fii. Procesul se va repeta recursiv
    pentru fiul cu a carui valoare s-a facut interchimbarea, pana cand nu mai este
    nevoie de interschimbari (numim functia moveDown).
*/

void heapify(heap h,int i)
{
	int st,dr,m,aux;
	st=2*i;
	dr=st+1;
	if(st<=h.n-1 && h.v[st]>h.v[i])
		m=st;
	else
		m=i;
	if(dr<=h.n-1 && h.v[dr]>h.v[m])
		m=dr;
	if(m!=i)
	{
		swap(&(h.v[i]),&(h.v[m]));
		heapify(h,m);
	}
}

void moveDown(heap *h, int index);
char removeMax(heap *h)
{
    h->v[1]=h->v[h->n];
    char temp=h->v[1];
    h->n--;
    moveDown(h,1);
    return temp;
}

void moveDown(heap *h, int index)
{
    int st,dr,m;
    st=2*index;
    dr=st+1;
    if(st<=h->n-1 && h->v[st]<h->v[index])
	{
		m=st;
	}
	else
		m=index;
	if(dr<=h->n-1 && h->v[dr]<h->v[m])
	{
		m=dr;
	}
	if(m!=index)
	{
		swap(&(h->v[index]),&(h->v[m]));
		moveDown(h,m);
	}
}

// a=vectorul nesortat , n = lungimea vectorului (2 p )
/*
    v ← createHeapFrom(a, n)
    i ← n
    for i > 1 do
        swap(v[1], v[i]
        moveDown(v[1])
    end for
*/

void makeheap(heap h)
{
	int i;
	for(i=h.n/2;i>=1;i--)
		heapify(h,i);
}


void heap_sort(char *a, int n)
{
    int i,t;
    heap h;
    init_heap(&h);
    for(i=0;i<n;i++)
    	add(&h,a[i]);
    /*for(i=h.n;i>=1;i--)
    {
    	t=h.v[1];
    	h.v[1]=h.v[h.n];
    	h.v[h.n]=t;
    	h.n--;
    	heapify(h,1);
    }
    for(i=1;i<n;i++)
    	a[i]=h.v[i];*/
    char temp=removeMax(&h);

}

/*
(2p) Sa se defineasca structurile de date:
    Node - contine un caracter (char), frecventa de aparitie a caracterului (int) si
    doi pointeri catre fiul din stanga si cel din dreapta.
    PriorityQueue - contine un vector de Node si lungimea vectorului
    Pair - contine un caracter (char) si un string (char*), unde stringul reprezinta
    codificarea binara a caracterului
    Definiti operatiile:
    // creeaza un nod nou care contine caracterul ch ,
    // frecventa fr si are fii left si right
    Node* make ( char ch , int fr , Node* left , Node* right) ;
    // adauga nodul n la coada cu prioritati pq (1 p )
    void add ( PriorityQueue *pq , Node *n ) ;
    // returneaza si elimina elementul cu prioritatea maxima
    // din coada cu prioritati (1 p )
    Node* remove ( PriorityQueue *pq ) ;
    pentru o coada cu prioritati care sa contina elemente de tip Node *, prioritatea
    fiind data de frecventa caracterului.
    Testati functiile adaugand caracterele urmatoare impreuna cu frecventele  
    corespunzatoare:
    chars = {'a','b','c','d','e','f’};
    freqs = {36,14,12,10,20,8};
    Apoi eliminati primele 3 elemente din coada cu prioritati
*/


/*
    Sa se defineasca functiile buildHuffman, encode si decode
*/

/*
    // l = lungimea, chars = caracterele,
    // freqs = frecventele caracterelor
    // construieste arborele Huffman corespunzator (1 p )

Codificarea Huffman consta in construirea unui arbore bazandu-se pe caracterele
ce apar intr-un text si pe frecventa de aparitie a acestora. 
Caracterele se introduc in arbore in ordinea crescatoare a frecventei de
aparitie. Se foloseste o coada de prioritati pentru a pastra nodurile ordonate.

    Pseudo cod build Huffman: 
    buildHuffman(characters, frequencies)
    creeaza un nod frunza pentru fiecare caracter din text
    while exista mai mult de un nod in coada cu prioritati do
        extrage cele doua noduri cu frecventele de aparitie cele mai mici
        creeaza un nou nod intermediar avand cele 2 noduri extrase drept fii, si a
        carui frecventa sa fie suma celor doua frecvente
        adauga noul nod in coada cu prioritati
    end while
    nodul ramas este radacina arborelui Huffman complet
    Node* buildHuffman (char* chars, int* freqs, int l);
*/

/*
Se parcurge arborele de la radacina spre frunze si fiecarei muchii i se asociaza
o valoare 0 sau 1. De exemplu, muchiei ce duce la fiul stang i se asociaza valoarea
0, iar celei care duce la fiul drept i se asociaza valoarea 1. Conventia se pastreaza
pentru intreg arborele. La finalul parcurgerii, fiecare nod va avea asociat un
cod Huffman. Dupa aceasta parcurgere fiecarui caracter ii va fi asociat un cod,
aceasta mapare va fi retinuta, pe baza ei codificandu-se textul.
    // text = textul initial ,
    // codes = codurile Huffman rezultate din arbore
    // codifica un text dat (1 p)
    char* encode (char* text ,Pair* code s )
*/

/*
Pentru a decodifica un text care a fost compresat folosind un arbore Huffman
este nevoie ca arborele sa fi fost salvat, altfel nu se poate face decodificarea.
Decodificarea se face parcurgand textul codificat cifra cu cifra si in functie de
cifra citita se va parcurge arborele, daca se intalneste un 0 se merge pe ramura
stanga, iar daca se intalneste un 1, pe ramura dreapta. In momentul in care
se ajunge la o frunza, inseamna ca un caracter a fost decodificat si urmeaza un
altul.
    // huffTree = arborele Huffman rezultat de la functia buildHuffman,
    // encodedText = textul codificat cu functia anterioara
    // decodifica textul dat avand arborele (1 p)
    char∗ decode ( Node∗ huffTree , char ∗ encodedText) ;
*/

/*
    Testati functiile astfel:
    Folosind exemplul de la problema anterioara generat si arborele Huffman corespunzator.
    Generati codurile Huffman ale caracterelor introduse in arbore
    (trebuie sa rezulte un vector de perechi: caracter-codificare. De exemplu: a -
    ’001’, b = ’1101’ etc.
    Codificati urmatorul text folosind lista de coduri rezultata anterior: ”abaaefddeabaaceda”.
    Decodificati textul returnat de apelul functiei encode pe textul anterior.
*/


void printHeap(heap *h)
{
	for (int i=1;i<h->n;i++)
		printf("%c ",h->v[i]);
}

int main()
{
    heap h;
    init_heap(&h);
    add(&h,'g');
    add(&h,'m');
    add(&h,'b');
    add(&h,'c');
    add(&h,'v');
    add(&h,'f') ;
    add(&h,'i') ;
    add(&h,'a') ;
    printHeap(&h);
    char m;
    m = removeMax(&h);
    printf("%c\n", m) ;
    printHeap(&h);
    printf("\n");
    m = removeMax(&h) ;
    printf("%c \n" , m) ;
    printHeap(&h);
    printf("\n");
    m = removeMax(&h) ;
    printf("%c \n", m) ;
    printHeap(&h);
    printf("\n");
    heap_sort("cpalstmi", 8);

    return 0;
}


