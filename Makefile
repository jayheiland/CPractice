CXX = gcc
CXXFLAGS = -g -Wall
BLD = ./build
BIN = ./bin
EXEC = $(BIN)/game.app
SRC = ./src

mac: $(BLD)/main.o $(BLD)/world.o $(BLD)/general.o $(BLD)/message.o $(BLD)/user_input.o $(BLD)/graphics.o $(BLD)/creature.o
	$(CXX) $(CXXFLAGS) -o $(EXEC) $^ -I./external/SDL2/2.0.10/include -L./external/SDL2/2.0.10/lib -lSDL2

$(BLD)/main.o: $(SRC)/main.c
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/world.o: $(SRC)/world.c
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/general.o: $(SRC)/general.c
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/message.o: $(SRC)/message.c
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/user_input.o: $(SRC)/user_input.c
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/graphics.o: $(SRC)/graphics.c
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/creature.o: $(SRC)/creature.c
	$(CXX) $(CXXFLAGS) -o $@ -c $^

dirSetup:
	mkdir build
	mkdir bin

clean:
	rm $(BLD)/*.o
	rm $(BIN)/*.app
	rmdir $(BLD)
	rmdir $(BIN)