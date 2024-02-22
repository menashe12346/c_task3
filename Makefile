CC = gcc
CFLAGS = -Wall -g

all: libclassStrList.a StrList

StrList.o: StrList.c StrList.h
	$(CC) $(CFLAGS) -c $<

libclassStrList.a: StrList.o
	ar rcu $@ $^

Main.o: Main.c StrList.h
	$(CC) $(CFLAGS) -c $<

StrList: Main.o libclassStrList.a
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o *.a StrList