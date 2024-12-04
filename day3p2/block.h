#include <vector>

struct Block {
	bool included;
	std::vector<int>* list;
};

extern std::vector<Block> blocks;
