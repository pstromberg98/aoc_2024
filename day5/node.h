struct Node {
	std::vector<Node*> children;
	Node* parent = nullptr;
	bool hasparent = false;
	int number;
};

Node* create_node();
void free_nodes();
