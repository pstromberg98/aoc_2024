#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include "node.h"
extern int yylex();

std::unordered_set<int> keys;
std::unordered_map<int, std::vector<int>> rules;
std::vector<std::vector<int>> sequences;

void expand(Node* n, bool first=false);
void traverse(Node* root, std::vector<Node*>& leaves);
void sequence(std::vector<Node*>& leaves);

std::vector<Node*> roots;

// sequence
// state
// 1. we can add to state
// 2. we must then check state
// 3. if check fails, does not follow rules
// 4. state index
//
// add (n) to state if seq contains()

int main() {
	yylex();

	std::cout << "expansions needed: " << keys.size() << std::endl;
	Node* node = create_node();
	for (auto key : keys) {
		Node* node = create_node();
		node->number = key;
		expand(node, true);
		roots.push_back(node);
	}

	std::cout << "expanding done" << std::endl;

	for (auto root : roots) {
		std::vector<Node*> leaves;
		traverse(root, leaves);
		sequence(leaves);
	}


	for (auto seq : sequences) {
		for (auto n : seq) {
			std::cout << n << "-";
		}
		std::cout << std::endl;
	}

	free_nodes();
	return 0;
}

void sequence(std::vector<Node*>& leaves) {
	for (auto leave : leaves) {
		Node* n = leave;
		std::vector<int> seqs;
		while (true) {
			seqs.push_back(n->number);
			if (!n->hasparent) {
				break;
			}
			n = n->parent;
		}

		std::reverse(seqs.begin(), seqs.end());
		sequences.push_back(seqs);
	}
}

void traverse(Node* root, std::vector<Node*>& leaves) {
	int ccount = root->children.size();
	
	for (int i = 0; i < ccount; i++) {
		Node* child = root->children[i];
		traverse(child, leaves);
	}

	if (ccount == 0) {
		leaves.push_back(root);
	}
}

std::unordered_set<int> visited;
void expand(Node* n, bool first) {
	std::vector<int> ckeys = rules[n->number];
	for (auto k : ckeys) {
		Node* child = create_node();
		child->number = k;
		child->parent = n;
		child->hasparent = true;

		n->children.push_back(child);

		if (visited.find(k) == visited.end()) {
			visited.insert(k);
			expand(child);
		}
	}

	if (first) {
		visited.clear();
	}
}

