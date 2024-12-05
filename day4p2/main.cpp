#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <cstdio>

typedef std::pair<int, int> Coords;

Coords cursor_to_coords(int cursor, int w, int h);
Coords merge(Coords c1, Coords c2);

int distance(Coords c1, Coords c2);
int coords_to_index(Coords coords, int w);

void print_state(std::string input, std::vector<Coords> coords, int w, int h);

std::string diagonal(std::string input, int w, int h, bool right=true);
std::string vertical(std::string input, int w, int h);
int exhaustive_search(std::string input, std::regex reg);

int main() {
	std::stringstream os;
	int w = 0;
	int h = 0;
	for (std::string line; std::getline(std::cin, line);) {
		if (w == 0) {
			w = line.size();
		}
        	os << line;
		std::cout << line << std::endl;
		h++;
    	}

	std::regex r("XMAS");
	std::regex b("SAMX");

	std::string s = os.str();
	std::string sr = std::string(s.rbegin(), s.rend());

	std::string rdiagonal = diagonal(s, w, h);
	std::string rdiagonalReversed = std::string(rdiagonal.rbegin(), rdiagonal.rend());
	std::string ldiagonal = diagonal(s, w, h, false);
	std::string ldiagonalReversed = std::string(ldiagonal.rbegin(), ldiagonal.rend());
	std::string v = vertical(s, w, h);
	std::string vr = std::string(v.rbegin(), v.rend());

	int linearcount = exhaustive_search(s, r) + exhaustive_search(sr, r);
	int ldiagonalcount = exhaustive_search(ldiagonal, r) + exhaustive_search(ldiagonalReversed, r);
	int rdiagonalcount = exhaustive_search(rdiagonal, r) + exhaustive_search(rdiagonalReversed, r);
	int verticalcount = exhaustive_search(v, r) + exhaustive_search(vr, r);
	int sum = linearcount + ldiagonalcount + rdiagonalcount + verticalcount;

	std::cout << "result: " << sum << std::endl;
	// std::cout << "standard: " << standardMatches << std::endl;
	return 0;
}

int exhaustive_search(std::string input, std::regex reg) {
	int count = 0;
	std::smatch match; 

	std::stringstream os(input);
	std::string line;

	while (std::getline(os, line)) {
		// std::cout << "line: " << line << std::endl;
		while (regex_search(line, match, reg)) {
			std::cout << "FOUND: " << match[0] << std::endl;
			count++;
			line = match.suffix();
			// std::cout << line << std::endl;
		}
	}


	return count;
}

std::string vertical(std::string input, int w, int h) {
	std::stringstream out;
	for(int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			int idx = coords_to_index(Coords(x, y), w);
			out << input[idx];
		}
		out << std::endl;
	}

	return out.str();
}

std::string diagonal(std::string input, int w, int h, bool right) {
	std::stringstream out;

	int largestside = std::max(w, h);
	int length = (w + h) - 3;
	int dist = 0;
	for (int i = 3; i < length; i++) {
		int hc = right ? i : (w - i);
		int vc = right ? -i : (w + i);

		Coords c1 = cursor_to_coords(hc, w, h);
		Coords c2 = cursor_to_coords(vc, w, h);

		Coords start = c2.first > c1.first ? c1 : c2;
		Coords end = c2.first > c1.first ? c2 : c1;

		
		int dist = right ? i + 1 : i;
		if (i > largestside) {
			dist = largestside - (i % largestside);
		}

		// std::cout << std::endl;
		int direction = end.second > start.second ? 1 : -1;
		std::vector<Coords> line;
		for (int d = 0; d < dist; d++) {
			int x = start.first + d;
			int y = start.second + (direction * d);
			int idx = coords_to_index(Coords(x, y), w);
			line.push_back(Coords(x, y));
			// std::cout << input[idx];
			out << input[idx];
		}
		// print_state(input, line, w, h);
		out << std::endl;
	}

	std::cout << out.str();
	return out.str();
}

int coords_to_index(Coords coords, int w) {
	int start = coords.second * w;
	return start + coords.first;
}

void print_state(std::string input, std::vector<Coords> coords, int w, int h) {
	std::cout << std::endl;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (x == 0) {
				std::cout << y << ": ";
			}
			Coords c = Coords(x, y);

			bool exists = false;
			for (auto target : coords) {
				if (target.first == x && target.second == y) {
					exists = true;
					break;
				}
			}

			int idx = coords_to_index(Coords(x, y), w);
			if (!exists) {
				std::cout << input[idx];
			} else {
				std::cout << "-";
			}
		}

		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Coords cursor_to_coords(int cursor, int w, int h) {

	if (cursor < 0) {
		cursor += (w + h) * 2;
	}

	if (cursor > 0) {
		int ncursor = (cursor % ((w + h) * 2));
		if (ncursor <= w) {
			// first side
			return Coords(ncursor, 0);
		} else if (ncursor > w && ncursor < (w + h)) {
			// second side
			return Coords(w, ncursor % w);
		} else if (ncursor < (w + h + w)) {
			// third side
			return Coords(w - (ncursor % (w + h)), h);
		} else {
			// fourth side
			return Coords(0, h - (ncursor % (w + h + w)));
		}
	}

	return Coords(0, 0);
}

Coords merge(Coords c1, Coords c2) {
	if (c1.first == 0) {
		return Coords(c2.first, c1.second);
	} else {
		return Coords(c1.first, c2.second);
	}
}

int distance(Coords c1, Coords c2) {
	int a = c2.first - c1.first;
	int b = c2.second - c1.second;
	int c = pow(a, 2) + pow(b, 2);
	return sqrt(c);
}
