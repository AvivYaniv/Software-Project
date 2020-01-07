CC = gcc
OBJS = parserTester.o parser.o
FLAGS = -g 
EXEC = parserTester
COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors -g -DDEBUG

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(FLAGS)

parserTester.o: parserTester.c parser.h
	$(CC) $(COMP_FLAG) -c $*.c

parser.o: parser.c parser.h
	$(CC) $(COMP_FLAG) -c $*.c

clean:
	rm -f $(OBJS) $(EXEC)
