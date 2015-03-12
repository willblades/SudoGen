#include <vector>
#include <string>
#include <map>

#ifndef BOARD_H_
#define BOARD_H_

enum difficulty
{
	easy, moderate,hard
};

class Board
{
public:
	Board();
	Board(difficulty diff);
	Board(difficulty diff, int length);
	Board(int length);
	~Board();
	void Initialize();
	void InitiateRandomFromScratch(); // depricated
	void GeneratePuzzle(); 
	void DisplayInConsole();
	void SolveGeneratedPuzzle();
	std::vector<std::vector<int> > getBoard() { return board; };
	std::vector<std::vector<int> > getSolution() { return solution; };
	int getBoardlength() { return board_length; };
protected:
	void Startup();
	void FindandEraseEmptySpace(int key, int value);
	bool IsNumberinSubGrid(int number, int xgrid, int ygrid);
	void HiddenSingles();
private:
	std::vector<std::vector<int> > board;
	std::vector<std::vector<int> > solution;
	std::vector<int> possible_numbers;
	std::multimap<int, int> emptyspaces;
	int board_length;
	difficulty difficulty_settings; 
};

#endif