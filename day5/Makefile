CXXFLAGS += -g -Wall -O3 -pedantic -Wextra --std=c++20
all: test

test: parts
	./parts < .input

visual: parts
	./parts ppm < .input | convert - day5.png

clean:
	rm -f parts *.o
