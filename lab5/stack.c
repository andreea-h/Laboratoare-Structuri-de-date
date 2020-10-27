#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct nod 
{
    char val;
    struct nod* next;
} nod;

int isEmpty(nod* cap)
{
    return cap == NULL;
}

void printStack(nod* cap)
{
    nod* p = cap;
    while(p != NULL)
    {
        printf("%c ", p->val);
        p = p->next;
    }
    printf("\n");
}

/* functia peak arata ce se afla in varful stivei fara a scoate vreun 
element de pe stiva 0.5p */
char peak(nod* cap) 
{
	/*nod *aux=cap;
	while(aux->next!=NULL)
	{
		aux=aux->next;
	}*/

	return cap->val;	
}

/* functia push adauga un element pe stiva ->
    se va insera element la inceputul listei 1p*/
void push(nod** cap, char val) 
{
	nod *nou=(nod *)malloc(sizeof(nod));
	nou->val=val;
	if(*cap==NULL)
	{
		nou->next=NULL;
		*cap=nou;
	}
	else
	{
		nou->next=*cap;
		*cap=nou;
	}
}

/* functia pop scoate un element de pe stiva si il intoarce ->
    se va scoate element de la inceputul listei 1p*/
char pop(nod** cap)
{
	nod *aux=*cap;
	char rez=aux->val;
	*cap=(*cap)->next;
	free(aux);
	return rez;
}

/* 
    functia primeste o expresie matematica,
    si verifica daca ordinea parantezelor este corecta
    (se va verifica daca atunci cand se deschide o paranteza
    de un tip se va inchide o paranteza de acelasi timp)
    functia va returna 1 in cazul in care expresia este corecta
    va returna 0 in cazul in care expresia este gresita
    exemplu :
        {()} -> corect
        {(]} -> gresit
    indicatii: se va crea si folosi o stiva pentru verificare
    Stiva se va crea si folosi cu ajutorul functiilor definite anterior
    2p
*/
int checkForBalancedParanthesis(char* expresie)
{
    int n=strlen(expresie);
    int i;
    nod *stack=NULL;
    for(i=0;i<n;i++)
    {
    	if(expresie[i]=='[' || expresie[i]=='{' || expresie[i]=='(' )
    	{
    		push(&stack,expresie[i]);
    		//printStack(stack);
    	}	
    	else
    	{
    		char el=pop(&stack);
    		//printf("%c\n",el);
    		if(expresie[i]==')' && el!='(')
    			return 0;
    		if(expresie[i]=='}' && el!='{')
    			return 0;
    		if(expresie[i]==']' && el!='[')
    			return 0;
    	}
    }
    return 1;
}

/* 
    functia primeste un sir de caractere si afiseaza sirul de caractere
    in ordine inversa.
    Pentru aceasta se va folosi o stiva.
    Stiva se va crea si folosi cu ajutorul functiilor definite anterior
    1p
*/
void reverseOrder(char* inputString)
{
	int n=strlen(inputString);
	int i;
	nod *stack=NULL;
	for(i=0;i<n;i++)
		push(&stack,inputString[i]);
	printStack(stack);
}

/*
    functia primeste o expresie in forma prefixata si 
    afiseaza expresia in forma infixata
    pseudo-cod:
    This algorithm is a non-tail recursive method. 
    1.The reversed input string is completely pushed into a stack. 
	    prefixToInfix(stack) 
    2.IF stack is not empty 
        a. Temp -->pop the stack 
        b. IF temp is a operator 
		    Write a opening parenthesis to output 
		    prefixToInfix(stack) 
		    Write temp to output 
		    prefixToInfix(stack) 
		    Write a closing parenthesis to output 
    c. ELSE IF temp is a space -->prefixToInfix(stack)  
    d. ELSE 
		Write temp to output 
		IF stack.top NOT EQUAL to space -->prefixToInfix(stack)
		
	Exemplu:
	input: *+a-bc/-de+-fgh
	output: (a+b-c)*(d-e)/(f-g+h) 
	2p
*/

int operand(char el)
{
	if((el>='a'&&el<='z')|| (el>='A' && el<='Z'))
		return 1;
	return 0;
}

void prefixInfix(char* expresie)
{
	nod *stack=NULL;
    int n=strlen(expresie);
    for(int i=n-1;i>=0;i--)
    	push(&stack,expresie[i]);
    printStack(stack);
    while(stack!=NULL)
    {
    	char temp=pop(&stack);
    	if(operand(temp)==0)
    	{
    		printf("(");
    		prefixInfix(expresie+1);
    		printf("%c",temp);
    		prefixInfix(expresie+1);
    		printf(")");
    	}
    	else
    		if(temp==' ')
    			prefixInfix(expresie+1);
    	else
    		printf("%c",temp);
    }
}

int main()
{
    nod* stack =  NULL;
    push(&stack, 'a');
    push(&stack, 'b');
    push(&stack, 'c');
    printStack(stack);
    printf("Peak-ul este: %c\n", peak(stack));
    printf("Am scos: %c \n", pop(&stack));
    printStack(stack);
    printf("Am scos: %c \n", pop(&stack));
    printStack(stack);
    printf("Am scos: %c \n", pop(&stack));
    printStack(stack);

    int check = checkForBalancedParanthesis("{((()))}");
    printf("Should be true %d\n", check); // should print 1
    
    check = checkForBalancedParanthesis("{((())}");
    printf("Should be false %d\n", check); // should print 0
    
    check = checkForBalancedParanthesis("{((([])))}");
    printf("Should be TRUE %d\n", check); // should print 0
    
    reverseOrder("WORDS");
    
 //  prefixInfix("*+a-bc/-de+-fgh");
 
    return 0;
}
