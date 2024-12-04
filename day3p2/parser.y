%{
	#include <iostream>
	#include "block.h"

	int yyerror(char* err);
	extern int yylex();
%}

%union {
	std::vector<int>* mullist;
	int product;
	struct Block block;
}

%token DO
%token DONT
%token <product> MUL

%type <mullist> mul_block
%type <block> block
%type <block> do_block
%type <block> dont_block

%%
	input:
		blocks
		;

	blocks:
		block 		{blocks.push_back($1);}
		|block blocks	{blocks.push_back($1);}
		;
	block:
		dont_block	{}
		|do_block 	{}
		|mul_block 	{
					$$ = Block{
						.included = true,
						.list = $1,
					};
				}
		;

	mul_block:
		MUL		{
					auto list = new std::vector<int>();
					list->push_back($1);
					$$ = list;
				}
		|MUL mul_block  {
					$2->push_back($1);
					$$ = $2;
				}
		;

	dont_block:
		DONT mul_block 	{
					$$ = Block{
						.included = false,
						.list = $2
					};
				}
		;

	do_block:
		DO
		|DO mul_block 	{
					$$ = Block{
						.included = true,
						.list = $2
					};
				}
		;
%%

int yyerror(char* err) {
	std::cout << err << std::endl;
}

int yywrap() {
	return 1;
}
