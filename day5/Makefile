CXXFLAGS += -g -Wall -O3 -pedantic -Wextra --std=c++20
all: parts

test: all
	./parts < .input

visual: all
	./parts ppm < .input > day5.ppm
	convert day5.ppm day5.png

clean:
	rm -f parts *.o
