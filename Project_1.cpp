// Project_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "general.h"
#include "grid.h"
#include "Characters.h"
#include "general.h"
#include <conio.h>
using namespace std;


void changeGrid(pair<int, int> nextCoords, char direction, grid *newGrid);
void endGame(grid * newGrid, Characters * myChar);
void playGame(grid * newGrid, Characters * myChar);
void gameSetup(string currentChar, string names[4]);
void changeState(pair<int, int> nextCoords, char direction, grid * newGrid, Characters * myChar);
void moveMob(grid * newGrid, Characters * myChar);
int main()
{
	grid newGrid(10, 10, 4);
	cout << "Welcome to \"Dungeon Crawl\"" << endl;
	string names[4] = { "Rob", "Charlie", "Kendrick", "Mildred" };
	srand(time(NULL));
	string currentChar = names[rand() % 4];
	gameSetup(currentChar, names);
 	return 0;
}

void gameSetup(string currentChar, string names[4]) {
	
	cout << "Please choose an option: "
		<< "\n1. Generate default world\n2. Choose Character\n3. Setup world\n4. Quit"
		<< "\nYour current character is: " << currentChar << endl;
	int userChoice;
	cin >> userChoice;
	switch(userChoice) {
	case 1: {
		grid newGrid(10, 10, 4);
		Characters myChar(currentChar);
		playGame(&newGrid, &myChar);
		break; }
	case 2:
		cout << "Available characters:\n1. Rob\n2. Charlie\n3. Kendrick\n4. Mildred\nPlease enter the corresponding number: " << flush;
		int charChoice;
		cin >> charChoice;
		currentChar = names[charChoice - 1];
		gameSetup(currentChar, names);
	case 3: {
		cout << "How many rows would you like there to be? Please enter at least 4" << flush;
		int rows;
		cin >> rows;
		cout << "How many columns would you like there to be? Please enter at least 4" << flush;
		int cols;
		cin >> cols;
		cout << "How many monsters would you like there to be? Please enter at least 4" << flush;
		int mobNo;
		cin >> mobNo;
		if (mobNo >= (rows*cols) - 6) {
			cout << "Please enter a sensible number of monsters.." << endl;
			gameSetup(currentChar, names);
		}
		grid newGrid(rows, cols, mobNo);
		Characters myChar(currentChar);
		playGame(&newGrid, &myChar);
		break; }
	case 4:
		return;
	}
}

void playGame(grid * newGrid, Characters * myChar) {
	cout << "Let us begin.. Good luck adventurer..." << endl;
	newGrid->printGrid();
	pair<int, int> nextCoords(0, 0);
	int posMoves[] = {87, 65, 83, 68};
	cout << "Up = 'W'\nLeft = 'A'\nDown = 'S'\nRight = 'D'" << endl;
	do {
		cout << "Please enter your next move: " << endl;
		char direction = _getch();
		int * checkInput = find(begin(posMoves), end(posMoves), direction);
		if (checkInput == end(posMoves)) {
			cout << "Please enter a valid input" << endl;
			continue;
		}
		
		nextCoords = newGrid->nextMove(direction);
		if (newGrid->hasObjectBeenMet())
			changeState(nextCoords, direction, newGrid, myChar);
		moveMob(newGrid, myChar);
		newGrid->checkOpenGates();
		newGrid->printGrid();
		newGrid->resetObjects();
	} while (myChar->getHP() > 0 && !newGrid->getMetEnd());
	endGame(newGrid, myChar);
	return;
}

void changeState(pair<int, int> nextCoords, char direction, grid * newGrid, Characters * myChar) {
	char nextObject = newGrid->getGrid()[nextCoords.first][nextCoords.second];
	switch (nextObject) {
	case 'M': {
		if (myChar->getWeapon()) {
			cout << "You have slain a monster!" << endl;
			changeGrid(nextCoords, direction, newGrid);
		}
		else {
			cout << "You can't kill a monster with your bare hands!" << endl;
			myChar->changeHP(-1);
		}
		break;
		}
	case 'S': {
		cout << "You've got yourself a sword, go kick ass!" << endl;
		myChar->setWeapon(true);
		changeGrid(nextCoords, direction, newGrid);
		break;
		}

	case '$': {
			  cout << "Congratulations, you've completed your quest!" << endl;
			  changeGrid(nextCoords, direction, newGrid);
			  break;
		}
	}
	return;

}

void changeGrid(pair<int, int> nextCoords, char direction, grid *newGrid) {
	if (direction == 'W') {
		newGrid->alterGrid(nextCoords.first + 1, nextCoords.second, '.', nextCoords.first, nextCoords.second, 'c');
	}
	else if (direction == 'A') {
		newGrid->alterGrid(nextCoords.first, nextCoords.second + 1, '.', nextCoords.first, nextCoords.second, 'c');
	}
	else if (direction == 'S') {
		newGrid->alterGrid(nextCoords.first - 1, nextCoords.second, '.', nextCoords.first, nextCoords.second, 'c');
	}
	else {
		newGrid->alterGrid(nextCoords.first, nextCoords.second - 1, '.', nextCoords.first, nextCoords.second, 'c');
	}
}

void moveMob(grid * newGrid, Characters * myChar) {
	int row;
	int col;
	int moveRow;
	int moveCol;
	int numSpaces = (newGrid->getRows())*(newGrid->getCols());
	for (int i = 0; i < numSpaces; i++) {
		row = rand() % newGrid->getRows();
		col = rand() % newGrid->getCols();
		moveRow = (rand() % 3) - 1;
		moveCol = (rand() % 3) - 1;
		if (newGrid->getGrid()[row][col] == 'M') {
			if (!(row + moveRow < 0 || row + moveRow >= newGrid->getRows() || col + moveCol < 0 || col + moveCol >= newGrid->getCols())) {
				if (newGrid->getGrid()[row + moveRow][col + moveCol] == '.') {
					newGrid->alterGrid(row, col, '.', row + moveRow, col + moveCol, 'M');
					break;
				}
				else if (newGrid->getGrid()[row + moveRow][col + moveCol] == 'c') {
					newGrid->alterGrid(row, col, '.', row + moveRow, col + moveCol, 'M');
					myChar->changeHP(-1);
					break;
				}


			}
		}

		
	}
	return;
}


void endGame(grid * newGrid, Characters * myChar) {
	if (newGrid->getMetEnd()) {
		cout << "Congratulations adventurer, you have succeeded in your quest!" << endl;
		cout << "You will now be taken back to the main menu, thanks for playing!" << endl;
	}
	else {
		cout << "Adventurer, you have failed your task.. You are dead.." << endl;
		cout << "Complete this quest you must.. Do so from the main menu.. You have dissapointed me.. Do not do this again.." << endl;
	}
	newGrid->resetObjects();
	myChar->changeHP(1);
	main();
}