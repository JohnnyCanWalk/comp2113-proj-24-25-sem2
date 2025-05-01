commonfunctions.o: commonfunctions.cpp commonfunctions.h
        g++ -c commonfunctions.cpp
listf.o: listf.cpp listf.h
        g++ -c listf.cpp
game.o: game.cpp game.h listf.h commonfunctions.h
        g++ -c game.cpp
story.o: story.cpp story.h
        g++ -c story.cpp
main.o: main.cpp story.h game.h commonfunctions.h
        g++ -c main.cpp
main: game.o main.o commonfunctions.o listf.o story.o
        g++ game.o main.o commonfunctions.o listf.o story.o -o main
clean:
        rm -f game.o main.o commonfunctions.o listf.o story.o
.PHONY: clean
