CC = gcc
OBJS = dllTester.o LinkedList.o boardUtils.o
FLAGS = -g
EXEC = dllTester
COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors -g

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(FLAGS)

dllTester.o: dllTester.c LinkedList.h ../boardUtils/boardUtils.h ../boardUtils/boardEntities.h 
	$(CC) $(COMP_FLAG) -c $*.c

LinkedList.o: LinkedList.h LinkedList.c ../boardUtils/boardUtils.h ../boardUtils/boardEntities.h
	$(CC) $(COMP_FLAG) -c $*.c

boardUtils.o: ../boardUtils/boardUtils.c ../boardUtils/boardUtils.h ../boardUtils/boardEntities.h
	$(CC) $(COMP_FLAG) -c ../boardUtils/boardUtils.c

clean:
	rm -f $(OBJS) $(EXEC)
