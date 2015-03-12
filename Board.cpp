#include "Board.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <set>

Board::Board()
{
	board_length = 9;
	difficulty_settings = easy;
	Startup();
}

Board::Board(difficulty diff)
{
	difficulty_settings = diff; 
	Startup();
}

Board::Board(difficulty diff, int length)
{
	difficulty_settings = diff;
	board_length = length;
	Startup();
}

Board::Board(int length)
{
	board_length = length;
	Startup();
}


void Board::Startup()
{
	for (int i = 1; i < board_length + 1; i++)
		possible_numbers.push_back(i);

	board.resize(board_length);
	for (int i = 0; i < board_length; i++)
			board[i].resize(9,-1);
}

Board::~Board()
{
	board.clear();
	solution.clear();
	possible_numbers.clear();
	emptyspaces.clear();
}

void Board::Initialize()
{ 
	board[0] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	board[1] = { 4, 5, 6, 7, 8, 9, 1, 2, 3 };
	board[2] = { 7, 8, 9, 1, 2, 3, 4, 5, 6 };
	board[3] = { 2, 3, 4, 5, 6, 7, 8, 9, 1 };
	board[4] = { 5, 6, 7, 8, 9, 1, 2, 3, 4 };
	board[5] = { 8, 9, 1, 2, 3, 4, 5, 6, 7 };
	board[6] = { 3, 4, 5, 6, 7, 8, 9, 1, 2 };
	board[7] = { 6, 7, 8, 9, 1, 2, 3, 4, 5 };
	board[8] = { 9, 1, 2, 3, 4, 5, 6, 7, 8 };

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1, 50);
	int swap_repeatitions = distribution(generator);

	//swap columns
	for (int i = 0; i < swap_repeatitions; i++)
	{
		for (int j = 0; j < board_length ; j += 3)
		{
			std::uniform_int_distribution<int> random(0, 2);
			int column1 = random(generator);
			int column2 = random(generator);
			std::swap(board[j + column1], board[j + column2]);
		}
	}
	
	// swap rows
	swap_repeatitions = distribution(generator);
	for (int i = 0; i < swap_repeatitions; i++)
	{
		for (int j = 0; j < board_length ; j += 3)
		{
			std::uniform_int_distribution<int> random(0, 2);
			int row1 = random(generator);
			int row2 = random(generator);

			for (int k = 0; k < board_length; k++)
			{
				int swap_temp = board[k][j + row1];
				board[k][j + row1] = board[k][j + row2];
				board[k][j + row2] = swap_temp;
			}
		}
	}

	//swap columns again
	swap_repeatitions = distribution(generator);
	for (int i = 0; i < swap_repeatitions; i++)
	{
		for (int j = 0; j < board_length; j += 3)
		{
			std::uniform_int_distribution<int> random(0, 2);
			int column1 = random(generator);
			int column2 = random(generator);
			std::swap(board[j + column1], board[j + column2]);
		}
	}
}

void Board::GeneratePuzzle()
{
	std::default_random_engine generator;
	int emptycells; 
	
	if (difficulty_settings == easy)
	{
		std::uniform_int_distribution<int> distribution1(46, 50);
		emptycells = distribution1(generator);
	}
	else if (difficulty_settings == moderate)
	{
		std::uniform_int_distribution<int> distribution2(51, 57);
		emptycells = distribution2(generator);
	}
	else
	{
		std::uniform_int_distribution<int> distribution3(58, 65);
		emptycells = distribution3(generator);
	}

	solution = board;
	int location1, location2; 
	bool isempty;

	for (int i = 0; i < emptycells; i++)
	{
		isempty = true;
		while (isempty)
		{
			std::uniform_int_distribution<int> distribution(0, board_length - 1);
			location1 = distribution(generator);
			std::uniform_int_distribution<int> distribution2(0, board_length - 1);
			location2 = distribution2(generator);
			if (board[location1][location2] != -1)
			{
				emptyspaces.insert(std::make_pair(location1, location2));
				board[location1][location2] = -1;
				isempty = false;
			}
		}	
	}
}

bool NoDuplicatesFound(std::vector<int> row, int element)
{
	std::vector<int>::iterator it = std::find(row.begin(), row.end(), element);
	if (it != row.end())
		return false;
	else
		return true;
}

void Board::InitiateRandomFromScratch()
{
	/*
	std::set<int> allocated_locations;
	std::vector<int> location_row, location_column, all_possible_locations;

	for (int x = 0; x < board_length; x++)
	{
		int current_number = possible_numbers.at(x);
		for (int y = 0; y < board_length; y++)
		{
			DisplayInConsole();

			int random_location = 0;
			bool empty_location_found = false;
			for (int i = 0; i < board_length; i++)
				all_possible_locations.push_back(i);
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::shuffle(all_possible_locations.begin(), all_possible_locations.end(),
				std::default_random_engine(seed));

			while (!empty_location_found)
			{
				random_location = all_possible_locations.at(0);

				for (int i = 0; i < board_length; i++)
				{
					location_column.push_back(board[i][random_location]);
					location_row.push_back(board[y][i]);
				}
					

				if ( //(allocated_locations.find(random_location) == allocated_locations.end()) &&  
					board[y][random_location] == -1 && 
					NoDuplicatesFound(location_column,current_number) &&
					NoDuplicatesFound(location_row,current_number) )
				{
					board[y][random_location] = current_number;
					allocated_locations.insert(random_location);
					empty_location_found = true;
				}
				all_possible_locations.erase(all_possible_locations.begin());
				location_column.clear(), location_row.clear();
				//int search_result = std::distance(all_possible_locations.begin(), 
					//std::find(all_possible_locations.begin(), 
				//all_possible_locations.end(), random_location));
				//all_possible_locations.erase(all_possible_locations.begin() 
				//+ search_result);
			}
			all_possible_locations.clear();
		}
		allocated_locations.clear();
	} */
}

void Board::DisplayInConsole()
{
	for (int i = 0; i < board_length; i++)
		std::cout << "--";
	std::cout << "\n";
	for (int i = 0; i < board_length; i++)
	{
		std::cout << "|";
		for (int j = 0; j < board_length; j++)
		{
			int number = board[i][j];
			if (number != -1)
				std::cout << board[i][j] << "|";
			else
				std::cout << "_|";
		}	
		std::cout << "\n";
	}
	for (int i = 0; i < board_length ; i++)
		std::cout << "--";
	std::cout << "\n";
	std::cin.ignore(80, '\n');
}



void Board::SolveGeneratedPuzzle()
{
	for (int i = 0; i < 50; i++)
		HiddenSingles();
}

void searchRowsandCols(std::vector<int>& searchzone,
	std::set<int>& possible_locations, int checkednumber, int colrownumber)
{
	//std::sort(searchzone.begin(), searchzone.end());
	if (std::find(searchzone.begin(), searchzone.end(), checkednumber) != searchzone.end())
		possible_locations.erase(colrownumber);
}

void Board::FindandEraseEmptySpace(int key, int value)
{
	typedef std::multimap<int, int>::iterator mapiter;
	std::pair<mapiter, mapiter> pairiter = emptyspaces.equal_range(key);

	mapiter iterator = pairiter.first;
	for (; iterator != pairiter.second; iterator++)
	{
		if (iterator->second == value)
		{
			emptyspaces.erase(iterator);
			break;
		}
	}
}

bool Board::IsNumberinSubGrid(int number, int xgrid, int ygrid)
{
	bool result = false;
	for (int i = xgrid; i < xgrid + 3; i++)
		for (int j = ygrid; j < ygrid + 3; j++)
			if (board[i][j] == number)
				return true;
	return result;
}

void Board::HiddenSingles()
{
	for (int i = 0; i < possible_numbers.size(); i++)
	{
		int checkednumber = possible_numbers.at(i);
		for (int xgrid = 0; xgrid < board_length ; xgrid += 3)
		{
			for (int ygrid = 0; ygrid < board_length; ygrid += 3)
			{
				// check and see if the number is already present or not
				// if it is, skip & move on
				if (!IsNumberinSubGrid(checkednumber, xgrid, ygrid))
				{
					std::set<int> possiblerow_locations{ xgrid, xgrid + 1, xgrid + 2 };
					std::set<int> possiblecol_locations{ ygrid, ygrid + 1, ygrid + 2 };

					// search rows first
					for (int rowcount = xgrid; rowcount < xgrid + 3; rowcount++)
					{
						std::vector<int> currentrow = board[rowcount];
						searchRowsandCols(currentrow,
							possiblerow_locations, checkednumber,rowcount);
					}

					// search columns next
					std::vector<int> currentcol;
					currentcol.resize(board_length, -1);
					for (int colcount = ygrid; colcount < ygrid + 3; colcount++)
					{
						for (int j = 0; j < board_length; j++)
							currentcol[j] = board[j][colcount];
						searchRowsandCols(currentcol,
							possiblecol_locations, checkednumber,colcount);
					}

					// if only one empty location remains, all's good and dandy! else...
					// we have to eliminate locations that might be already occupied in hopes
					// we end up with only one. This is done by eliminating non-empty cells

					if (possiblerow_locations.size() == 1 && possiblecol_locations.size() == 1)
					{
						int cell_x = *possiblerow_locations.begin();
						int cell_y = *possiblecol_locations.begin();
						board[cell_x][cell_y] = checkednumber;
						FindandEraseEmptySpace(cell_x, cell_y);
					}
					else
					{
						int emptyrowcount = 0;
						int temploc[2] = { -1, -1 };
						std::set<int>::iterator rowiter, coliter; 
						for (rowiter = possiblerow_locations.begin(); rowiter != 
							possiblerow_locations.end(); rowiter++)
						{
							for (coliter = possiblecol_locations.begin(); coliter != 
								possiblecol_locations.end(); coliter++)
							{
								int checkingx = *rowiter;
								int checkingy = *coliter;
								if (board[checkingx][checkingy] == -1)
								{
									emptyrowcount++;
									temploc[0] = checkingx;
									temploc[1] = checkingy;
								}
							}
						}
						if (emptyrowcount == 1)
						{
							int locatedcell_x = temploc[0];
							int locatedcell_y = temploc[1];
							board[locatedcell_x][locatedcell_y] = checkednumber;
							FindandEraseEmptySpace(locatedcell_x, locatedcell_y);
						}
					}
					possiblecol_locations.clear(), possiblerow_locations.clear();
				}
			}
		}
	}
}