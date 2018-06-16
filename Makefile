CXX=g++ -std=c++11
CXXFLAGS=-I./include/ -I./lib/ -I./lib-linux/


BIN_FOLDER=./bin/Linux/
SRC_FOLDER=./src/

DBFLAGS=-ggdb3 -O0 -g -Wall -Werror
RELEASEFLAGS=-O2 -lglfw -lrt -lm -ldl -lX11 -lpthread -lXrandr -lXinerama -lXxf86vm -lXcursor -lglut -lsfml-audio -lsfml-system 

SRC=$(wildcard $(SRC_FOLDER)*.cpp)
OBJ=$(addprefix $(BIN_FOLDER),$(notdir $(SRC:.cpp=.o)))
EXE=./bin/Linux/main

all: $(OBJ)
	$(CXX) -g -o $(EXE) $(OBJ) $(RELEASEFLAGS)

./bin/Linux/%.o: ./src/%.cpp
	@mkdir -p $(BIN_FOLDER)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(RELEASEFLAGS)

clean:
	rm -rf $(BIN_FOLDER)

run:
	make && cd $(BIN_FOLDER) && ./main

.PHONY: clean run
