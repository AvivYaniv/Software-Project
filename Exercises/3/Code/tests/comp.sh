#!/bin/sh
../HW3 100 < 1.in > HW3.out
../sudoku 100 < 1.in > sudoku.out


echo "---HW3:"
cat ./HW3.out

echo "---sudoku:"
cat ./sudoku.out

echo "---isDiff:"
sdiff -s HW3.out sudoku.out
echo "---/isDiff:"

echo "---end of comp.sh"
