CC = gcc
OBJS = main.o parser.o game.o solver.o boardUtils.o
FLAGS = -lm -g
#OBJS = main.o main_aux.o sp_nim.o
EXEC = sudoku
COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors -g

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(FLAGS)

main.o: main.c game.h solver.h parser.h boardEntities.h
	$(CC) $(COMP_FLAG) -c $*.c

parser.o: parser.c parser.h SPBufferset.h
	$(CC) $(COMP_FLAG) -c $*.c

game.o: game.c game.h solver.h parser.h boardEntities.h
	$(CC) $(COMP_FLAG) -c $*.c

boardUtils.o: boardUtils.c boardUtils.h boardEntities.h
	$(CC) $(COMP_FLAG) -c $*.c

solver.o: solver.c solver.h boardEntities.h boardUtils.h
	$(CC) $(COMP_FLAG) -c $*.c

clean:
	rm -f $(OBJS) $(EXEC)
