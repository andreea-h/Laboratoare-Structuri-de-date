#include<stdio.h>

typedef int stiva[100]; 
int n;
stiva st; 

void init(int k)
{
	st[k]=0;
}

int succesor(int k) 
{
	if (st[k]<st[k-1]+1)
    {	
	st[k]=st[k]+1; return 1;
}else return 0;}

int valid(int k) 
{
	return 1;
}

int solutie(int k) {return k==n;}

void tipar()
{
	for(int i=1;i<=n;i++)
	  printf("%d ",st[i]); 
	printf("\n");
}

void bt(int k)
{	
	init(k); 
	while(succesor(k)) 
		if(valid(k)) 
			if(solutie(k)) tipar();
			 else bt(k+1);
}

int main() 
{
	scanf("%d",&n);
	bt(1);
	return 0;
}