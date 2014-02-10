CC = gcc
CFLAGS = -Wall -Werror -g
INC = -I../hash_table/ -I../include/

OBJS = hash_table.o hash.o portfolio.o driver.o

driver: $(OBJS)
	$(CC) -o driver $(CFLAGS) $(INC) $(OBJS)
driver.o: driver.c
	$(CC) $(CFLAGS) $(INC) -c driver.c
hash_table.o: ../hash_table/hash_table.h ../hash_table/hash_table.c
	$(CC) $(CFLAGS) $(INC) -c ../hash_table/hash_table.c
hash.o: ../hash_table/hash/hash.h ../hash_table/hash/hash.c
	$(CC) $(CFLAGS) $(INC) -c ../hash_table/hash/hash.c
portfolio.o: portfolio.h portfolio.c
	$(CC) $(CFLAGS) $(INC) -c portfolio.c
.PHONY: clean
clean:
	rm -rf *.o driver
