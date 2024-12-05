#include <iostream>
#include <regex>
#include <cstdio>
#include <sstream>
#include <cmath>
#include <iterator>

struct Coord {
	int x;
	int y;
};

int coords_to_index(int x, int y);
Coord index_to_coord(int index);
std::string char_at(int x, int y);

int w = 0;
int h = 0;
std::string input;

int main() {
	std::stringstream inputs;
	std::string line;
	while(std::getline(std::cin, line)) {
		if (w == 0) {
			w = line.size();
		}
		inputs << line;
		h++;
	}

	std::smatch match;
	input = inputs.str();
	std::regex r("A");

	int count = 0;
	int lastpos = 0;
	std::vector<int> matchPositions;

	std::regex_iterator<std::string::iterator> rend;
	std::regex_iterator<std::string::iterator> a (input.begin(), input.end(), r);

	while (a != rend) {
		matchPositions.push_back(a->position());
		a++;
	}

	int sum = 0;
	for (auto xidx : matchPositions) {
		Coord coord = index_to_coord(xidx);
		auto br = char_at(coord.x + 1, coord.y + 1);
		auto tl = char_at(coord.x - 1, coord.y - 1);

		auto tr = char_at(coord.x + 1, coord.y - 1);
		auto bl = char_at(coord.x - 1, coord.y + 1);

		std::string left = br + tl;
		std::string right = bl + tr;

		bool leftm = left == "SM" || left == "MS";
		bool rightm = right == "SM" || right == "MS";

		if (rightm && leftm) {
			sum++;
		}
	}

	return 0;
}

std::string char_at(int x, int y) {
	if (x < 0 || x >= w) {
		return "0";
	}

	if (y < 0 || y >= h) {
		return "0";
	}
	char c = input[coords_to_index(x, y)];
	std::string s;
	s += c;
	return s;
}

Coord index_to_coord(int index) {
	int y = floor(index / w);
	int x = index % w;

	return Coord{
		.x = x,
		.y = y,
	};
}

int coords_to_index(int x, int y) {
	return (y * h) + x;
}
