#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include "Game.h"
#include "Leaderboards.h"
#include "Movements.h"

const int LEADERBOARD_SIZE = 5;
const int MAX_NICKNAME = 101;

void clearConsole() {
	std::cout << "\033[;H";
	std::cout << "\033[J";
}

void printBoard(int** arr, int size) {
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cout << std::setw(5) << arr[i][j];
		}
		std::cout << std::endl;
	}
}

int score(int** arr, int size) {
	int score = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			score += arr[i][j];
		}
	}
	return score + 2;
}

bool emptyArray(int** arr, int size) {
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (arr[i][j] == 0)
			{
				count++;
			}
		}
	}
	if (count == size * size)
	{
		return true;
	}
	return false;
}

bool checkPossibleMoves(int** arr, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (arr[i][j] == 0) {
				return true;
			}
			if (j < size - 1 && arr[i][j] == arr[i][j + 1]) {
				return true;
			}
			if (i < size - 1 && arr[i][j] == arr[i + 1][j]) {
				return true;
			}
		}
	}
	return false;
}

bool isEmptySpace(int** arr, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (arr[i][j] == 0)
				return true;
		}
	}
	return false;
}

void checkInput(int& num)
{
	while (true) {
		std::cin >> num;
		if (std::cin.fail()) {
			std::cout << "Invalid input. Please input a number. " << std::endl;
			std::cin.clear();
			std::cin.ignore(100000, '\n');
		}
		else {
			break;
		}
	}
}

bool win(int** arr, int size) {
	int countEmptySlots = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (arr[i][j] == 2048)
			{
				return true;
			}
		}
	}
	return false;
}
