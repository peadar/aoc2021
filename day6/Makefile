CXXFLAGS += -g -O3 -fno-omit-frame-pointer -Wall -Wextra -pedantic

test: all
	@echo in C++:
	@./parts 80 256 < .input
	@echo in python:
	@python ./parts.py < .input

all: parts

parts: parts.o
	$(CXX) -o $@ $^

clean:
	rm -f parts *.o perf.data*
