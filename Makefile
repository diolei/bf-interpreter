CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic

SRCS = brainfuck.c
EXEC = brainfuck

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC) 

clean:
	rm -f $(EXEC)
