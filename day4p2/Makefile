.PHONY: run

build/program: main.cpp build
	clang++ main.cpp -o build/program

build:
	mkdir build

run: build/program build/solution2
	./build/solution2 < input.txt
