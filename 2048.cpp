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

void insertNewTile(int** arr, int size) {
	srand(time(0));
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
				while (arr[i][j] == 0 && counter < size)
				{
					counter++;
					for (int row = i; row < size - 1; row++)
					{
						if (arr[row][j] == arr[row + 1][j]) {
							arr[row][j] *= 2;
							arr[row + 1][j] = 0;
						}
						arr[row][j] = arr[row + 1][j];
						arr[row + 1][j] = 0;
					}
					arr[size - 1][j] = 0;
					/*int row = i;
					while (row < size - 1)
					{
						arr[row][j] = arr[row + 1][j];
						arr[row + 1][j] = 0;
						row++;
					}
					arr[size - 1][j] = 0;*/
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


void drawBoard(int** arr, int size) {
	if (emptyArray(arr, size))
	{
		insertNewTile(arr, size);
	}
	insertNewTile(arr, size);
	printBoard(arr, size);
	moveTiles(arr, size);

	if (checkPossibleMoves == false)
	{
		std::cout << "Game over!" << std::endl;
		return;
	}
	else if (win)
	{
		std::cout << "Congrats! You got 2048!" << std::endl;
		return;
	}
	else
	{
	clearConsole();
	std::cout << score(arr, size) << std::endl; // prints the previous board sum
	drawBoard(arr, size);
	}

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

