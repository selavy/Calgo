CC = gcc
CPP = g++
DEBUG = -g
NOTDEBUG = -Ofast -fomit-frame-pointer
CFLAGS = -pedantic -fPIC $(NOTDEBUG)
PERMISSIVE = -fpermissive
INC = -I./include/ -I./portfolio/ -I./hash_table/ -I./database/ -I./queue/ -I./engine/
OBJS = main.o hash.o hash_table.o database.o queue.o engine.o portfolio.o
LD = -ldl
PYTHON = -I/usr/include/python2.7 -lpython2.7
SHARED = -shared -Wl,-soname,
PRINT_STATUS = #-D_PRINT_

#calgo: $(OBJS)
#	$(CC) -o calgo $(CFLAGS) $(INC) $(OBJS) $(LD) $(PYTHON)
#	python algoenginesetup.py build
calgo: ./build/ main.c
	mv ./build/lib.linux-x86_64-2.7/* .
	ln -sf algoengine.so libalgoengine.so
	$(CC) -o calgo $(CFLAGS) $(INC) main.c $(LD) $(PYTHON) -L. -lalgoengine
./build/: algoenginemodule.c
	python algoenginesetup.py build
.PHONY: clean
clean:
	rm -rf *.o *.so calgo build/ *.pyc
