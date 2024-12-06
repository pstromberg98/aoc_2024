#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <string>

extern int yylex();

std::unordered_set<int> keys;
std::unordered_map<int, std::vector<int>> rules;
std::vector<std::vector<int>> updates;
std::unordered_map<std::string, bool> cache;

bool search_by_left(int current, int proposed, std::vector<int>& input, std::unordered_set<int> visited={});
bool contains(std::vector<int>& input, int val);

int main() {
	yylex();

	int updateid = 0;
	std::vector<int> updateids;
	for (auto pages : updates) {
		bool invalid = false;
		for (int i = 0; i < pages.size(); i++) {
			int current = pages[i];
			for (int j = i + 1; j < pages.size(); j++) {
				int proposed = pages[j];
				if (!search_by_left(current, proposed, pages)) {
					std::cout << "invalid!" << std::endl;
					invalid = true;
					break;
				}
				
				if (invalid) {
					break;
				}
			}

			if (invalid) {
				break;
			}
		}

		if (!invalid) {
			updateids.push_back(updateid);
		}

		cache = std::unordered_map<std::string, bool>();

		updateid++;
	}

	int sum = 0;
	for (auto id : updateids) {
		auto pages = updates[id];
		int mid = pages[((pages.size() + 1) / 2) - 1];
		sum += mid;
	}

	std::cout << "successes: " << updateids.size() << std::endl;
	std::cout << "sum: " << sum << std::endl;

	return 0;
}

bool search_by_left(int current, int proposed, std::vector<int>& input, std::unordered_set<int> visited) {

	if (rules.find(proposed) != rules.end()) {
		std::vector<int> rule = rules[proposed];
		for (auto r : rule) {
			if (!contains(input, r)) {
				continue;
			}

			std::string ckey = std::to_string(current) + "-" + std::to_string(r) + "-" + std::to_string((long)&input);

			if (cache.find(ckey) != cache.end() && false) {
				// std::cout << "hit: " << ckey << std::endl;
				return cache[ckey];
			}

			if (visited.find(r) == visited.end()) {
				// std::cout << "checking: " << r << std::endl;
				if (r == current) {
					// std::cout << "proposed: " << r << " current: " << current;
					// cache[ckey] = false;
					return false;
				}

				if(!search_by_left(current, r, input, visited)) {
					// cache[ckey] = false;
					return false;
				} else {
					cache[ckey] = true;
				}
			}
		}
	}

	std::string cachekey = std::to_string(current) + "-" + std::to_string(proposed);
	
	// cache[cachekey] = true;
	// cache[ckey] = true;
	return true;
}

bool contains(std::vector<int>& input, int val) {
	for (auto v : input) {
		if (v == val) {
			return true;
		}
	}

	return false;
}
