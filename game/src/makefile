CXXFLAGS = -D_GLIBCXX_DEBUG -Wall -Wextra -v
SDLFLAGS = -lSDL -lSDL_image -lSDL_ttf

.PHONY: test_model clean
build:
	g++ -o ../bin/game.out controllers/main.cpp -g $(SDLFLAGS) $(CXXFLAGS)
clean:
	rm ../bin/*.out
