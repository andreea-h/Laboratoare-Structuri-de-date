#include<stdio.h>
#include<stdlib.h>

void aloca(int **v,int n)
{
	*v=(int *)calloc(n,sizeof(int));
	/*for(int i=0;i<n;i++)
		*v[i]=0;*/
}

void citire(int *v,int n)
{
	int i;
	for(i=0;i<n;i++)
		scanf("%d",&v[i]);
}

int maxim(int *v,int st,int dr)
{
	if(st==dr)
		return v[st];
	int m=(st+dr)/2;
	int max1=maxim(v,st,m);
	int max2=maxim(v,m+1,dr);
	if(max1>max2)
		return max1;
	else
		return max2;
}

int main()
{
	int *v;
	int nr;
	scanf("%d",&nr);
	aloca(&v,nr);
	citire(v,nr);
	for(int i=0;i<nr;i++)
		printf("%d ",v[i]);
	printf("\n");
	int max=maxim(v,0,nr-1);
	printf("%d\n",max);
	return 0;
}