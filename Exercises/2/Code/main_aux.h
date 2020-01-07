#ifndef MAIN_AUXH_
#define MAIN_AUXH_

#include <stdio.h>
#include <stdlib.h>

#include "sp_nim.h"
#include "SPBufferset.h"

#define		TRUE	1
#define		FALSE	0

void printHeaps(int turn, int number_of_heaps, int* heaps);

void runNim(int number_of_heaps, int* heaps);

#endif /*MAIN_AUXH_*/
