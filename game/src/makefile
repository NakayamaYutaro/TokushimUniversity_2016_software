CXXFLAGS = -D_GLIBCXX_DEBUG -Wall -Wextra -v
SDLFLAGS =  -lSDL -lSDL_image

.PHONY: test_model clean
build:
	g++ -o ../bin/game.out controllers/main.cpp -g -lpthread $(CXXFLAGS) $(SDLFLAGS)
clean:
	rm ../bin/*.out
