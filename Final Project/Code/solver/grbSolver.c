#include "grbSolver.h"


/* static module variables for the gurobi environment */
static GRBenv* grbEnv = NULL;


int initGrbEnvironment() {

	GRBenv **envPtr = &grbEnv;
	int error;

	/* Create environment for solving */
	error = GRBloadenv( envPtr, GUROBI_LOG_FILE_NAME );
	if ( error ) {
		printf( "GRBloadenv ERROR (%d): %s\n", error, GRBgeterrormsg( *envPtr ) );
		closeGrbEnvironment( *envPtr );
		return FALSE;
	}

	/* Do not log to console */
	error = GRBsetintparam( *envPtr, GRB_INT_PAR_LOGTOCONSOLE, 0 );
	if ( error ) {
		printf( "GRBsetintparam ERROR (%d): %s\n", error, GRBgeterrormsg( *envPtr ) );
		closeGrbEnvironment( *envPtr );
		return FALSE;
	}

	return TRUE;
}


void closeGrbEnvironment() {
	/* Free environment */
	if ( NULL != grbEnv ) {
		GRBfreeenv( grbEnv );
	}
}


int runGurobiSolver( BoardCell** orig_board, int boxW, int boxH ) {
	GRBmodel 	*model = NULL;
	int 		dim = boxW*boxH, optimizationStatus = 0, error = 0, 
				*indexArr = NULL, **board = NULL;
	char 		*valType = NULL, **names = NULL, *nameStorage = NULL;
	double 		*constraintValArr = NULL, *lowerBoundsArr = NULL, *sol = NULL;

	if (!allocateGrbMem(grbEnv, model, dim, &indexArr, &constraintValArr, 
						&lowerBoundsArr, &valType, &names, &nameStorage, 
						&sol, &board) ) {
		return FALSE;
	}

	/* copy sudoku board to gurobi 2D array */
	sudokuBoardToGrbBoard(board, orig_board, dim);

	/* Create a new empty model */
	createEmptyGrbModel(board, dim, nameStorage, lowerBoundsArr, valType, names);

	/* Create new model */
	error = GRBnewmodel( grbEnv, &model, GUROBI_LOG_MODEL_NAME, dim*dim*dim, NULL, lowerBoundsArr, NULL, valType, names );
	if ( error ) {
		printf( "GRBnewmodel ERROR (%d): %s\n", error, GRBgeterrormsg( grbEnv ) );
		freeGrbMem( grbEnv, model, dim, indexArr, constraintValArr, lowerBoundsArr, valType, names, nameStorage, sol, board );
		return FALSE;
	}

	/* set constraints for the model */
	if ( !setGrbModelConstraints(	grbEnv, model, dim, boxW, boxH, indexArr, 
							constraintValArr, lowerBoundsArr, valType, names, 
							nameStorage, sol, board ) ) {
		freeGrbMem( grbEnv, model, dim, indexArr, constraintValArr, lowerBoundsArr, valType, names, nameStorage, sol, board );
		return FALSE;
	}

	/* Optimize model */
	error = GRBoptimize( model );
	if ( error ) {
		printf( "GRBoptimize ERROR (%d): %s\n", error, GRBgeterrormsg( grbEnv ) );
		freeGrbMem( grbEnv, model, dim, indexArr, constraintValArr, lowerBoundsArr, valType, names, nameStorage, sol, board );
		return FALSE;
	}

	/* Write model info to GUROBI_LP_FILE_NAME */
	error = GRBwrite( model, GUROBI_LP_FILE_NAME );
	if ( error ) {
		printf( "GRBwrite ERROR (%d): %s\n", error, GRBgeterrormsg( grbEnv ) );
		freeGrbMem( grbEnv, model, dim, indexArr, constraintValArr, lowerBoundsArr, valType, names, nameStorage, sol, board );
		return FALSE;
	}

	/* Get solution information */
	error = GRBgetintattr( model, GRB_INT_ATTR_STATUS, &optimizationStatus );
	if ( error ) {
		printf( "GRBgetintattr ERROR (%d): %s\n", error, GRBgeterrormsg( grbEnv ) );
		freeGrbMem( grbEnv, model, dim, indexArr, constraintValArr, lowerBoundsArr, valType, names, nameStorage, sol, board );
		return FALSE;
	}

	/* Return false if not feasable or not bounded */
	if ( optimizationStatus == GRB_OPTIMAL ) {
	} else if (optimizationStatus == GRB_INF_OR_UNBD) {
		freeGrbMem( grbEnv, model, dim, indexArr, constraintValArr, lowerBoundsArr, valType, names, nameStorage, sol, board );
		return FALSE;
	} else {
		freeGrbMem( grbEnv, model, dim, indexArr, constraintValArr, lowerBoundsArr, valType, names, nameStorage, sol, board );
		return FALSE;
	}

	/* Get the optimized solution variables values */
	error = GRBgetdblattrarray( model, GRB_DBL_ATTR_X, 0, dim*dim*dim, sol );
	if ( error ) {
		printf( "GRBgetdblattrarray ERROR (%d): %s\n", error, GRBgeterrormsg( grbEnv ) );
		freeGrbMem( grbEnv, model, dim, indexArr, constraintValArr, lowerBoundsArr, valType, names, nameStorage, sol, board );
		return FALSE;
	}

	/* Write results back to orig_board */
	grbBoardToSudokuBoard(orig_board, sol, dim);

	/* free resources */
	freeGrbMem( grbEnv, model, dim, indexArr, constraintValArr, lowerBoundsArr, valType, names, nameStorage, sol, board );
	return TRUE;
}


void createEmptyGrbModel(int **board, int dim, char* nameStorage, double *lowerBoundsArr, char *valType, char **names) {
	char *cursor = nameStorage;
	int y = 0, x = 0, v = 0;

	for ( y = 0; y < dim; y++ ) {
		for ( x = 0; x < dim; x++ ) {
			for ( v = 0; v < dim; v++ ) {
				if ( board[y][x] == v ) {
					lowerBoundsArr[y*dim*dim+x*dim+v] = 1;
				} else {
					lowerBoundsArr[y*dim*dim+x*dim+v] = 0;
				}
				valType[y*dim*dim+x*dim+v] = GRB_BINARY;

				names[y*dim*dim+x*dim+v] = cursor;
				sprintf( names[y*dim*dim+x*dim+v], "x[%d,%d,%d]", y, x, v+1 );
				cursor += strlen( names[y*dim*dim+x*dim+v] ) + 1;
			}
		}
	}
}


void sudokuBoardToGrbBoard(int** board, BoardCell** sudokuBoard, int dim) {
	int y = 0, x = 0;
	
	for (y = 0; y < dim; y++ ) {
		for (x = 0; x < dim; x++ ) {
			board[y][x] = sudokuBoard[y*dim + x]->val - 1;
		}
	}
}


void grbBoardToSudokuBoard(BoardCell** sudokuBoard, double* sol, int dim) {
	int x, y;
	for ( y = 0; y < dim*dim*dim; y += dim ) {
		for ( x = 0 ; x < dim ; x++  ) {
			if (  ( int )sol[y + x] == 1  ) {
				/* store result in relevant cell */
				sudokuBoard[y/dim]->val = x + 1;
				/*printf( "%d,", x + 1 );*/
			}
		}
		/* if ( ( y/dim ) % dim == ( dim-1 ) ) printf( "\n" ); */
	}
}



int setGrbModelConstraints(	GRBenv *grbEnv, GRBmodel *model, int dim, int boxW, int boxH, int* indexArr, 
							double* constraintValArr, double* lowerBoundsArr, char* valType, char** names, 
							char* nameStorage, double* sol, int* board[] ) {
	
	int x, y, v, xBox, yBox, count, error;

	/* Each cell in the board must have one value */
	for ( y = 0; y < dim; y++ ) {
		for ( x = 0; x < dim; x++ ) {
			for ( v = 0; v < dim; v++ ) {
				indexArr[v] = y*dim*dim + x*dim + v;
				constraintValArr[v] = 1.0;
			}

			error = GRBaddconstr( model, dim, indexArr, constraintValArr, GRB_EQUAL, 1.0, NULL );
			if ( error ) {
				printf( "GRBaddconstr ERROR (%d): %s\n", error, GRBgeterrormsg( grbEnv ) );
				freeGrbMem( grbEnv, model, dim, indexArr, constraintValArr, lowerBoundsArr, valType, names, nameStorage, sol, board );
				return FALSE;
			}
		}
	}

	/* Each value must appear once in each row */
	for ( v = 0; v < dim; v++ ) {
		for ( x = 0; x < dim; x++ ) {
			for ( y = 0; y < dim; y++ ) {
				indexArr[y] = y*dim*dim + x*dim + v;
				constraintValArr[y] = 1.0;
			}

			error = GRBaddconstr( model, dim, indexArr, constraintValArr, GRB_EQUAL, 1.0, NULL );
			if ( error ) {
				printf( "GRBaddconstr ERROR (%d): %s\n", error, GRBgeterrormsg( grbEnv ) );
				freeGrbMem( grbEnv, model, dim, indexArr, constraintValArr, lowerBoundsArr, valType, names, nameStorage, sol, board );
				return FALSE;
			}
		}
	}

	/* Each value must appear once in each column */
	for ( v = 0; v < dim; v++ ) {
		for ( y = 0; y < dim; y++ ) {
			for ( x = 0; x < dim; x++ ) {
				indexArr[x] = y*dim*dim + x*dim + v;
				constraintValArr[x] = 1.0;
			}

			error = GRBaddconstr( model, dim, indexArr, constraintValArr, GRB_EQUAL, 1.0, NULL );
			if ( error ) {
				printf( "GRBaddconstr ERROR (%d): %s\n", error, GRBgeterrormsg( grbEnv ) );
				freeGrbMem( grbEnv, model, dim, indexArr, constraintValArr, lowerBoundsArr, valType, names, nameStorage, sol, board );
				return FALSE;
			}
		}
	}

	/* Each value must appear once in each box */
	for ( v = 0; v < dim; v++ ) {
		for ( yBox = 0; yBox < boxW; yBox++ ) {
			for ( xBox = 0; xBox < boxH; xBox++ ) {
				count = 0;
				for ( y = yBox*boxH; y < ( yBox+1 )*boxH; y++ ) {
					for ( x = xBox*boxW; x < ( xBox+1 )*boxW; x++ ) {
						indexArr[count] = y*dim*dim + x*dim + v;
						constraintValArr[count] = 1.0;
						count++;
					}
				}

				error = GRBaddconstr( model, dim, indexArr, constraintValArr, GRB_EQUAL, 1.0, NULL );
				if ( error ) {
					printf( "GRBaddconstr ERROR (%d): %s\n", error, GRBgeterrormsg( grbEnv ) );
					freeGrbMem( grbEnv, model, dim, indexArr, constraintValArr, lowerBoundsArr, valType, names, nameStorage, sol, board );
					return FALSE;
				}
			}
		}
	}

	return TRUE;
}


int allocateGrbMem(	GRBenv *env, GRBmodel *model, int dim, int** indexArr, double** constraintValArr, 
					double** lowerBoundsArr, char** valType, char*** names, char** nameStorage, 
					double** sol, int** board[] ) {
	int y;

	*board = (int**)malloc( dim * sizeof(int*));
	if (NULL == *board) {
		printf("runGurobiSolver ERROR: memory allocation error.\n");
		freeGrbMem(env, model, dim, *indexArr, *constraintValArr, *lowerBoundsArr, *valType, *names, *nameStorage, *sol, *board);
		return FALSE;
	}

	for (y = 0 ; y < dim ; y++ ) {
		(*board)[y] = (int*)malloc( dim * sizeof(int) );
		if (NULL == (*board)[y]) {
			printf("runGurobiSolver ERROR: memory allocation error.\n");
			freeGrbMem(env, model, dim, *indexArr, *constraintValArr, *lowerBoundsArr, *valType, *names, *nameStorage, *sol, *board);
			return FALSE;
		}
	}

	*indexArr = (int*)malloc( dim * sizeof(int) );
	if (NULL == *indexArr) {
		printf("runGurobiSolver ERROR: memory allocation error.\n");
		freeGrbMem(env, model, dim, *indexArr, *constraintValArr, *lowerBoundsArr, *valType, *names, *nameStorage, *sol, *board);
		return FALSE;
	}

	*constraintValArr = (double*)malloc( dim * sizeof(double) );
	if (NULL == *constraintValArr) {
		printf("runGurobiSolver ERROR: memory allocation error.\n");
		freeGrbMem(env, model, dim, *indexArr, *constraintValArr, *lowerBoundsArr, *valType, *names, *nameStorage, *sol, *board);
		return FALSE;
	}

	*lowerBoundsArr = (double*)malloc( dim*dim*dim * sizeof(double) );
	if (NULL == *lowerBoundsArr) {
		printf("runGurobiSolver ERROR: memory allocation error.\n");
		freeGrbMem(env, model, dim, *indexArr, *constraintValArr, *lowerBoundsArr, *valType, *names, *nameStorage, *sol, *board);
		return FALSE;
	}

	*valType = (char*)malloc( dim*dim*dim * sizeof(char) );
	if (NULL == *valType) {
		printf("runGurobiSolver ERROR: memory allocation error.\n");
		freeGrbMem(env, model, dim, *indexArr, *constraintValArr, *lowerBoundsArr, *valType, *names, *nameStorage, *sol, *board);
		return FALSE;
	}

	*names = (char**)malloc( dim*dim*dim * sizeof(char*) );
	if (NULL == *names) {
		printf("runGurobiSolver ERROR: memory allocation error.\n");
		freeGrbMem(env, model, dim, *indexArr, *constraintValArr, *lowerBoundsArr, *valType, *names, *nameStorage, *sol, *board);
		return FALSE;
	}

	*nameStorage = (char*)malloc( (NAME_MIN_LEN > dim ? NAME_MIN_LEN : dim)*dim*dim*dim * sizeof(char) );
	if (NULL == *nameStorage) {
		printf("runGurobiSolver ERROR: memory allocation error.\n");
		freeGrbMem(env, model, dim, *indexArr, *constraintValArr, *lowerBoundsArr, *valType, *names, *nameStorage, *sol, *board);
		return FALSE;
	}

	*sol = (double*)malloc( dim*dim*dim * sizeof(double) );
	if (NULL == *sol) {
		printf("runGurobiSolver ERROR: memory allocation error.\n");
		freeGrbMem(env, model, dim, *indexArr, *constraintValArr, *lowerBoundsArr, *valType, *names, *nameStorage, *sol, *board);
		return FALSE;
	}

	return TRUE;
}


void freeGrbMem(GRBenv *env, GRBmodel *model, int dim, int* indexArr, double* constraintValArr, 
				double* lowerBoundsArr, char* valType, char** names, char* nameStorage, double* sol, 
				int* board[] ) {

	int i;
	long e = (long) env;
	i = (int)e;

	/* Free model */
	if ( NULL != model ) {
		GRBfreemodel( model );
	}

	if ( NULL != indexArr ) free( indexArr );
	if ( NULL != constraintValArr ) free( constraintValArr );
	if ( NULL != lowerBoundsArr ) free( lowerBoundsArr );
	if ( NULL != valType ) free( valType );
	if ( NULL != names ) free( names );
	if ( NULL != nameStorage ) free( nameStorage );
	if ( NULL != sol ) free( sol );

	if ( NULL != board ) {
		for ( i = 0 ; i < dim ; i++  ) {
			if ( NULL != board[i] ) {
				free( board[i] );
			}
		}
		free( board );
	}

}

