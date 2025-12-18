%{
#include <stdio.h>
extern int yylex(); /* lexical analyzer generated from lex.l */
extern char *yytext; /* last token, defined in lex.l  */

int yyerror(const char* s);
%}

%union {  
	int    intValue;  
	double dblValue;
}

%token <intValue> INTEGER
%token <dblValue> REAL

%%

input :  /* secv. vida */
           | input line
           ;
line :   INTEGER '\n'      {printf("integer: %d\n", $1);}         	
		| REAL    '\n'  {printf("real: %f \n", $1);}  
	;
%%

int yyerror(char const *s)
{
       printf("syntax error\n");
}

int main()
{
  if(0==yyparse()) printf("\nResult yyparse OK\n");
  return 0;
}