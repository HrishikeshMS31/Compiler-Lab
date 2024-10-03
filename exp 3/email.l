%{
#include <stdio.h>
int flag=0;
%}
 
%%
([a-z0-9]+"@gmail.com\n")|([a-zA-Z0-9]+"@yahoo.com\n") { flag=1;}
. { ;}
%%
 
void main( )
{
	yylex();
	if (flag==0)
		printf("Invalid email\n");
	else
		printf("Valid email\n");
}

int yywrap()
{
return 1;
}
