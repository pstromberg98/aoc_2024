#include <iostream>
#include <array>
#include <unordered_map>
#include "input.h"

extern int yylex();
extern int yyparse();

std::vector<intpair> pairs;
std::vector<int> left;
std::vector<int> right;

int main() {
	yyparse();
	for (auto l : left) {
		std::cout << l << std::endl;
	}
	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());
	std::cout << "after" << std::endl;
	for (auto l : left) {
		std::cout << l << std::endl;
	}


	std::vector<int> distances;
	std::unordered_map<int, int> repeats;
	for (auto r : right) {
		repeats[r] = 0;
	}

	int sum = 0;
	for (int i = 0; i < left.size(); i++) {
		int l = left[i];
		int r = right[i];

		int distance = abs(l - r);
		sum += distance;
		distances.push_back(distance);
	}

	std::cout << "sum: " << sum << std::endl;
	return 0;
}
