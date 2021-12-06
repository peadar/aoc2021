parts: parts.o
	$(CXX) -o $@ $^

test: parts
	@echo part1
	@./parts 80 < .input
	@echo part2
	@./parts 256 < .input

clean:
	rm -f parts *.o
