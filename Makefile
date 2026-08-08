CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -O2

SRCS = brainfuck.c
EXEC = brainfuck

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC)

clean:
	rm -f $(EXEC)
