CXX = g++
CXXFLAGS = -g -Wall -std=c++17
BLD = ./build
BIN = ./bin
EXEC = $(BIN)/game.app
SRC = ./src

all_faster:
	make all -j 4

all: $(BLD)/main.o $(BLD)/world.o $(BLD)/general.o $(BLD)/creature.o $(BLD)/creaturem.o $(BLD)/graphics.o $(BLD)/objectm.o $(BLD)/object.o $(BLD)/material_group.o $(BLD)/material.o $(BLD)/battle.o $(BLD)/worldm.o
	$(CXX) $(CXXFLAGS) -o $(EXEC) $^ -lgoldenplains

$(BLD)/main.o: $(SRC)/main.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/world.o: $(SRC)/world.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/general.o: $(SRC)/general.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/creature.o: $(SRC)/creature.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/creaturem.o: $(SRC)/creaturem.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/graphics.o: $(SRC)/graphics.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/objectm.o: $(SRC)/objectm.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/object.o: $(SRC)/object.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/material_group.o: $(SRC)/material_group.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/material.o: $(SRC)/material.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/battle.o: $(SRC)/battle.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

$(BLD)/worldm.o: $(SRC)/worldm.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

.PHONY: dirSetup dirCleanup clean run debug

dirSetup:
	mkdir build
	mkdir bin

dirCleanup:
	rmdir build
	rmdir bin

clean:
	rm -f $(BLD)/*.o
	rm -f $(BIN)/*.app

rebuild:
	make clean
	make

run:
	./bin/game.app

memcheck:
	valgrind --leak-check=full --verbose ./bin/game.app
	echo "valgrind shows small, one-time memory leaks (about 2 kb) when running this Vulkan application, probably don't need to worry about these"

debug:
	lldb ./bin/game.app