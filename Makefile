game.o: game.cpp game.h
        g++ -c game.cpp
main.o: main.cpp game.h
        g++ -c main.cpp
main: game.o main.o
        g++ game.o main.o -o main
clean:
        rm -f game.o main.o
.PHONY: clean
