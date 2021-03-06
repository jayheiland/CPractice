CXX = g++
CXXFLAGS = -g -Wall -std=c++17
BLD = ./build
BIN = ./bin
EXEC = $(BIN)/game.app
SRC = ./src

all: $(BLD)/main.o $(BLD)/world.o $(BLD)/general.o $(BLD)/message.o $(BLD)/user_input.o $(BLD)/graphics.o $(BLD)/creature.o $(BLD)/creature_group.o $(BLD)/object_group.o $(BLD)/object.o $(BLD)/material_group.o $(BLD)/material.o
	$(CXX) $(CXXFLAGS) -o $(EXEC) $^ -I./external/SDL2/2.0.10/include -L./external/SDL2/2.0.10/lib -lSDL2

$(BLD)/main.o: $(SRC)/main.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/world.o: $(SRC)/world.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/general.o: $(SRC)/general.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/message.o: $(SRC)/message.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/user_input.o: $(SRC)/user_input.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/graphics.o: $(SRC)/graphics.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/creature.o: $(SRC)/creature.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/creature_group.o: $(SRC)/creature_group.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/object_group.o: $(SRC)/object_group.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/object.o: $(SRC)/object.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/material_group.o: $(SRC)/material_group.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/material.o: $(SRC)/material.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

dirSetup:
	mkdir build
	mkdir bin

dirCleanup:
	rmdir build
	rmdir bin

clean:
	rm $(BLD)/*.o
	rm $(BIN)/*.app