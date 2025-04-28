commonfunctions.o: commonfunctions.cpp commonfunctions.h
        g++ -c commonfunctions.cpp
game.o: game.cpp game.h commonfunctions.h
        g++ -c game.cpp
main.o: main.cpp game.h commonfunctions.h
        g++ -c main.cpp
main: game.o main.o commonfunctions.o
        g++ game.o main.o commonfunctions.o -o main
clean:
        rm -f game.o main.o commonfunctions.o
.PHONY: clean
