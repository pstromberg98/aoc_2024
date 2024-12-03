#include <vector>

enum TokenType {
	NEWLINE = 1,
	NUMBER,
};

struct Token {
	TokenType type;
	int data;
};

extern std::vector<Token> tokens;
