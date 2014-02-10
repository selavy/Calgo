CC = gcc
CFLAGS = -Wall -Werror -pedantic -g
INC = -I../include/ -I../portfolio/ -I../hash_table/ -I../database/ -I../queue/

OBJS = driver.o hash.o hash_table.o database.o queue.o engine.o portfolio.o

driver: $(OBJS)
	$(CC) -o driver $(CFLAGS) $(INC) $(OBJS)
driver.o: driver.c
	$(CC) $(CFLAGS) $(INC) -c driver.c
hash.o: ../hash_table/hash/hash.h ../hash_table/hash/hash.c
	$(CC) $(CFLAGS) $(INC) -c ../hash_table/hash/hash.c
hash_table.o: ../hash_table/hash_table.h ../hash_table/hash_table.c
	$(CC) $(CFLAGS) $(INC) -c ../hash_table/hash_table.c
database.o: ../database/database.h ../database/database.c
	$(CC) $(CFLAGS) $(INC) -c ../database/database.c
queue.o: ../queue/queue.h ../queue/queue.c
	$(CC) $(CFLAGS) $(INC) -c ../queue/queue.c
engine.o: engine.h engine.c
	$(CC) $(CFLAGS) $(INC) -c engine.c
portfolio.o: ../portfolio/portfolio.h ../portfolio/portfolio.c
	$(CC) $(CFLAGS) $(INC) -c ../portfolio/portfolio.c

.PHONY: clean
clean:
	rm -rf *.o driver