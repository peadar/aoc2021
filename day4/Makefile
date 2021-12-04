CXXFLAGS += --std=c++20 -g

all: answer
test: answer
	@echo question input
	./answer < ./.input
	@echo example input
	./answer < ./.testinput

clean:
	rm -f part1 *.o
