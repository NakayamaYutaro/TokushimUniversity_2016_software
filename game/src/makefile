CXXFLAGS = -D_GLIBCXX_DEBUG -std=c++11 -Wall -Wextra -v
LDLIBS = -lCppUTest -lCppUTestExt

.PHONY: test_model clean
build:
	g++ -o ../bin/game.out controllers/main.cpp -std=c++11 -lSDL -lSDL_image $(LDLIBS) $(CXXFLAGS)
clean:
	rm ../bin/*.out
