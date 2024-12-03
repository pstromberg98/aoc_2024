.PHONY: run

build/program: main.cpp lexer.yy.cpp parser.tab.cpp input.h build
	clang++ main.cpp parser.tab.cpp lexer.yy.cpp -I./ -o build/program

lexer.yy.cpp: lexer.l
	lex -o lexer.yy.cpp lexer.l

parser.tab.cpp: parser.y
	yacc -d -o parser.tab.cpp parser.y

build:
	mkdir build

run: build/program
	./build/program < input.txt
