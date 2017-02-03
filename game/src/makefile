CC = g++
CXXFLAGS = -D_GLIBCXX_DEBUG -Wall -Wextra -v
SDLFLAGS =  -lSDL -lSDL_image -lSDL_ttf

.PHONY: test_model clean
build:
	$(CC) -o ../bin/game.out controllers/main.cpp -g -lpthread $(CXXFLAGS) $(SDLFLAGS)
clean:
	rm ../bin/*.out
