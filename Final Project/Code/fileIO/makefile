CC = gcc
OBJS = fileIOTester.o fileIO.o boardUtils.o
FLAGS = -g
EXEC = fileIOTester
COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors -g

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(FLAGS)

fileIOTester.o: fileIOTester.c fileIO.h
	$(CC) $(COMP_FLAG) -c $*.c

fileIO.o:  fileIO.c  fileIO.h ../boardUtils.h
	$(CC) $(COMP_FLAG) -c $*.c

boardUtils.o:  ../boardUtils.c  ../boardUtils.h
	$(CC) $(COMP_FLAG) -c ../boardUtils.c

clean:
	rm -f $(OBJS) $(EXEC)
