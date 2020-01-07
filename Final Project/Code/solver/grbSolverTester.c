#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gurobi_c.h"

#include "grbSolver.h"



void tester3x2() {
	int boxW = 3;
	int boxH = 2;
	int N = boxW*boxH;
	int res = 0;
	BoardCell*** board = allocateBoard(N, N);

	board[0][0]->val = 2;
	board[0][1]->val = 3;
	board[0][2]->val = 4;

	/*printf("%d, %d, %d, %d \n", boxW, boxH, N, res);*/
	printBoard(*board, boxW, boxH, FALSE, FALSE);

	res = runGurobiSolver(*board, boxW, boxH);

	if (res) {
		printf("board is solvable\n");
	} else {
		printf("board is unsolvable\n");
	}

	printBoard(*board, boxW, boxH, FALSE, FALSE);

	printf("======================\n");
	zerosBoard(board, N, N);
	board[0][0]->val = 2;
	board[0][1]->val = 3;
	board[0][2]->val = 4;
	board[1][4]->val = 5;

	printBoard(*board, boxW, boxH, FALSE, FALSE);

	res = runGurobiSolver(*board, boxW, boxH);

	if (res) {
		printf("board is solvable\n");
	} else {
		printf("board is unsolvable\n");
	}

	printBoard(*board, boxW, boxH, FALSE, FALSE);


}


void tester3x3() {
	int boxW = 3;
	int boxH = 3;
	int N = boxW*boxH;
	int res = 0;
	BoardCell*** board = allocateBoard(N, N);

	board[0][0]->val = 2;
	board[0][1]->val = 1;
	board[0][2]->val = 5;

	/*printf("%d, %d, %d, %d \n", boxW, boxH, N, res);*/
	printBoard(*board, boxW, boxH, FALSE, FALSE);

	res = runGurobiSolver(*board, boxW, boxH);

	if (res) {
		printf("board is solvable\n");
	} else {
		printf("board is unsolvable\n");
	}

	printBoard(*board, boxW, boxH, FALSE, FALSE);

	printf("======================\n");
	zerosBoard(board, N, N);
	board[0][0]->val = 2;
	board[0][1]->val = 1;
	board[0][2]->val = 5;
	board[1][4]->val = 3;
	board[2][7]->val = 3;

	printBoard(*board, boxW, boxH, FALSE, FALSE);

	res = runGurobiSolver(*board, boxW, boxH);

	if (res) {
		printf("board is solvable\n");
	} else {
		printf("board is unsolvable\n");
	}

	printBoard(*board, boxW, boxH, FALSE, FALSE);

	printf("======================\n");
	zerosBoard(board, N, N);
	board[0][0]->val = 2;
	board[0][1]->val = 1;
	board[0][2]->val = 5;
	board[2][7]->val = 3;

	printBoard(*board, boxW, boxH, FALSE, FALSE);

	res = runGurobiSolver(*board, boxW, boxH);

	if (res) {
		printf("board is solvable\n");
	} else {
		printf("board is unsolvable\n");
	}

	printBoard(*board, boxW, boxH, FALSE, FALSE);


	freeBoard(board, N, N);

}

int main()
{

	/* initial values for static module variables */
	/*GRBenv* grbEnv = NULL;*/

	if ( !initGrbEnvironment() ) {
		printf("error: could not initialize gurobi solver\n");
		return -1;
	}

	tester3x3();
	printf("---------------------------------\n");
	tester3x2();
	printf("---------------------------------\n");
	tester3x3();

	closeGrbEnvironment();

	return 0;
}