#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;
class grid
{	
private:
	int weaponSpawnCoords[2][2];
	int rows;
	int cols;
	int mobNo;
	bool alive = true;
	bool winGame = false;
	bool metMob;
	bool metWeapon;
	bool metWall;
	bool metEnd;
	typedef vector<vector<char>> gridVec;
	gridVec myGrid;
	vector<vector<int>> posMoves = { {-1,0}, {1,0}, {0,-1}, {0,1} };

public:
	
	int getRows();
	int getCols();
	bool getMetEnd();
	void setWinGame(bool winGame);
	grid(int rows, int cols, int mobNo);
	void setAttributes(int rows, int cols, int mobNo);
	void printGrid();
	pair<int, int> nextMove(char direction);
	void setAlive(bool status);
	bool getAlive();
	void spawnWeapon();
	void setEndPoint();
	void spawnMobs();
	gridVec getGrid();
	void objectMet(char whatObject);
	void resetObjects();
	bool hasObjectBeenMet();
	void alterGrid(int fromRow, int fromCol, char fromChar, int toRow, int toCol, char toChar);
	void checkOpenGates();
	//void checkState(pair<int, int> nextCoords, grid newGrid, char direction);
	//void checkCharStatus(int checkRow, int checkCol);
	//vector<vector<int>> grid::calcMoves(vector<vector<int>>  posMoves, int i, int j);
	~grid();
};
