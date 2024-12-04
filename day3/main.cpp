#include <iostream>
#include "main.h"

extern int yylex();
int sum = 0;

int main() {
	yylex();
	std::cout << "sum: " << sum << std::endl;
	return 0;
}
