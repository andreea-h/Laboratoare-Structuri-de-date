#include<stdio.h>

//suma primelor n numere naturale
int suma(int n)
{
	if(n==1)
		return 1;
	else if(n>0)
		return n+suma(n-1);
}

int main()
{
	int a;
	scanf("%d",&a);
	printf("%d\n",suma(a));
	return 0;
}