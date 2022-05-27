CXXFLAGS += -g -O3 -std=c++2a -Wall

.PHONY: all test clean check

check: tests solve
	./reduce_test
	./explode_test
	./solve < input.txt

all: solve

clean:
	rm -f *.o solve *_test *.a

libsn.a: sn.o
	ar r $@ $^

solve: solve.o libsn.a
	$(CXX) -o $@ $^

tests: all explode_test reduce_test

explode_test: explode_test.o libsn.a
	$(CXX) -o $@ $^
reduce_test: reduce_test.o libsn.a
	$(CXX) -o $@ $^
