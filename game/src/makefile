CXXFLAGS = -D_GLIBCXX_DEBUG -Wall -Wextra -v

.PHONY: test_model clean
build:
	g++ -o ../bin/game.out controllers/main.cpp -lSDL -lSDL_image $(CXXFLAGS)
clean:
	rm ../bin/*.out
