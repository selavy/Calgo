CPP = gcc
CFLAGS = -Wall -Werror -pedantic -g

OBJS = rbtree.o main.o


driver: $(OBJS)
	$(CPP) -o driver $(CFLAGS) $(OBJS)
main.o: main.c
	$(CPP) $(CFLAGS) -c main.c
rbtree.o: rbtree.h rbtree.c
	$(CPP) $(CFLAGS) -c rbtree.c

.PHONY: clean
clean:
	rm -rf *.o driver