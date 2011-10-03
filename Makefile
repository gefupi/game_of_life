OUT=gameOfLife
CC=gcc
OBJS=game_of_life.o biotope.o life_point.o read_biotopefile.o fast_biotope.o
CFLAGS=-Wall -Wextra -o $(OUT)


$(OUT):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS)

game_of_life.o: game_of_life.c std_const.h biotope.h fast_biotope.h
	$(CC) -c game_of_life.c

biotope.o: biotope.c biotope.h\
           life_point.h std_const.h
	$(CC) -c biotope.c

fast_biotope.o: fast_biotope.c fast_biotope.h\
                std_const.h
	$(CC) -c fast_biotope.c

life_point.o: life_point.c life_point.h
	$(CC) -c life_point.c

read_biotopefile.o: read_biotopefile.c read_biotopefile.h
	$(CC) -c read_biotopefile.c

# Some usefull stuff
clean:
	rm -f *.o *.c~ *.h~ $(OUT)

run:
	./$(OUT)