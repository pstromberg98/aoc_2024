.PHONY: run

program: main.cpp lexer.yy.cpp tokens.h
	clang++ main.cpp lexer.yy.cpp -o program

lexer.yy.cpp: tokens.h lexer.l
	lex -o lexer.yy.cpp lexer.l

run: program input.txt
	./program < input.txt
