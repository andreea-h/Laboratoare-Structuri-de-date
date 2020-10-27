#include<stdio.h>

void impare(int *v,int st,int dr,int *imp)
{
	if(st==dr)
		return;
	if(v[dr]%2==1)
		*imp=*imp+1;
	impare(v,st,dr-1,imp);
}

int main()
{
	int v[]={10,2,3,5,6,7,1,2,13,11,15};
	int st=0;
	int dr=10;
	int rez=0;
	impare(v,st,dr,&rez);
	printf("%d\n",rez);
	return 0;
}