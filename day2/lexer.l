%{
	#include "tokens.h"
%}

%%
\n	{
		Token token;
		token.type = NEWLINE;
		tokens.push_back(token);
		return NEWLINE;
	}
[0-9]+	{
		Token token;
		token.type = NUMBER;
		token.data = atoi(yytext);
		tokens.push_back(token);
		return NUMBER;
	}
\ 	{}
<<EOF>> {return 0;}
%%

int yywrap() {
	return 1;
}
