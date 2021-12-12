CXXFLAGS += --std=c++20 -g

test: all
	@echo question input
	./answer < ./.input
	@echo example input
	./answer < ./.testinput

all: answer

clean:
	rm -f answer *.o
