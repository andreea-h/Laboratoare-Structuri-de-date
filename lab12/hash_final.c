#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define H 13

typedef struct nod { // un nod din listă
 char * cuv; // adresa unui cuvânt
 int nr; // număr de apariţii cuvânt
 struct nod * leg; // legatura la nodul următor
} nod;

typedef nod * Map [H]; // tipul dicţionar 

int hash (char * s) {
    int i, sum = 0;
    for (i = 0; i < strlen(s); i++)
        sum = sum + (i + 1) * s[i];
    return sum % H;
} 

/*
    Funcţia de iniţializare a tabelei de dispersie, care iniţializează cu NULL
    fiecare element din tabela de dispersie 
    1P
*/
void initD (Map d)
{
	int i;
	for(i=0;i<H;i++)
	{
		d[i]=NULL;
	}
}

/*
    Funcţia de afişare a tabelei de dispersie – pentru fiecare cuvânt din
    text, se afişează numărul de apariţii al cuvântului din text 
    1P
*/
void printD (Map d) 
{	
	int i;
	nod *aux;
	for(i=0;i<H;i++)
	{
		aux=d[i];
		while(aux!=NULL)
		{
			printf("Cuvantul %s apare de %iori\n",aux->cuv,aux->nr);
			aux=aux->leg;
		}
	}
} 

/*
    Funcţia de căutare a unui cuvânt în tabela de dispersie – poziţia cheii c
    în tabela de dispersie este aflată folosind funcţia de dispersie 
    2P
*/
nod * cautD (Map d, char * c) 
{
	int i=hash(c);
	nod *aux=d[i];
	while(aux!=NULL)
	{
		if(strcmp(aux->cuv,c)==0)
			return aux;
		aux=aux->leg;
	}
	return NULL;
}

/*
    Funcţia de adăugare a unei perechi cheie–valoare în tabela de
    dispersie
    – poziţia cheii c în tabela de dispersie este aflată folosind funcţia de
    dispersie
    – dacă cheia c există în nodul p
    	– modifică valoarea asociată cheii c
    – dacă cheia c nu există în tabela de dispersie
    	– se creează un nod nou
    	– se completează nodul cu cheia c şi valoarea nr
    	– se adaugă nodul la începutul listei 
    2P
    
*/
void putD (Map d, char * c, int nr) 
{
	int i=hash(c);
	if(d[i]==NULL)
	{
		d[i]=(nod*)malloc(sizeof(nod));
		d[i]->cuv=strdup(c);
		d[i]->nr=nr;
		d[i]->leg=NULL;
	}
	else
	{
		nod *aux=cautD(d,c);
		if(aux!=NULL)
			aux->nr=nr;
		else
		{
			aux=d[i];
			while(aux->leg!=NULL)
				aux=aux->leg;
			nod *p=malloc(sizeof(nod));
			p->cuv=strdup(c);
			p->nr=nr;
			p->leg=NULL;
			aux->leg=p;
		}
	}
}

/*
    Funcţia de extragere a valorii asociate unei chei date
    2P
*/ //numarul de aparitii pentru un cuvant
int getD (Map d, char * c) 
{
	nod *aux=cautD(d,c);
	if(aux!=NULL)
		return aux->nr;	
	return 0;
} 

/*
	Functia sterge o pereche cheie-valoare din tabela de dispersie
	- pozitia cheii c se calculeaza folosind functia de dispersie
	- se sterge elementul corespunzator 
	2P
*/
void removeD (Map d, char * c) 
{
	int index=hash(c);
	nod *p=d[index],*q;
	if(d[index]==NULL)
		return;
	if(strcmp(p->cuv,c)==0)
	{
		q=d[index];
		d[index]=d[index]->leg;
		free(q);
	}
	else
	{
		while(p!=NULL)
		{
			q=p;
			p=p->leg;
			if(strcmp(p->cuv,c)==0)
				break;
		}
		if(p->leg==NULL)
		{
			q->leg=NULL;
			free(p);
		}
		else
		{
			nod *aux=p;
			p=p->leg;
			q->leg=p;
			free(aux);
		}
	}
}

int main()
{
    char numef[20], buf[128], * q;
    Map dc;
    int nra;
    FILE *f;
    f = fopen ("test.txt", "r");
    initD (dc);
    while ( fscanf ( f, "%s", buf) > 0) {
        q = strdup (buf);
        // creare adresă pentru şirul citit
        nra = getD (dc, q); 
        // calculează număr de apariţii cuvânt
        if (nra == 0) // dacă e prima apariţie
            putD (dc, q, 1);
        // pune cuvântul în tabela de dispersie
        else // dacă nu e prima apariţie
            putD (dc, q, nra + 1);  
        // modifică numărul de apariţii ale cuvântului
    }
    printD (dc); // afişare tabela de dispersie 
  	removeD (dc, "buna");
    printD (dc);
    printf("\n");
    removeD (dc, "ingerii");
    printD (dc);
    return 0;
}

