OBJS = main.o main_functions.o other_functions.o
SOURCE = main.c main_functions.c other_functions.c
HEADER = functions.h structs.h
OUT = mygraph
CC=gcc
FLAGS= -g -c
CLEAR = clear_screen

all: $(CLEAR) $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

clear_screen:
	clear

main.o: main.c
	$(CC) $(FLAGS) main.c

main_functions.o: main_functions.c
	$(CC) $(FLAGS) main_functions.c

other_functions.o: other_functions.c
	$(CC) $(FLAGS) other_functions.c

clean:
	rm -f $(OBJS) $(OUT)
