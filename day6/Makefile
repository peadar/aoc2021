CXXFLAGS += -g -O3 -fno-omit-frame-pointer -Wall -Wextra -pedantic
parts: parts.o
	$(CXX) -o $@ $^

test: parts
	@echo in C++:
	@./parts 80 256 < .input
	@echo in python:
	@python ./parts.py < .input

clean:
	rm -f parts *.o
