#include <iostream>
#include <iomanip>
#include <cstdlib>

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
	return score;
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

void insertNewTile(int** arr, int size) {
	srand(time(0));
	int x1 = rand() % size;
	int y1 = rand() % size;
	while (arr[x1][y1] != 0)
	{
		x1 = rand() % size;
		y1 = rand() % size;
	}
	arr[x1][y1] = 2;
}

void swap(int& a, int& b) {
	int c = a;
	a = b;
	b = c;
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
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = 0; j < size; j++)
			{
				int counter = 0;
				while (arr[i][j] == 0 && counter<size)
				{
					counter++;
					/*for (int row = i + 1; row < size - 1; row++)
					{
						arr[row][j] = arr[row + 1][j];
					}
					arr[size - 1][j] = 0;*/
					int row = i;
					while (row < size - 1)
					{
						arr[row][j] = arr[row + 1][j];
						arr[row + 1][j] = 0;
						row++;
					}
					arr[size - 1][j] = 0;
				}
				if (arr[i][j] == arr[i + 1][j]) {
					arr[i][j] *= 2;
					arr[i + 1][j] = 0;
					//score += arr[i][j];
				}
			}
		}
		break;
	case's':
		break;
	case 'a':
		break;
	case 'd':
		break;
	default:
		break;
	}
}


int boardState(int** arr, int size) {
	int countEmptySlots = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (arr[i][j] == 0)
			{
				countEmptySlots++;
			}
			if (arr[i][j] == 2048)
			{
				return -1;
			}
		}
	}
	if (countEmptySlots != 0)
	{
		return 1;
	}
	return 0;
}

void drawBoard(int** arr, int size) {
	if (emptyArray(arr, size))
	{
		insertNewTile(arr, size);
	}
	insertNewTile(arr, size);
	printBoard(arr, size);
	moveTiles(arr, size);

	if (boardState(arr, size) == 0)
	{
		std::cout << "Game over!" << std::endl;
		return;
	}
	else if (boardState(arr, size) == -1)
	{
		std::cout << "Congrats! You got 2048!" << std::endl;
		return;
	}
	clearConsole();
	std::cout << score(arr, size) << std::endl; // prints the previous board sum
	drawBoard(arr, size);
}

int main()
{
	char* nickname = new char[100];
	int dimension = 0;
	std::cout << "Enter your nickname: ";
	std::cin >> nickname;
	std::cout << "Enter dimension: ";
	std::cin >> dimension;

	int** board = new int* [dimension];
	for (int i = 0; i < dimension; i++)
	{
		board[i] = new int[dimension]();
	}

	drawBoard(board, dimension);

	for (int i = 0; i < dimension; i++) {
		delete[] board[i];
	}
	delete[] board;
	delete[] nickname;
	return 0;
}

