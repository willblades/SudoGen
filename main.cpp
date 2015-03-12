#include <iostream>
#include <math.h>
#include <vector>
#include "Board.h"
using namespace std;

int main()
{
	Board mainBoard;
	mainBoard.Initialize();
	mainBoard.GeneratePuzzle();
	mainBoard.DisplayInConsole();
	mainBoard.SolveGeneratedPuzzle();
	mainBoard.DisplayInConsole();
	return 0;
}