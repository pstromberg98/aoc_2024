build/program: lexer.yy.cpp main.cpp node.h node.cpp build
	clang++ main.cpp lexer.yy.cpp node.cpp -o build/program

lexer.yy.cpp: lexer.l
	lex -o lexer.yy.cpp lexer.l

build:
	mkdir build

run: build/program
	./build/program < input.txt
