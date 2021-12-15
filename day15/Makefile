CXXFLAGS += -g -O0 -std=c++20 -Wall

test: all
	@./solve 1 < .input
	@./solve 2 < .input

all: solve

clean:
	rm -f *.o solve
