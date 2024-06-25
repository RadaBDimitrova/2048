#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include "Game.h"
#include "Helper.h"
#include "Leaderboards.h"

const int LEADERBOARD_SIZE = 5;
const int MAX_NICKNAME = 101;

void mergeUp(int** arr, int size) {
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (arr[i][j] == 0)
			{
				continue;
			}
			if (arr[i][j] == arr[i + 1][j])
			{
				arr[i + 1][j] = 0;
				arr[i][j] *= 2;
			}
		}
	}
}

void mergeDown(int** arr, int size) {
	for (int i = size - 1; i > 0; i--)
	{
		for (int j = 0; j < size; j++)
		{
			if (arr[i][j] == 0)
			{
				continue;
			}
			if (arr[i][j] == arr[i - 1][j])
			{
				arr[i - 1][j] = 0;
				arr[i][j] *= 2;
			}
		}
	}
}

void moveUp(int** arr, int size) {
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int counter = 0;
			while (arr[i][j] == 0 && counter < size)
			{
				counter++;
				for (int row = i; row < size - 1; row++)
				{
					arr[row][j] = arr[row + 1][j];
					arr[row + 1][j] = 0;
				}
				arr[size - 1][j] = 0;
			}
		}
	}
}

void moveDown(int** arr, int size) {
	for (int i = size - 1; i > 0; i--)
	{
		for (int j = 0; j < size; j++)
		{
			int counter = 0;
			while (arr[i][j] == 0 && counter < size)
			{
				counter++;
				for (int row = i; row > 0; row--)
				{
					arr[row][j] = arr[row - 1][j];
					arr[row - 1][j] = 0;
				}
				arr[0][j] = 0;
			}
		}
	}
}

void mergeRight(int** arr, int size) {
	for (int i = 0; i < size; i++)
	{
		for (int j = size - 1; j > 0; j--)
		{
			if (arr[i][j] == 0)
			{
				continue;
			}
			if (arr[i][j] == arr[i][j - 1])
			{
				arr[i][j - 1] = 0;
				arr[i][j] *= 2;
			}
		}
	}
}

void mergeLeft(int** arr, int size) {
	for (int i = 0; i < size; i++)
	{
		for (int j = size - 1; j > 0; j--)
		{
			if (arr[i][j] == 0)
			{
				continue;
			}
			if (arr[i][j] == arr[i][j - 1])
			{
				arr[i][j - 1] *= 2;
				arr[i][j] = 0;
			}
		}
	}
}

void moveLeft(int** arr, int size) {
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - 1; j++)
		{
			int counter = 0;
			while (arr[i][j] == 0 && counter < size)
			{
				counter++;
				for (int col = j; col < size - 1; col++)
				{
					arr[i][col] = arr[i][col + 1];
					arr[i][col + 1] = 0;
				}
				arr[i][size - 1] = 0;
			}
		}
	}
}

void moveRight(int** arr, int size) {
	for (int i = 0; i < size; i++)
	{
		for (int j = size - 1; j > 0; j--)
		{
			int counter = 0;
			while (arr[i][j] == 0 && counter < size)
			{
				counter++;
				for (int col = j; col > 0; col--)
				{
					arr[i][col] = arr[i][col - 1];
					arr[i][col - 1] = 0;
				}
				arr[i][0] = 0;
			}
		}
	}
}

void moveTiles(int** arr, int size) {
	int score = 0;
	char direction;
	std::cin >> direction;
	while (direction != 'w' && direction != 's' && direction != 'd' && direction != 'a')
	{
		std::cin >> direction;
	}
	switch (direction)
	{
	case 'w':
		moveUp(arr, size);
		mergeUp(arr, size);
		moveUp(arr, size);
		break;
	case's':
		moveDown(arr, size);
		mergeDown(arr, size);
		moveDown(arr, size);
		break;
	case 'a':
		moveLeft(arr, size);
		mergeLeft(arr, size);
		moveLeft(arr, size);
		break;
	case 'd':
		moveRight(arr, size);
		mergeRight(arr, size);
		moveRight(arr, size);
		break;
	default:
		break;
	}
}
