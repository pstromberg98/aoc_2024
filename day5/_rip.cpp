#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include "node.h"

extern int yylex();

struct RuleSequence {
	int seqidx = 0;
	std::vector<int>* sequence;
};

std::unordered_set<int> keys;
std::unordered_map<int, std::vector<int>> rules;
std::vector<RuleSequence*> sequences;
std::vector<std::vector<int>> pages;

void expand(Node* n, std::unordered_set<int> visited={});
void traverse(Node* root, std::vector<Node*>& leaves);
void sequence(std::vector<Node*>& leaves);
bool push_to_sequence(RuleSequence* rseq, int value);
bool is_sequence_applicable(RuleSequence* rseq, std::vector<int>& values);
RuleSequence* reduce(RuleSequence* rseq, std::vector<int>& values);

std::vector<Node*> roots;

#define DEBUG
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
		std::cout << "expanding node: " << key << std::endl;
		expand(node);
		std::cout << std::endl;
		roots.push_back(node);
	}

	std::cout << "expanding done" << std::endl;

	for (auto root : roots) {
		std::vector<Node*> leaves;
		traverse(root, leaves);
		sequence(leaves);
	}

	std::vector<int> validpages;
	int pageid = 0;
	for (auto page : pages) {
		bool valid = false;
		for (auto value : page) {
			int seqid = 0;
			for (auto s : sequences) {
				auto reduced = reduce(s, page);
#ifdef DEBUG
				std::cout << "SEQUENCE: " << seqid << " VALUE: " << value << std::endl;
#endif
				valid = push_to_sequence(reduced, value);
				free(reduced);

				if (!valid) {
					break;
				}

				seqid++;

#ifdef DEBUG
				std::cout << std::endl;
				std::cout << std::endl;
#endif
			}

			if (!valid) {
				std::cout << "invalid!" << std::endl;
				break;
			}
		}

		if (valid) {
			validpages.push_back(pageid);
		}

		for (auto s : sequences) {
			s->seqidx = 0;
		}

		pageid++;
	}

	int sum = 0;
	for (auto pgid : validpages) {
		auto values = pages[pgid];
		auto mid = values[((values.size() + 1) / 2) - 1];
		std::cout << "page id: " << pgid << std::endl;
		sum += mid;
	}

	std::cout << "result: " << sum << std::endl;

	/*
	for (auto seq : sequences) {
		for (auto n : seq) {
			std::cout << n << "-";
		}
		std::cout << std::endl;
	}
	*/

	free_nodes();
	return 0;
}

RuleSequence* reduce(RuleSequence* rseq, std::vector<int>& values) {
	RuleSequence* newrseq = (RuleSequence*)malloc(sizeof(RuleSequence));
	newrseq->sequence = new std::vector<int>();
	newrseq->seqidx = rseq->seqidx;

	for (auto v : values) {
		for (int i = 0; i < rseq->sequence->size(); i++) {
			int rval = rseq->sequence->at(i);

			if (rval == v) {
				newrseq->sequence->push_back(v);
			}
		}
	}

	return newrseq;
}

bool is_sequence_applicable(RuleSequence* rseq, std::vector<int>& values) {
	// if sequence contains more value types than values

	for (int i = 0; i < rseq->sequence->size(); i++) {
		int sval = rseq->sequence->at(i);
		std::cout << "searching for: " << sval << std::endl;

		bool contains = false;
		for (auto v : values) {
			if (v == sval) {
				contains = true;
				std::cout << "found!" << std::endl;
				break;
			}
		}

		if (!contains) {
			return false;
		}
	}

	return true;
}

bool push_to_sequence(RuleSequence* rseq, int value) {
	int order = -1;
	int i = 0;

	for (int sidx = 0; sidx < rseq->sequence->size(); sidx++) {
		int s = rseq->sequence->at(sidx);
		if (s == value) {
			order = i;
			break;
		}
		i++;
	}

#ifdef DEBUG
	std::cout << "order: " << order << std::endl;
	std::cout << "value: " << value << std::endl;
	std::cout << "seqidx: " << rseq->seqidx << std::endl;
	std::cout << "sequence: ";
	for (int a = 0; a < rseq->sequence->size(); a++) {
		std::cout << rseq->sequence->at(a) << " ";
	}
	std::cout << std::endl;
#endif

	if (order == -1) {
		return true;
	}

	if (order >= rseq->seqidx) {
		rseq->seqidx++;
		// std::cout << "new seqidx: " << rseq->seqidx << std::endl;
		return true;
	}

	return false;
}

void sequence(std::vector<Node*>& leaves) {
	for (auto leave : leaves) {
		Node* n = leave;
		std::vector<int>* seqs = new std::vector<int>();
		while (true) {
			seqs->push_back(n->number);
			if (!n->hasparent) {
				break;
			}
			n = n->parent;
		}

		std::reverse(seqs->begin(), seqs->end());
		RuleSequence* rs = (RuleSequence*)malloc(sizeof(RuleSequence));
		rs->sequence = seqs;
		sequences.push_back(rs);
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

void expand(Node* n, std::unordered_set<int> visited) {

	std::cout << "visited: ";
	for (auto v : visited) {
		std::cout << v;
	}
	std::cout << std::endl;

	std::vector<int> ckeys = rules[n->number];
	if (visited.find(n->number) != visited.end()) {
		std::cout << "skiping" << std::endl;
		return;
	} else {
		visited.insert(n->number);
	}

	for (auto k : ckeys) {
		if (visited.find(k) != visited.end()) {
			continue;
		}
		Node* child = create_node();
		child->number = k;
		child->parent = n;
		child->hasparent = true;

		n->children.push_back(child);

		expand(child, visited);
	}
}

