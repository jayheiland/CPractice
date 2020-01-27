CXX = gcc
CXXFLAGS = -g -Wall
BLD = ./build
BIN = ./bin
EXEC = $(BIN)/game.app
SRC = ./src

mac: $(BLD)/main.o $(BLD)/world.o $(BLD)/general.o
	$(CXX) $(CXXFLAGS) -o $(EXEC) $^

$(BLD)/main.o: $(SRC)/main.c
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/world.o: $(SRC)/world.c
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/general.o: $(SRC)/general.c
	$(CXX) $(CXXFLAGS) -o $@ -c $^

dir_setup:
	mkdir build
	mkdir bin

clean:
	rm $(BLD)/*.o
	rm $(BIN)/*.app
	rmdir $(BLD)
	rmdir $(BIN)