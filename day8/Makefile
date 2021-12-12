CXXFLAGS =-O3 -g --std=c++20 -fno-omit-frame-pointer -Wall -Werror -pedantic -Wextra

test: all
	./parts < .input

all: parts
clean:
	rm -f *.o parts perf.data*
