OUT=gameOfLife
CC=gcc
OBJS=game_of_life.o biotope.o life_point.o
CFLAGS=-Wall -o $(OUT)


$(OUT):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS)

main.o: game_of_life.c std_const.h
	$(CC) -c game_of_life.c

biotope.o: biotope.c biotope.h\
           life_point.h
	$(CC) -c biotope.c

life_point.o: life_point.c life_point.h
	$(CC) -c life_point.c

# Some usefull stuff
clean:
	rm -f *.o *.c~ *.h~ $(OUT)

run:
	./$(OUT)