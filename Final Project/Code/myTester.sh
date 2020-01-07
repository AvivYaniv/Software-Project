#!/bin/sh

# myTester.sh
# 
# How to use: 	1. Place this script and the 'tests' folder in the same folder as the 'sudoku-console' is.
# 				2. Run in terminal './myTester.sh' 
# 				3. If nothing is printed between the test names lines, the test was passed.


# delete previous test results 
rm tests/observed/*.txt
rm tests/observed/*.out

echo "---------- solve ----------"
./sudoku-console < tests/solveTest.in > tests/observed/solve.out
diff ./tests/expected/solve.out 				./tests/observed/solve.out
diff ./tests/expected/solve_board.txt	 		./tests/observed/solve_board.txt


echo "---------- undo ----------"
./sudoku-console < tests/undoTest.in > tests/observed/undo.out
diff ./tests/expected/undo.out 					./tests/observed/undo.out


echo "---------- init mode ----------"
./sudoku-console < tests/initModeTest.in > tests/observed/initMode.out
diff ./tests/expected/initMode.out 			./tests/observed/initMode.out


echo "---------- edit ----------"
./sudoku-console < tests/editTest.in > tests/observed/editTest.out
diff ./tests/expected/editTest.out 				./tests/observed/editTest.out
diff ./tests/expected/edit_out_board2.txt 		./tests/observed/edit_out_board2.txt



echo "---------- mark_errors ----------"
./sudoku-console < tests/mark_errorsTest.in > tests/observed/mark_errorsTest.out
diff ./tests/expected/mark_errorsTest.out 				./tests/observed/mark_errorsTest.out


echo "---------- set ----------"
./sudoku-console < tests/setTest.in > tests/observed/setTest.out
diff ./tests/expected/setTest.out 						./tests/observed/setTest.out
diff ./tests/expected/setTest_save_edit_mode.txt	 	./tests/observed/setTest_save_edit_mode.txt
diff ./tests/expected/setTest_save_solve_mode.txt	 	./tests/observed/setTest_save_solve_mode.txt


echo "---------- validate ----------"
./sudoku-console < tests/validateTest.in > tests/observed/validateTest.out
diff ./tests/expected/validateTest.out 				./tests/observed/validateTest.out


echo "---------- hint ----------"
./sudoku-console < tests/hintTest.in > tests/observed/hintTest.out
diff ./tests/expected/hintTest.out 				./tests/observed/hintTest.out


echo "---------- num_solutions ----------"
./sudoku-console < tests/num_solutionsTest.in > tests/observed/num_solutions.out
diff ./tests/expected/num_solutions.out 			./tests/observed/num_solutions.out


echo "---------- open completed board ----------"
./sudoku-console < tests/compBoardTest.in > tests/observed/compBoardTest.out
diff ./tests/expected/compBoardTest.out 			./tests/observed/compBoardTest.out



echo "---------- autofill ----------"
./sudoku-console < tests/autofillTest.in > tests/observed/autofillTest.out
diff ./tests/expected/autofillTest.out 				./tests/observed/autofillTest.out


echo "---------- save ----------"
./sudoku-console < tests/saveTest.in > tests/observed/saveTest.out
diff ./tests/expected/saveTest.out 					./tests/observed/saveTest.out
diff ./tests/expected/save_board2.txt 				./tests/observed/save_board2.txt
diff ./tests/expected/save_board3.txt 				./tests/observed/save_board3.txt
diff ./tests/expected/save_edit_board.txt	 		./tests/observed/save_edit_board.txt
diff ./tests/expected/save_solve_board.txt	 		./tests/observed/save_solve_board.txt
diff ./tests/expected/save_test_with_error.txt	 	./tests/observed/save_test_with_error.txt


echo "---------- reset ----------"
./sudoku-console < tests/resetTest.in > tests/observed/reset.out
diff ./tests/expected/reset.out 				./tests/observed/reset.out

echo "---------- board 2x3 ----------"
./sudoku-console < tests/testBoard2_3.in > tests/observed/testBoard2_3.out
diff ./tests/expected/testBoard2_3.out 						./tests/observed/testBoard2_3.out
diff ./tests/expected/b2_3-saveTestEdit.txt 				./tests/observed/b2_3-saveTestEdit.txt
diff ./tests/expected/b2_3-saveTestSolve.txt 				./tests/observed/b2_3-saveTestSolve.txt

echo "---------- board 5x1 ----------"
./sudoku-console < tests/testBoard_5x1.in > tests/observed/testBoard_5x1.out
diff ./tests/expected/testBoard_5x1.out 						./tests/observed/testBoard_5x1.out
diff ./tests/expected/b5x1-saveTestEdit.txt 				./tests/observed/b5x1-saveTestEdit.txt
diff ./tests/expected/b5x1-saveTestSolve.txt 				./tests/observed/b5x1-saveTestSolve.txt

echo "---------- board 1x1 ----------"
./sudoku-console < tests/testBoard_1x1.in > tests/observed/testBoard_1x1.out

echo "---------- board 4x2 ----------"
./sudoku-console < tests/testBoard4x2.in > tests/observed/testBoard4x2.out
diff ./tests/expected/testBoard4x2.out 						./tests/observed/testBoard4x2.out
diff ./tests/expected/b4_2-saved.txt 				./tests/observed/b4_2-saved.txt
diff ./tests/expected/b4_2-saved2.txt 				./tests/observed/b4_2-saved2.txt

echo "---------- board 2x6 ----------"
./sudoku-console < tests/testBoard_2x6.in > tests/observed/testBoard2x6.out
diff ./tests/expected/testBoard2x6.out 						./tests/observed/testBoard2x6.out
diff ./tests/expected/b2x6-saveTestSolve.txt 				./tests/observed/b2x6-saveTestSolve.txt


echo "---------- various board sizes ----------"
./sudoku-console < tests/testVariousBoardSizes.in > tests/observed/testVariousBoardSizes.out
diff ./tests/expected/testVariousBoardSizes.out 			./tests/observed/testVariousBoardSizes.out


echo "---------- load solved board ----------"
./sudoku-console < tests/loadSolvedTest.in > tests/observed/loadSolvedTest.out
diff ./tests/expected/loadSolvedTest.out 				./tests/observed/loadSolvedTest.out

echo "---------- test faulty autofill ----------"
./sudoku-console < tests/testFaultyAutofill.in > tests/observed/testFaultyAutofill.out
diff ./tests/expected/testFaultyAutofill.out 			./tests/observed/testFaultyAutofill.out

echo "---------- test load erroneous board ----------"
./sudoku-console < tests/testLoadErrBoard.in > tests/observed/testLoadErrBoard.out
diff ./tests/expected/testLoadErrBoard.out 			./tests/observed/testLoadErrBoard.out

./sudoku-console < tests/testErroneusLoad.in > tests/observed/testErroneusLoad.out
diff ./tests/expected/testErroneusLoad.out 			./tests/observed/testErroneusLoad.out


echo "---------- test unformatted boards loading ----------"
./sudoku-console < tests/unformattedBoard.in > tests/observed/unformattedBoard.out
diff ./tests/expected/unformattedBoard.out 			./tests/observed/unformattedBoard.out

echo "---------- test early eof ----------"
./sudoku-console < tests/testPartialCommand1.in > tests/observed/testPartialCommand1.out
diff ./tests/expected/testPartialCommand1.out 			./tests/observed/testPartialCommand1.out

./sudoku-console < tests/testPartialCommand2.in > tests/observed/testPartialCommand2.out
diff ./tests/expected/testPartialCommand2.out 			./tests/observed/testPartialCommand2.out

./sudoku-console < tests/testPartialCommand3.in > tests/observed/testPartialCommand3.out
diff ./tests/expected/testPartialCommand3.out 			./tests/observed/testPartialCommand3.out

./sudoku-console < tests/testPartialCommand4.in > tests/observed/testPartialCommand4.out
diff ./tests/expected/testPartialCommand4.out 			./tests/observed/testPartialCommand4.out

./sudoku-console < tests/testPartialCommand5.in > tests/observed/testPartialCommand5.out
diff ./tests/expected/testPartialCommand5.out 			./tests/observed/testPartialCommand5.out

echo "---------- test command out of buffer ----------"
./sudoku-console < tests/testOutOfBufCmd.in > tests/observed/testOutOfBufCmd.out
diff ./tests/expected/testOutOfBufCmd.out 			./tests/observed/testOutOfBufCmd.out


# can not use because the board is not printed after solve/edit commands (moodle files are too old)
# echo "---------- moodle test files ----------"
# rm tests/test_moodle/sudoku-console
# cp ./sudoku-console tests/test_moodle/
# cd tests/test_moodle/
# ./compare.sh
# cd ../..

echo "---------- generate ----------"
./sudoku-console < tests/generateTest.in > tests/observed/generateTest.out
diff ./tests/expected/generateTest.out 				./tests/observed/generateTest.out

