#include<stdio.h>
#include<math.h>

int suma(int x,int n)
{
	if(n==0)
		return 1;
	if(n>0)
		return suma(x,n-1)+pow(x,n);
}


int main()
{
	int x,n;
	scanf("%d%d",&x,&n);
	printf("%d\n",suma(x,n));
	return 0;
}