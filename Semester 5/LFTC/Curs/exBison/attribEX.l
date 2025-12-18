%{
#include "attribEX.tab.h" /* token type definitions from .y file */
%}

digit [0-9]
%%
{digit}+	{
        		yylval.intValue = atoi(yytext);                  
				return INTEGER;                
		}
{digit}+"."{digit}*    {
                      		yylval.dblValue = atof(yytext);
							return REAL;                        
			    }
[\n]		return '\n';

%%
int yywrap() {
  return 1; /* tell scanner no further files need to be processed */
}
