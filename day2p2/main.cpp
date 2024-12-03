#include <iostream>
#include <map>
#include <algorithm>
#include "tokens.h"

struct Range {
	int start;
	int end;
};

extern int yylex();
typedef unsigned int uint;
typedef std::vector<int> Report;
typedef std::pair<int, Report> ErrReport;

std::vector<ErrReport> erreports;

std::vector<Token> tokens;

bool can_fix(Report& report, std::vector<Range>& ranges);
void generate_ranges(Report report, std::vector<Range>& ranges);

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
	for (int i = 0; i < reports.size(); i++) {
		auto report = reports[i];
		std::vector<Range> ranges;
		generate_ranges(report, ranges);

		if (ranges.size() == 1) {
			sum++;
		} else if(can_fix(report, ranges)) {
			sum++;
		}
	}

	std::cout << "result: " << sum << std::endl;

	return 0;
}

bool can_fix(Report& report, std::vector<Range>& ranges) {
	for (int i = 0; i < ranges.size() * 2; i++) {
		int tidx = 0;
		int ridx = i / 2;
		if (i == 0 || i % 2 == 0) {
			tidx = ranges[ridx].start;
		} else {
			tidx = ranges[ridx].end;
		}

		Report clone(report);
		auto start = clone.begin() + tidx;
		auto end = clone.begin() + tidx + 1;

		clone.erase(start, end);
	
		std::vector<Range> nranges;
		generate_ranges(clone, nranges);
		
		if (nranges.size() == 1) {
			return true;
		}
	}

	return false;
}

void generate_ranges(Report report, std::vector<Range>& ranges) {
	Range crange;
	crange.start = 0;

	bool sincrease = report[1] > report[0];

	for (int i = 0; i < report.size() - 1; i++) {
		int current = report[i];
		int next = report[i + 1];

		int diff = std::abs(next - current);
		bool increasing = next > current;
		if ((increasing != sincrease) || diff < 1 || diff > 3) {
			ranges.push_back(crange);
			crange = Range{
				.start = i + 1,
				.end = i + 1,
			};
			continue;
		}
		
		crange.end = i + 1;
	}

	ranges.push_back(crange);
}
