OUT=gameOfLife
CC=gcc
OBJS=game_of_life.o biotope.o
CFLAGS=-Wall -o $(OUT)


$(OUT):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS)

main.o: game_of_life.c std_const.h
	$(CC) -c game_of_life.c

biotope.o: biotope.c biotope.h
	$(CC) -c biotope.c


# Some usefull stuff
clean:
	rm -f *.o $(OUT)
	
run:
	./$(OUT)