C = gcc

OBJS = main.o hash.o

proj: $(OBJS)
	$(C) -o proj $(OBJS)
ttest: time_test.o $(OBJS)
	$(C) -o ttest time_test.o hash.o
main.o: main.c
	$(C) -c main.c
hash.o: hash.h hash.c
	$(C) -c hash.c
time_test.o: time_test.c
	$(C) -c time_test.c
cleaner: cleaner.c
	$(C) -o cleaner cleaner.c
.PHONY: clean
clean:
	rm -rf *.o proj ttest
