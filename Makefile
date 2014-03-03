CC = gcc
DEBUG = -g
NOTDEBUG = -Ofast -fomit-frame-pointer
CFLAGS = -pedantic -fPIC $(NOTDEBUG)
INC = -I./include/ -I./portfolio/ -I./hash_table/ -I./database/ -I./queue/ -I./engine/
OBJS = main.o hash.o hash_table.o database.o queue.o engine.o portfolio.o
LD = -ldl
SHARED = -shared -Wl,-soname,
PRINT_STATUS = -D_PRINT_

calgo: $(OBJS) libstrategy.so
	$(CC) -o calgo $(LD) $(CFLAGS) $(INC) $(OBJS)
libstrategy.so: strategy.o engine.o backtest.o
	$(CC) -o libstrategy.so -fPIC -shared -Wl,-soname,libstrategy.so strategy.o engine.o portfolio.o queue.o hash_table.o hash.o database.o backtest.o
strategy.o: strategy.h strategy.c
	$(CC) $(CFLAGS) $(INC) -c strategy.c
backtest.o: backtest.h backtest.c
	$(CC) $(CFLAGS) $(INC) -c backtest.c
main.o: main.c
	$(CC) $(CFLAGS) $(INC) -c main.c
hash.o: ./hash_table/hash/hash.h ./hash_table/hash/hash.c
	$(CC) $(CFLAGS) $(INC) -c ./hash_table/hash/hash.c
hash_table.o: ./hash_table/hash_table.h ./hash_table/hash_table.c
	$(CC) $(CFLAGS) $(INC) -c ./hash_table/hash_table.c
database.o: ./database/database.h ./database/database.c
	$(CC) $(CFLAGS) $(INC) -c ./database/database.c
queue.o: ./queue/queue.h ./queue/queue.c
	$(CC) $(CFLAGS) $(INC) -c ./queue/queue.c
engine.o: ./engine/engine.h ./engine/engine.c
	$(CC) $(CFLAGS) $(INC) $(PRINT_STATUS) -c ./engine/engine.c
portfolio.o: ./portfolio/portfolio.h ./portfolio/portfolio.c
	$(CC) $(CFLAGS) $(INC) -c ./portfolio/portfolio.c

.PHONY: clean
clean:
	rm -rf *.o *.so calgo
