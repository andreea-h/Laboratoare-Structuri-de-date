#include<stdio.h>

int cmmdc(int a,int b)
{
	if(a==b)
		return a;
	if(a>b)
		return cmmdc(a-b,b);
	else
		return cmmdc(a,b-a);
}

int main()
{
	int x,y;
	scanf("%d%d",&x,&y);
	printf("%d\n",cmmdc(x,y));
	return 0;
}
