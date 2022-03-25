CC := g++-10
FLAGS := -std=c++20
BIN_FOLD := bin

$(BIN_FOLD)/res: test/main.cpp
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm $(BIN_FOLD)/*