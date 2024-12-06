%{
	#include <iostream>
	#include <regex>
	#include <string>
	#include <unordered_map>
	#include <unordered_set>
	
	extern std::unordered_set<int> keys;
	extern std::unordered_map<int, std::vector<int>> rules;
	extern std::vector<std::vector<int>> pages;
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
[0-9,]+\n		{
				std::string input(yytext);
				std::smatch match;
				std::regex r("[0-9]+");

				std::vector<int> page;
				while(regex_search(input, match, r)) {
					page.push_back(stoi(match[0]));
					input = match.suffix();
				}

				//std::reverse(page.begin(), page.end());
				pages.push_back(page);
			}
.			{}
\n			{}
%%

int yywrap() {
	return 1;
}
