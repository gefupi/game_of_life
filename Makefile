OUT=gameOfLife
CC=gcc
OBJS=game_of_life.o
CFLAGS=-Wall -o $(OUT)


$(OUT):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS)

main.o: game_of_life.c std_const.h
	$(CC) -c game_of_life.c

clean:
	rm -f *.o $(OUT)
	
