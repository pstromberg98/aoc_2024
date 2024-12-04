%{
	#include <iostream>
	#include <string>
	#include <regex>
	#include "main.h"
	#include "block.h"
	#include "parser.tab.hpp"
%}

%%
don\'t\(\)		{
				return DONT;
			}
do\(\)			{
				return DO;
			}
mul\([0-9]+,[0-9]+\) 	{
				std::string mul(yytext);		
				std::smatch matches;

				std::regex digits("[0-9]+");
				std::vector<int> operands;
				while(std::regex_search(mul, matches, digits)) {
					int operand = stoi(matches[0]);
					operands.push_back(operand);
					mul = matches.suffix();
				}

				yylval.product = operands[0] * operands[1];

				return MUL;
			}

. 			{}
\n			{}
%%

int yywrap() {
	return 1;
}
