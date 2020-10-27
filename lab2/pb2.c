#include<stdio.h>

int cauta(int *v,int st,int dr,int x)
{
	int m=(st+dr)/2;
	if(v[m]==x)
		return m;
	else
	{
		if(v[m]>x)
			return cauta(v,st,m,x);
		else
			return cauta(v,m+1,dr,x);
	}
}

int main()
{
	int v[10];
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&v[i]);
	int x;
	scanf("%d",&x);
	int rez=cauta(v,0,n-1,x);
	printf("%d\n",rez);

	return 0;
}