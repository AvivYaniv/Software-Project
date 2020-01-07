CC = gcc
OBJDIR = objs

GUROBI_COMP = -I/usr/local/lib/gurobi563/include

# two solvers possible, default is gurobi ILP. If 'SOLVER_BT' flag was given, backtrack solver 
# will be used (for local testing purposes) 
ifndef SOLVER_BT
	OBJS = $(OBJDIR)/main.o $(OBJDIR)/grbSolver.o $(OBJDIR)/parser.o $(OBJDIR)/gameLogic.o $(OBJDIR)/boardUtils.o $(OBJDIR)/LinkedList.o $(OBJDIR)/fileIO.o $(OBJDIR)/solver.o $(OBJDIR)/Stack.o
	IS_BT_FLAG = 
	GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56
	COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors -g $(GUROBI_COMP)
else
	OBJS = $(OBJDIR)/main.o $(OBJDIR)/parser.o $(OBJDIR)/gameLogic.o $(OBJDIR)/boardUtils.o $(OBJDIR)/LinkedList.o $(OBJDIR)/fileIO.o $(OBJDIR)/solver.o $(OBJDIR)/Stack.o
	IS_BT_FLAG = -DSOLVER_BT 
	GUROBI_LIB = 
	COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors -g
endif

FLAGS = -lm -g
EXEC = sudoku-console



all : $(EXEC)
.PHONY : all

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(GUROBI_LIB) $(FLAGS)

$(OBJDIR)/main.o: main.c gameLogic/gameLogic.h parser/parser.h solver/solver.h boardUtils/boardUtils.h boardUtils/boardEntities.h
	$(CC) $(COMP_FLAG) -c main.c -o $@ $(IS_BT_FLAG)

ifndef SOLVER_BT
$(OBJDIR)/grbSolver.o: solver/grbSolver.h solver/grbSolver.c boardUtils/boardUtils.h boardUtils/boardEntities.h
	$(CC) $(COMP_FLAG) -c solver/grbSolver.c -o $@  
endif

$(OBJDIR)/solver.o: solver/solver.c solver/solver.h solver/grbSolver.h boardUtils/boardUtils.h boardUtils/boardEntities.h
	$(CC) $(COMP_FLAG) -c solver/solver.c -o $@  $(IS_BT_FLAG)


$(OBJDIR)/parser.o: parser/parser.c parser/parser.h SPBufferset/SPBufferset.h
	$(CC) $(COMP_FLAG) -c parser/parser.c -o $@ 

$(OBJDIR)/fileIO.o: fileIO/fileIO.c fileIO/fileIO.h boardUtils/boardUtils.h boardUtils/boardEntities.h
	$(CC) $(COMP_FLAG) -c fileIO/fileIO.c -o $@ 

$(OBJDIR)/gameLogic.o: gameLogic/gameLogic.c gameLogic/gameLogic.h parser/parser.h boardUtils/boardEntities.h
	$(CC) $(COMP_FLAG) -c gameLogic/gameLogic.c -o $@ $(IS_BT_FLAG)

$(OBJDIR)/boardUtils.o: boardUtils/boardUtils.c boardUtils/boardUtils.h boardUtils/boardEntities.h
	$(CC) $(COMP_FLAG) -c boardUtils/boardUtils.c -o $@ 

$(OBJDIR)/LinkedList.o: LinkedList/LinkedList.c LinkedList/LinkedList.h boardUtils/boardUtils.h boardUtils/boardEntities.h 
	$(CC) $(COMP_FLAG) -c LinkedList/LinkedList.c -o $@ 

$(OBJDIR)/Stack.o: Stack/Stack.c Stack/Stack.h boardUtils/boardUtils.h boardUtils/boardEntities.h
	$(CC) $(COMP_FLAG) -c Stack/Stack.c -o $@ 


clean:
	rm -f $(OBJS) $(EXEC)
