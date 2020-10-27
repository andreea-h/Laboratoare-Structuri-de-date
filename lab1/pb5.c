#include<stdio.h>

int M(int n);
int F(int n)
{
	if(n==0)
		return 1;
	if(n>0)
		return n-M(F(n-1));
}

int M(int n)
{
	if(n==0)
		return 0;
	if(n>0)
		return n-F(M(n-1));
}

int main()
{
	int x;
	scanf("%d",&x);
	int i;
	printf("%d\n",F(x));
	printf("%d\n",M(x));
	
	return 0;
}