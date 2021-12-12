CXXFLAGS += -g -Wall -O3 -pedantic -Wextra --std=c++20

test: all
	./parts < .input

all: parts

visual: parts
	./parts ppm < .input | convert - day5.png

clean:
	rm -f parts *.o
