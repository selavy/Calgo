CC = gcc
CFLAGS = -fPIC
INC = -L./ -lmy_function

LD = -ldl
OBJS = main.o
LIBS_FILES = my_function.o
LIBS = libmy_function.so

dynamic: $(OBJS) $(LIBS)
	$(CC) -o dynamic $(CFLAGS) $(OBJS) $(LD)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
shared_lib: $(LIBS) dynamic_main.o
	$(CC) -o shared_lib $(CFLAGS) $(INC) dynamic_main.o
dynamic_main.o: dynamic_main.c
	$(CC) $(CFLAGS) -c dynamic_main.c
libmy_function.so: $(LIBS_FILES)
	$(CC) -o libmy_function.so -shared -Wl,-soname,libmy_function.so $(LIBS_FILES)
my_function.o: my_function.h my_function.c
	$(CC) $(CFLAGS) -c my_function.c
.PHONY: clean
clean:
	rm -rf *.o dynamic shared_lib *.so
