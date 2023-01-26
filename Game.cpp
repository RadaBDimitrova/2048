#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include "Helper.h"
#include "Leaderboards.h"
#include "Movements.h"

const int LEADERBOARD_SIZE = 5;
const int MAX_NICKNAME = 101;

void startMenu();

void insertNewTile(int** arr, int size) {
	if (!isEmptySpace(arr, size)) {
		return;
	}
	srand(time(NULL));
	int x = rand() % size;
	int y = rand() % size;
	while (arr[x][y] != 0)
	{
		x = rand() % size;
		y = rand() % size;
	}
	int determineWhether2or4 = rand() % 10;
	if (determineWhether2or4 == 7)
		// 7 is a random number between 0 and 9 in order to get the 10% chance to get 4
	{
		arr[x][y] = 4;
	}
	else
	{
		arr[x][y] = 2;
	}
}


void afterWin() {
	clearConsole();
	std::cout << "Congrats! You got 2048! Enter 1 to go to Start Menu and 0 to quit." << std::endl;
	int choice;
	checkInput(choice);
	if (choice)
	{
		startMenu();
	}
	else
	{
		std::exit(0);
	}
}

void afterLoss() {
	clearConsole();
	std::cout << "Game over! Enter 1 to go to Start Menu and 0 to quit." << std::endl;
	int choice;
	checkInput(choice);
	if (choice)
	{
		startMenu();
	}
	else
	{
		std::exit(0);
	}
}

void drawBoard(int** arr, int size, char* nickname) {
	if (emptyArray(arr, size))
	{
		insertNewTile(arr, size);
	}
	insertNewTile(arr, size);
	printBoard(arr, size);
	moveTiles(arr, size);
	if (win(arr, size))
	{
		afterWin();

	}
	else if (!checkPossibleMoves(arr, size))
	{
		afterLoss();
	}
	else
	{
		clearConsole();
		std::cout << "Score: " << score(arr, size) << std::endl;
		drawBoard(arr, size, nickname);
	}
}

void startGame() {
	char* nickname = new char[MAX_NICKNAME];
	int dimension = 0;
	std::cout << "Enter your nickname: ";
	std::cin >> nickname;
	std::cout << "Enter dimension: ";
	std::cin >> dimension;
	while (dimension < 4 || dimension > 10)
	{
		std::cin >> dimension;
	}
	int** board = new int* [dimension];
	for (int i = 0; i < dimension; i++)
	{
		board[i] = new int[dimension]();
	}

	drawBoard(board, dimension, nickname);
	LeaderBoard(nickname, score(board, dimension), dimension);

	for (int i = 0; i < dimension; i++) {
		delete[] board[i];
	}
	delete[] board;
	startMenu();
	return;
}


void startMenu() {
	clearConsole();
	std::cout << "START MENU" << std::endl;
	std::cout << "1. Start game" << std::endl;
	std::cout << "2. Leaderboard" << std::endl;
	std::cout << "3. Quit" << std::endl;
	int choice;
	checkInput(choice);
	while (choice != 1 && choice != 2 && choice != 3)
	{
		std::cout << "Invalid choice. Please enter a number corresponding to the menu options." << std::endl;
		std::cin >> choice;
		clearConsole();
	}
	clearConsole();
	switch (choice)
	{
	case 1:
		startGame();
		break;
	case 2:

		printLeaderBoard();
		break;
	case 3:
		return;
	default:
		break;
	}
}