all: clean fold_expressions fold_expressions2 fold_expressions3 union

clean:
	@rm -f *.bin
	# @find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;

fold_expressions:
	g++ -std=c++17 $@.cpp -o $@.bin

fold_expressions2:
	g++ -std=c++17 $@.cpp -o $@.bin

fold_expressions3:
	g++ -std=c++17 -ISI/include/ $@.cpp -o $@.bin

union:
	g++ -std=c++17 $@.cpp -o $@.bin
