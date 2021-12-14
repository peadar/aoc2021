CXXFLAGS += -g -O3 -std=c++20 -Wall

test: all
	@echo -n "part1: "
	@./solve 10 < .input
	@echo -n "part2: "
	@./solve 40 < .input

all: solve

clean:
	rm -f *.o solve
