./sudoku-console < test1 > _res1
./sudoku-console < test2 > _res2
./sudoku-console < test3 > _res3
diff -q -s --strip-trailing-cr res1 _res1
diff -q -s --strip-trailing-cr res2 _res2
diff -q -s --strip-trailing-cr res3 _res3
