%{
#include <stdio.h>
int vow=0;
int cons=0;
%}
 
%%
([aeiouAEIOU]) { vow++; }
([a-zA-Z]) { cons++; }
. {;}
%%
 
void main( )
{
	printf("Enter text:\n");
	yylex();
	printf("Number of vowels: %d\n",vow);
	printf("Number of consonants: %d\n",cons);
}

int yywrap()
{
return 1;
}
