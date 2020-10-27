#include<stdio.h>

//numararea valorilor din vectorul a egale cu b
void cauta(int *a,int dr,int b,int *nr)
{
	if(a[dr]==b)
		*nr=*nr+1;
	if(dr>1)
		cauta(a,dr-1,b,nr);
}

int main()
{
	int v[]={10,20,30,40,30,50,30,90,23,100,30};
	int n=11;
	int nr=30;
	int rez=0;
	cauta(v,n-1,nr,&rez);
	printf("%d\n",rez);
	return 0;
}