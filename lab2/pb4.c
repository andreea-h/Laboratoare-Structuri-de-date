#include<stdio.h>

void swap(int *x,int *y)
{
	int aux;
	aux=*x;
	*x=*y;
	*y=aux;
}

int partitionare(int *v,int st,int dr,int pivot)
{
	int s=st-1;
	int d=dr;
	while(1)
	{
		while(s<dr && v[++s]<pivot);
		while(d>st && v[--d]>pivot);
		if(s>=d)
			break;
		else
			swap(&v[s],&v[d]);
	}	
	swap(&v[s],&v[dr]);
	return s;
}

void quicksort(int *v,int st,int dr)
{
	if(st>=dr)
		return;
	else
	{
		int m=partitionare(v,st,dr,v[dr]);
		quicksort(v,st,m-1);
		quicksort(v,m+1,dr);
	}
}	

int main()
{
	int v[10],n,i;
	scanf("%d",&n);
	for(i=0;i<n;i++)
		scanf("%d",&v[i]);
	quicksort(v,0,n-1);
	for(i=0;i<n;i++)
		printf("%d ",v[i]);
	printf("\n");
		
	return 0;
}