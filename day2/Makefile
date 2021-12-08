CXXFLAGS = -g -O0
all: test
sol: lexer.o parser.o
	$(CXX) -o $@ $^
lexer.cc: lexer.l parser.h
	flex -o $@ lexer.l
parser.cc parser.h: parser.y
	bison -o parser.cc --defines=parser.h $^
clean:
	rm -rf *.cc *.o sol *.h sm
test: sol sm
	./sol < .input
	./sm < .input
