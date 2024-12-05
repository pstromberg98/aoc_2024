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
bool crawl(Coord from, int xdiff, int ydiff);

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
	std::regex r("X");

	int count = 0;
	int lastpos = 0;
	std::vector<int> matchPositions;

	std::regex_iterator<std::string::iterator> rend;
	std::regex_iterator<std::string::iterator> a (input.begin(), input.end(), r);

	while (a != rend) {
		matchPositions.push_back(a->position());
		std::cout << " [" << a->position() << "]";
		a++;
	}

	/*
	while(regex_search(input, match, r)) {
		input = match.suffix();
		std::cout << match.position() << std::endl;

		int pos = pos + (match.position() - 1);
		matchPositions.push_back(pos);

		lastpos = pos;
		count++;
	}
	*/

	int sum = 0;
	for (auto xidx : matchPositions) {
		Coord coord = index_to_coord(xidx);
		for (int y = -1; y <= 1; y++) {
			for (int x = -1; x <= 1; x++) {
				if (x == 0 && y == 0) {
					continue;
				}

				std::cout << "crawling" << std::endl;

				if (crawl(coord, x, y)) {
					sum++;
				}
			}
		}
	}

	std::cout << "x count: " << matchPositions.size() << std::endl;
	std::cout << "w: " << w << std::endl;
	std::cout << "h: " << h << std::endl;
	std::cout << "sum: " << sum << std::endl;
	return 0;
}

bool crawl(Coord from, int xdiff, int ydiff) {
	int x = from.x;
	int y = from.y;

	std::string m = "X";

	for (int i = 1; i < 4; i++) {
		x += xdiff;
		y += ydiff;

		if (x < 0 || x >= w) {
			break;
		}

		if (y < 0 || y >= h) {
			break;
		}

		int idx = coords_to_index(x, y);
		m += input[idx];
	}


	if (m == "XMAS") {
		std::cout << "xdiff: " << xdiff << std::endl;
		std::cout << "ydiff: " << ydiff << std::endl;
		return true;
	}

	return false;
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
