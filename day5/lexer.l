%{
	#include <iostream>
	#include <regex>
	#include <string>
	#include <unordered_map>
	#include <unordered_set>
	
	extern std::unordered_set<int> keys;
	extern std::unordered_map<int, std::vector<int>> rules;
%}

%%
[0-9]+\|[0-9]+		{
				std::string input(yytext);
				std::smatch first;
				std::smatch second;
				std::regex r("[0-9]+");


				std::regex_search(input, first, r);

				std::string next = first.suffix();
				std::regex_search(next, second, r);
				
				int key = stoi(first[0]);
				int value = stoi(second[0]);


				if (rules.find(key) == rules.end()) {
					keys.insert(key);
					rules[key] = std::vector<int>();
				}

				rules[key].push_back(value);
			}
.			{}
\n			{}
%%

int yywrap() {
	return 1;
}
