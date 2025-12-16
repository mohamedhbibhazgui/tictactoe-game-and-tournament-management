CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
OBJ = main.o players.o matches.o game.o fileio.o utils.o

all: tournament

tournament: $(OBJ)
	$(CC) $(CFLAGS) -o tournament $(OBJ)

main.o: main.c players.h matches.h game.h fileio.h utils.h
players.o: players.c players.h matches.h utils.h
matches.o: matches.c matches.h players.h utils.h
game.o: game.c game.h players.h matches.h utils.h
fileio.o: fileio.c fileio.h players.h matches.h
utils.o: utils.c utils.h

clean:
	rm -f *.o tournament

run: tournament
	./tournament
