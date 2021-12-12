CXXFLAGS = -g -O0

test: all
	./sol < .input
	./sm < .input

all: sol sm
sol: lexer.o parser.o
	$(CXX) -o $@ $^
lexer.cc: lexer.l parser.h
	flex -o $@ lexer.l
parser.cc parser.h: parser.y
	bison -o parser.cc --defines=parser.h $^
clean:
	rm -rf *.cc *.o sol *.h sm
