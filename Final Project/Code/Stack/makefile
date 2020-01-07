CC = gcc
OBJS = stackTester.o Stack.o boardUtils.o
FLAGS = -g
EXEC = stackTester
COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors -g

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(FLAGS)

stackTester.o: stackTester.c Stack.h ../boardUtils/boardUtils.h ../boardUtils/boardEntities.h 
	$(CC) $(COMP_FLAG) -c $*.c

Stack.o: Stack.h Stack.c ../boardUtils/boardUtils.h ../boardUtils/boardEntities.h
	$(CC) $(COMP_FLAG) -c $*.c

boardUtils.o: ../boardUtils/boardUtils.c ../boardUtils/boardUtils.h ../boardUtils/boardEntities.h
	$(CC) $(COMP_FLAG) -c ../boardUtils/boardUtils.c

clean:
	rm -f $(OBJS) $(EXEC)
