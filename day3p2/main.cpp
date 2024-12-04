#include <iostream>
#include "main.h"
#include "block.h"

extern int yylex();
extern int yyparse();
extern int yydebug;
int sum = 0;

std::vector<Block> blocks;

int main() {
	// yydebug = 1;
	yyparse();
	std::cout << "blocks: " << blocks.size() << std::endl;
	int sum = 0;
	for (auto block : blocks) {
		if (!block.included) {
			continue;
		}

		for (auto n : *(block.list)) {
			sum += n;
		}
	}
	std::cout << "sum: " << sum << std::endl;
	return 0;
}
