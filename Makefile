OUT=gameOfLife
CC=gcc
OBJS=main.o
CFLAGS=-Wall 


$(OUT):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS)

main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o $(OUT) >> /dev/null
	
