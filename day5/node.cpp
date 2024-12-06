#include <vector>
#include "node.h"

std::vector<Node*> allnodes;

Node* create_node() {
	Node* n = new Node();
	allnodes.push_back(n);
	return n;
}

void free_nodes() {
	for (auto n : allnodes) {
		free(n);
	}
}
