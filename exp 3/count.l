%{
#include <stdio.h>
int words=0;
int chars=0;
int lines=0;
%}
 
%%
([a-zA-Z0-9])+ { words++; 
chars+=yyleng;}
([\n])+ { lines++; }
. {chars++;}
%%
 
void main( )
{
printf("Enter text:\n");
yylex();
printf("Number of words: %d\n",words);
printf("Number of lines: %d\n",lines);
printf("Number of characters: %d\n",chars);
}

int yywrap()
{
return 1;
}

