CC = gcc
OBJS = grbSolverTester.o grbSolver.o boardUtils.o
FLAGS = -g -lm
EXEC = grbSolverTester
COMP_FLAG = -ansi -O3 -Wall -Wextra -Werror -pedantic-errors -g

GUROBI_COMP = -I/usr/local/lib/gurobi563/include
GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56


$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(GUROBI_LIB) $(FLAGS)

grbSolverTester.o: grbSolverTester.c grbSolver.h ../boardUtils/boardUtils.h ../boardUtils/boardEntities.h 
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

grbSolver.o: grbSolver.h grbSolver.c ../boardUtils/boardUtils.h ../boardUtils/boardEntities.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c

boardUtils.o: ../boardUtils/boardUtils.c ../boardUtils/boardUtils.h ../boardUtils/boardEntities.h
	$(CC) $(COMP_FLAG) -c ../boardUtils/boardUtils.c

clean:
	rm -f $(OBJS) $(EXEC)
