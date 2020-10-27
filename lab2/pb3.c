#include<stdio.h>
#include<stdlib.h>
int n;
int *v;//vectorul de sortat
void MergeSort();
void recMergeSort(int *w,int st,int dr);
void merge(int *w,int st,int mj,int dr);

int main()
{
	scanf("%d",&n);//nr de elemente din vector
	v=(int *)malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
		scanf("%d",&v[i]);
	MergeSort();//se sorteaza vectorul
	for(int i=0;i<n;i++)
		printf("%d ",v[i]);
	printf("\n");
	return 0;
}

void MergeSort()
{
	int *w=(int *)malloc(n*sizeof(int));//in w se va obtine vectorul sortat
	recMergeSort(w,0,n-1);
}

void recMergeSort(int *w,int st,int dr)
{
	if(st==dr)
		return;//nu are sens sortarea
	else
	{
		int m=(st+dr)/2;
		recMergeSort(w,st,m);//se sorteaza jum inferioara
		recMergeSort(w,m+1,dr);//se sorteaza jum superioara
		merge(w,st,m+1,dr);//se interclaseaza jumatarile
	}
}

void merge(int *w,int s,int m,int d)//m este indexul de inceput pentru cea de-a doua jumatate
{
	int j=0;
	int st=s;
	int mj=m-1;
	int nr=d-s+1;
	while(s<=mj && m<=d)
		if(v[s]<v[m])
			w[j++]=v[s++];
		else
			w[j++]=v[m++];
	while(s<=mj)
		w[j++]=v[s++];
	while(m<=d)
		w[j++]=v[m++];
	for(j=0;j<nr;j++)
		v[st+j]=w[j];
}