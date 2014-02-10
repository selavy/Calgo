CC = gcc
CFLAGS = -Wall -Werror -g -pedantic
INC = -I../include/

OBJS = driver.o queue.o

driver: $(OBJS)
	$(CC) -o driver $(CFLAGS) $(INC) $(OBJS)
driver.o: driver.c
	$(CC) $(CFLAGS) $(INC) -c driver.c
queue.o: queue.h queue.c
	$(CC) $(CFLAGS) $(INC) -c queue.c

.PHONY: clean
clean:
	rm -rf *.o driver