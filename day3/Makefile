.PHONY: run

build/program: main.cpp lexer.yy.cpp main.h build
	clang++ main.cpp lexer.yy.cpp -o build/program

lexer.yy.cpp: lexer.l
	lex -o lexer.yy.cpp lexer.l

build:
	mkdir build

run: build/program input.txt
	./build/program < input.txt
