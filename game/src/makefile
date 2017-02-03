CC = g++
CXXFLAGS = -D_GLIBCXX_DEBUG -Wall -Wextra -v -g3
SDLFLAGS = -lm -lSDL -lSDL_image -lSDL_ttf -lSDL_gfx -lcwiimote -D_ENABLE_TILT -D_ENABLE_FORC -L/usr/lib

.PHONY: build clean
build:
	$(CC) -o ../bin/game.out controllers/main.cpp -g -lpthread $(CXXFLAGS) $(SDLFLAGS)
clean:
	rm ../bin/*.out
