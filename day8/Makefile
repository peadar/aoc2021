CXXFLAGS =-O3 -g --std=c++20 -fno-omit-frame-pointer -Wall -Werror -pedantic -Wextra

all: parts

parts: parts.o
	$(CXX) -o $@ $^

test: parts
	./parts < .input
clean:
	rm *.o parts perf.data*
