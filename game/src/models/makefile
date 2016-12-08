CXXFLAGS = -D_GLIBCXX_DEBUG -std=c++11 -Wall -Wextra -v
LDLIBS = -lCppUTest -lCppUTestExt

.PHONY: test_model clean
test_model:
	g++ -o ../../bin/test.out test_model.cpp -std=c++11 -lSDL -lSDL_image $(LDLIBS) $(CXXFLAGS)
clean:
	rm *.out
