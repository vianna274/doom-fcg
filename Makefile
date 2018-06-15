./bin/Linux/main: src/*.cpp include/*.h
	mkdir -p bin/Linux
	g++ -std=c++11 -Wall -Wno-unused-function -g -I ./include/ -o ./bin/Linux/main src/main.cpp src/glad.c src/player.cpp src/object.cpp src/wall.cpp src/support.cpp src/gun.cpp src/enemy.cpp src/textrendering.cpp src/tiny_obj_loader.cpp src/stb_image.cpp ./lib-linux/libglfw3.a src/collision.cpp -lrt -lm -ldl -lX11 -lpthread -lXrandr -lXinerama -lXxf86vm -lXcursor -lglut -lsfml-audio -lsfml-system 

.PHONY: clean run
clean:
	rm -f bin/Linux/main

run: ./bin/Linux/main
	cd bin/Linux && ./main
#CC=g++ -std=c++11
#CFLAGS=-I./include/ -I./lib/ -I./lib-linux/


#BIN_FOLDER=./bin/Linux/
#SRC_FOLDER=./src/

#DBFLAGS=-ggdb3 -O0 -g -Wall -Werror
#LDFLAGS=-lasan
#RELEASEFLAGS=-O2 -lglfw -lrt -lm -ldl -lX11 -lpthread -lXrandr -lXinerama -lXxf86vm -lXcursor -lglut -lsfml-audio -lsfml-system 


#SRC=$(wildcard $(SRC_FOLDER)*.cpp)
#OBJ=$(addprefix $(BIN_FOLDER),$(notdir $(SRC:.cpp=.o)))
#EXE=./bin/Linux/main

#all: $(OBJ)
#	g++ -g -o $(EXE) $(OBJ)

#./bin/Linux/%.o: ./src/%.cpp
#	@mkdir -p $(BIN_FOLDER)
#	$(CC) -o $@ $< $(CFLAGS) $(RELEASEFLAGS)

#clean:
#	rm -f $(BIN_FOLDER)*.o

#run: ./bin/Linux/main
#	cd bin/Linux && ./main

#.PHONY: clean run
