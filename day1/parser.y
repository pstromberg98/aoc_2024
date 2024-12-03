%{
	#include <iostream>
	#include <vector>
	#include <utility>
	#include "input.h"

	extern int yylex();
	
	int yyerror(char* msg);
%}

%union {
	unsigned int number;
}

%token <number> NUMBER

%%
program:
	pair program
	|
	;

pair:
	NUMBER NUMBER {
		std::pair<int, int> p($1, $2);
		
		pairs.push_back(p);
		left.push_back($1);
		right.push_back($2);
	}
	;
%%

int yywrap() {
	return 1;
}

int yyerror(char* err) {
	std::cout << err << std::endl;
	return 0;
}
