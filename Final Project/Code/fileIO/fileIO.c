#include "fileIO.h"

/*
 * is given char 'c' a whitespace
 */
int isCharWS(char c) {
	return ( (' ' == c) || ('\n' == c) || ('\t' == c) || ('\r' == c) || 
			 ('\f' == c) || ('\v' == c) );
}


int loadBoardFromFile(char* filePath, BoardCell**** boardp, int* bwp, int* bhp) 
{
	FILE* ifp;
	BoardCell** board;
	int w, h, num, isCellFixed, i = 0;
	char c;

	/* check that path is not NULL */
	if (NULL == filePath) {
		return FALSE;
	}

	/* open file for reading */
	ifp = fopen(filePath, "r");

	if ( NULL == ifp ) {
		return FALSE;
	}
	
	/* read board box dimensions */
	if (FILE_NUMBERS_IN_FIRST_LINE != fscanf(ifp, "%d %d", bhp, bwp) ) {
		return FALSE;
	}

	w = h = (*bwp) * (*bhp);

	/* allocate a new board */
	*boardp = allocateBoard(w, h);

	if (boardp == NULL) {
		printf("board is null!\n");
		return FALSE;
	}

	/* also without asterisk merely for convenience  */
	board = **boardp;

	/* read board values from file */
	while ( (i < w*h) && (1 == fscanf(ifp, "%d", &num)) ) {
		/* check if the next char is EOF or '.' meaning it is a fixed cell */
		/* first, consume whitespaces (so the cursor is set to a non-whitespace character) */
		while ( isCharWS(c = fgetc(ifp)) );

		/* if the next non-whitespace character is the 'fixed cell' char, then the cell is fixed */
		isCellFixed = (FILE_FIXED_CELL_CHAR == c);

		if (!isCellFixed) {
			/* go back one character in the stream */
			if ( 0 != fseek(ifp, -1L, SEEK_CUR) ) {
				fclose(ifp);
				return FALSE;
			}
		}

		board[i]->val = num;
		board[i]->isUserSet = (0 != num && !isCellFixed);
		board[i]->isError = FALSE;
		board[i]->isFixed = isCellFixed;

		i++;
	}

	fclose(ifp);

	return TRUE;
}


int saveBoardToFile(char* filePath, BoardCell*** board, int bw, int bh) {
	FILE* ofp;
	BoardCell* cell;
	int x, y;
	int N = bw * bh;

	/* check that path is not NULL */
	if (NULL == filePath) {
		return FALSE;
	}

	/* open file for reading */
	ofp = fopen(filePath, "w");

	if ( NULL == ofp ) {
		return FALSE;
	}
	
	/* write board box dimensions, return on failure */
	if ( 0 > fprintf(ofp, "%d %d\n", bh, bw) ) {
		fclose(ofp);
		return FALSE;
	}

	/* write board values */
	for ( y = 0 ; y < N ; y++ ) {
		for ( x = 0 ; x < N ; x++ ) {

			cell = board[y][x];

			if ( NULL == cell ) {
				return FALSE;
			}


			/* write cell value to file */
			if ( 0 > fprintf(ofp, "%d", cell->val) ) {
				fclose(ofp);
				return FALSE;
			}


			/* write is fixed character to file */
			if ( cell->isFixed ) {
				if ( 0 > fprintf(ofp, "%c",FILE_FIXED_CELL_CHAR ) ) {
					fclose(ofp);
					return FALSE;
				}				
			}

			/* fprintf(ofp, "%d%c", cell->val, (cell->isFixed ? FILE_FIXED_CELL_CHAR : '' ) ); */

			/* do not write space after the last cell */
			if ( x != N - 1 ) {
				if ( 0 > fprintf(ofp, " ") ) {
					fclose(ofp);
					return FALSE;
				}				
			}

		}

		/* start a new line */
		if ( 0 > fprintf(ofp, "\n") ) {
			fclose(ofp);
			return FALSE;
		}				
	}

	fclose(ofp);

	return TRUE;
}
