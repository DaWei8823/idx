CC=gcc
CFLAGS=-I. -g -D TEST -Wall
SRCS=$(wildcard *.c) $(wildcard test/*.c)
OBJS=${SRCS:.c=.o}

DEPS=$(wildcard *.h)

all: tests clean

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tests: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)	

run: tests
	./tests

debug: tests
	gdb tests

clean:
	rm *.o
