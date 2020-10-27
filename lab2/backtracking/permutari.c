#include<stdio.h>
int st[10];
int n;
void afisare()
{
	for(int i=1;i<=n;i++)
		printf("%d ",st[i]);
	printf("\n");
}

int valid(int k)//daca elementul mai apare in stiva
{
	for(int i=1;i<=k-1;i++)
		if(st[k]==st[i])
			return 0;
	return 1;
}

void backtr(int k)
{
	for(int i=1;i<=n;i++)
	{
		st[k]=i;
		if(valid(k)==1)
			if(k==n)
				afisare(n);
			else
				backtr(k+1);
	}
}

int main()
{
	scanf("%d",&n);
	backtr(1);
	return 0;
}