OPT = -Wall -Wextra -g
OBJS = main.o room.o house.o hunter.o ghost.o utils.o logger.o 

fp : $(OBJS)
	gcc $(OPT) -o  fp -lpthread $(OBJS)

main.o : main.c defs.h
	gcc $(OPT) -c main.c 

room.o: room.c defs.h
	gcc $(OPT) -c room.c

house.o: house.c defs.h
	gcc $(OPT) -c house.c

hunter.o: hunter.c defs.h
	gcc $(OPT) -c hunter.c

ghost.o: ghost.c defs.h
	gcc $(OPT) -c ghost.c

utils.o: utils.c defs.h
	gcc $(OPT) -c utils.c

logger.o: logger.c defs.h
	gcc $(OPT) -c logger.c

# Clean up
clean:
	rm -f $(OBJS) fp
