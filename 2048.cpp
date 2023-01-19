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

void mergeUpDown(int** arr, int size) {
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size - 1; i++)
		{
			for (int row = i + 1; row < size; row++)
			{
				if (arr[row][j] == 0)
				{
					continue;
				}
				if (arr[i][j] == 0)
				{
					arr[i][j] = arr[row][j];
					arr[row][j] = 0;
				}
				else if (arr[i][j] == arr[row][j])
				{
					arr[i][j] *= 2;
					arr[row][j] = 0;
				}
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
			mergeUpDown(arr, size);
			moveUp(arr, size);
			break;
		case's':
			mergeUpDown(arr, size);
			moveDown(arr, size);
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

		if (win(arr, size))
		{
			std::cout << "Congrats! You got 2048!" << std::endl;
			return;
		}
		else if (!checkPossibleMoves(arr, size))
		{
			std::cout << "Game over!" << std::endl;
			return;
		}
		else
		{
			clearConsole();
			std::cout << "Score: " << score(arr, size) << std::endl; // prints the previous board sum
			drawBoard(arr, size);
		}
	}

	void startGame() {
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
		return;
	}

	void startMenu() {
		std::cout << "1. Start game" << std::endl;
		std::cout << "2. Leaderboard" << std::endl;
		std::cout << "3. Quit" << std::endl;
		int choice;
		std::cin >> choice;
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
		case 2: //open menu for leaderboard options
			break;
		case 3:
			return;
		default:
			break;
		}
	}

	int main()
	{
		startMenu();
	}
