#include <iostream>
#include "tokens.h"

extern int yylex();
typedef unsigned int uint;
typedef std::vector<int> Report;

std::vector<Token> tokens;

bool is_safe(Report report);

int main() {
	int t = yylex();
	std::vector<Report> reports;
	Report creport;
	while (t != 0) {
		Token token = tokens[tokens.size() - 1];

		if (t == NUMBER) {
			creport.push_back(token.data);
		} else {
			reports.push_back(creport);
			creport.clear();
		}

		t = yylex();
	}

	int sum = 0;
	for (auto report : reports) {
		bool safe = is_safe(report);
		if (safe) {
			sum++;
		}
	}

	std::cout << "result: " << sum << std::endl;

	return 0;
}

bool is_safe(Report report) {
	bool sincrease = report[1] > report[0];
	for (int i = 0; i < report.size() - 1; i++) {
		int current = report[i];
		int next = report[i + 1];

		bool increasing = next > current;
		if (increasing != sincrease) {
			return false;	
		}

		int diff = std::abs(next - current);
		
		if (diff < 1 || diff > 3) {
			return false;
		}
	}

	return true;
}
