#include <iostream>
#include <array>
#include <unordered_map>
#include "input.h"

extern int yylex();
extern int yyparse();

std::vector<uintpair> pairs;
std::vector<uint> left;
std::vector<uint> right;

int main() {
	yyparse();

	std::vector<uint> distances;
	std::unordered_map<uint, uint> repeats;
	for (auto r : right) {
		if (repeats.find(r) != repeats.end()) {
			repeats[r]++; 
		} else {
			repeats[r] = 1;
		}
	}

	uint sum = 0;
	for (int i = 0; i < left.size(); i++) {
		uint l = left[i];

		if (repeats.find(l) != repeats.end()) {
			int score = l * repeats[l];
			sum += score;
		}
	}

	std::cout << "sum: " << sum << std::endl;
	return 0;
}
