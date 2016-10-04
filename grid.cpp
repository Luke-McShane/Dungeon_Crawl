#include "stdafx.h"
#include "grid.h"
#include "Characters.h"


grid::grid(int rows, int cols, int mobNo) : rows(rows), cols(cols), mobNo(mobNo) {

	srand(time(0));
	myGrid.resize(rows, vector<char>(cols, '.'));
	
	myGrid[0][0] = 'c';
	spawnWeapon();
	setEndPoint();
	spawnMobs();
	
}

void grid::setAttributes(int rows, int cols, int mobNo) {
	this->rows = rows;
	this->cols = cols;
	this->mobNo = mobNo;
}

int grid::getRows() {
	return rows;
}

int grid::getCols() {
	return cols;
}

bool grid::getMetEnd() {
	return metEnd;
}

void grid::setWinGame(bool metEnd) {
	this->metEnd = metEnd;
}

pair<int, int> grid::nextMove(char direction) {
	for (int i = 0; i < myGrid.size(); ++i) {
		for (int j = 0; j < myGrid[0].size(); ++j) {
			if (myGrid[i][j] == 'c'){
				if (i == 0 && direction == 'W' || i == rows - 1 && direction == 'S' || j == 0 && direction == 'A' || j == cols - 1 && direction == 'D')
					return make_pair(i, j);
				
				switch (direction) {
				case 'W':
					try {
						cout << "Howdy" << endl;
						if (myGrid[i - 1][j] != '.') {
							//checkCharStatus(i - 1, j);
							objectMet(myGrid[i - 1][j]);
							return make_pair(i - 1, j);
						};
						myGrid[i - 1][j] = 'c';
						myGrid[i][j] = '.';
						return make_pair(i - 1, j);
					}
					catch (int e) {
						cout << "Error has occurred: " << e << endl;
						return make_pair(i, j);
					}
				case 'A':
					try {
						if (myGrid[i][j - 1] != '.') {
							objectMet(myGrid[i][j - 1]);
							//checkCharStatus(i, j - 1);
							return make_pair(i, j - 1);
						};
						myGrid[i][j - 1] = 'c';
						myGrid[i][j] = '.';
						return make_pair(i, j - 1);
					}
					catch (int e) {
						cout << "Error has occurred: " << e << endl;
						return make_pair(i, j);
					}
				case 'S':
					try {
						if (myGrid[i + 1][j] != '.') {
							objectMet(myGrid[i + 1][j]);
							//checkCharStatus(i + 1, j);
							return make_pair(i + 1, j);
						}
						myGrid[i + 1][j] = 'c';
						myGrid[i][j] = '.';
						return make_pair(i + 1, j + 1);
					}
					catch (int e) {
						cout << "Error has occurred: " << e << endl;
						return make_pair(i, j);
					}
				case 'D':
					try {
						if (myGrid[i][j + 1] != '.') {
							objectMet(myGrid[i][j + 1]);
							//checkCharStatus(i, j + 1);
							return make_pair(i, j + 1);
						}
						myGrid[i][j + 1] = 'c';
						myGrid[i][j] = '.';
						return make_pair(i, j + 1);
					}
					catch (int e) {
						cout << "Error has occurred: " << e << endl;
						return make_pair(i, j);
					}
				default:
					cout << "Invalid input, please try again.." << endl;

				}
				//posMoves = calcMoves(posMoves, i, j);

			}
		}
	}
}

void grid::objectMet(char whatObject) {
	switch (whatObject) {
	case 'M':
		metMob = true;
		break;
	case '@':
		metWall = true;
		break;
	case '$':
		metEnd = true;
		break;
	case 'S':
		metWeapon = true;
		break;
	}
	return;
}

bool grid::hasObjectBeenMet() {
	if (metEnd == true || metMob == true || metWall == true || metWeapon == true)
		return true;
	else
		return false;
}

void grid::resetObjects() {
	metMob = false;
	metWall = false;
	metWeapon = false;
}

void grid::alterGrid(int fromRow, int fromCol, char fromChar, int toRow, int toCol, char toChar) {
	myGrid[fromRow][fromCol] = fromChar;
	myGrid[toRow][toCol] = toChar;
}

void grid::spawnWeapon() {
	switch (int randNo = rand() % 1) {
	case 0:
		myGrid[myGrid.size()-1][myGrid[0].size() / 2 - 1] = 'S';
		break;
	case 1:
		myGrid[myGrid.size() / 2 - 1][myGrid[0].size() - 1] = 'S';
		break;
	}
}

void grid::setEndPoint() {
	myGrid[myGrid.size()-1][myGrid[0].size()-1] = '$';
	myGrid[myGrid.size()-2][myGrid[0].size()-1] = '@';
	myGrid[myGrid.size()-1][myGrid[0].size()-2] = '@';
	myGrid[myGrid.size()-2][myGrid[0].size()-2] = '@';
}

void grid::printGrid() {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cout << myGrid[i][j];
		}
		cout << endl;
	}
}

void grid::spawnMobs() {
	int monsterRow;
	int monsterCol;
	for (int i = 0; i < (mobNo); ++i) {
		monsterRow = (rand() % (myGrid.size()));
		monsterCol = (rand() % (myGrid[0].size()));
		cout << "M row: " << monsterRow << " M col: " << monsterCol << endl;
		if (myGrid[monsterRow][monsterCol] == '.' && !(monsterRow == 0 && monsterCol == 1) && !(monsterRow == 1 && monsterCol == 0) && !(monsterRow == 1 && monsterCol == 1))
			myGrid[monsterRow][monsterCol] = 'M';
		else
			//cout << "KJ";
			--i;
	}
}

void grid::checkOpenGates() {
	bool openGates = true;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (myGrid[i][j] == 'M') {
				openGates = false;
				break;
			}
		}
	}
	if (openGates) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (myGrid[i][j] == '@')
					myGrid[i][j] = '.';
			}
		}
	}
}

bool grid::getAlive() {
	return alive;
}

void grid::setAlive(bool status) {
	alive = status;
}

vector<vector<char>> grid::getGrid() {
	return myGrid;
}

grid::~grid()
{}