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
		for (auto level : report) {
			std::cout << level << " ";
		}


		bool safe = is_safe(report);
		if (safe) {
			sum++;
		}
	}

	return 0;
}

bool is_safe(Report report) {
	bool sincrease = report[1] > report[0];
	for (int i = 1; i < report.size() - 1; i++) {
		int prev = report[i - 1];
		int current = report[i];
		int next = report[i + 1];

		bool increasing = next > current;
		if (increasing != sincrease) {
			return false;	
		}

		int leftdiff = std::abs(prev - current);
		int rightdiff = std::abs(next - current);
		
		if (leftdiff < 1 || leftdiff > 3 || rightdiff < 1 || rightdiff > 3) {
			return false;
		}
	}

	return true;
}
