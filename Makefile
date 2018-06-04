./bin/Linux/main: src/*.cpp include/*.h
	mkdir -p bin/Linux
	g++ -std=c++11 -Wall -Wno-unused-function -g -I ./include/ -o ./bin/Linux/main src/main.cpp src/glad.c src/player.cpp src/object.cpp src/wall.cpp src/support.cpp src/textrendering.cpp src/tiny_obj_loader.cpp src/stb_image.cpp ./lib-linux/libglfw3.a -lrt -lm -ldl -lX11 -lpthread -lXrandr -lXinerama -lXxf86vm -lsfml-audio -lsfml-system -lXcursor

.PHONY: clean run
clean:
	rm -f bin/Linux/main

run: ./bin/Linux/main
	cd bin/Linux && ./main
