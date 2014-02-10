CC = gcc
CPP = g++
CFLAGS = -Wall -Werror -pedantic -g
CPPFLAGS = $(CFLAGS) -std=c++11

OBJS = hash_table.o driver.o hash.o

driver: $(OBJS)
	$(CC) -o driver $(CFLAGS) $(OBJS)
cppdriver: cppdriver.cpp
	$(CPP) -o cppdriver $(CPPFLAGS) cppdriver.cpp
hash_table.o: hash_table.h hash_table.c
	$(CC) $(CFLAGS) -c hash_table.c
driver.o: driver.c
	$(CC) $(CFLAGS) -c driver.c
hash.o: ./hash/hash.h ./hash/hash.c
	$(CC) $(CFLAGS) -c ./hash/hash.c
.PHONY: clean
clean:
	rm -rf *.o driver cppdriver