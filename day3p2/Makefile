.PHONY: run

build/program: main.cpp lexer.yy.cpp parser.tab.cpp main.h build
	clang++ main.cpp lexer.yy.cpp parser.tab.cpp -o build/program

lexer.yy.cpp: lexer.l
	lex -o lexer.yy.cpp lexer.l

parser.tab.cpp: parser.y
	yacc -t -d -o parser.tab.cpp parser.y

build:
	mkdir build

run: build/program input.txt
	./build/program < input.txt
