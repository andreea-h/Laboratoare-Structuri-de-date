#include<stdio.h>

int putere(int a,int b)
{
	if(b==1)
		return a;
	if(b>=0)
		return a*putere(a,b-1);
}

int main()
{
	//printf("%d\n",putere(2,3));
	int x,y;
	scanf("%d%d",&x,&y);
	printf("%d\n",putere(x,y));
	return 0;
}