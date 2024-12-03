%{
	#include "parser.tab.hpp"

%}

%%
[0-9]+		{
			yylval.number = atoi(yytext);
			return NUMBER;
		}
%%

int yywrap() {
	return 1;
}
