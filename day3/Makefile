YACC=bison

CXXFLAGS = -g -O0 --std=c++20

test: all
	./part1 < .input
	./part2 < .input
	python ./part2.py < .input

%.cc: %.y++
	bison -o $@ $^

clean:
	rm -rf part1.cc *.o part1 part2

part1: part1.cc
part2: part2.cc

all: part1 part2
