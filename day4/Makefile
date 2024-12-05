.PHONY: run

build/solution2: solution2.cpp build
	clang++ solution2.cpp -o build/solution2

build/program: main.cpp build
	clang++ main.cpp -o build/program

build:
	mkdir build

run: build/program build/solution2
	./build/solution2 < input.txt
