all: clean fold_expressions fold_expressions2

clean:
	@rm -f *.bin

fold_expressions:
	g++ -std=c++17 $@.cpp -o $@.bin

fold_expressions2:
	g++ -std=c++17 $@.cpp -o $@.bin