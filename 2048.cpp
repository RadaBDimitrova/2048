#include <iostream>
#include <iomanip>
#include <cstdlib>

void moveUp(int** arr, int size);
void moveDown(int** arr, int size);
void moveLeft(int** arr, int size);
void moveRight(int** arr, int size);
void mergeUp(int** arr, int size);
void mergeDown(int** arr, int size);
void mergeLeft(int** arr, int size);
void mergeRight(int** arr, int size);


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

void initializeBoard(int** arr, int size) {
	int x1 = rand() % size;
	int y1 = rand() % size;
	int x2 = rand() % size;
	int y2 = rand() % size;

	//in case the coordinates of the first two tiles are the same
	while (x2 == x1 && y2 == y1) {
		x2 = rand() % size;
		y2 = rand() % size;
	}

	arr[x1][y1] = 2;
	arr[x2][y2] = 2;
}

void insertNewTile(int** arr, int size) {
	int x1 = rand() % size; // error exception unhandled
	int y1 = rand() % size;
	while (arr[x1][y1] != 0)
	{
		x1 = rand() % size;
		y1 = rand() % size;
	}
	arr[x1][y1] = 2;
}

//void moveUp(int** arr, int size) {
//	bool updated = false;
//	for (int i = 0; i < size - 1; i++)
//	{
//		for (int j = 0; j < size; j++)
//		{
//			if (arr[i][j] == 0)
//			{
//				for (int row = i; row < size - 1; row++)
//				{
//					arr[row][j] = arr[row + 1][j];
//				}
//				arr[size - 1][j] = 0;
//				updated = true;
//			}
//		}
//	}
//	if (updated)
//	{
//		mergeUp(arr, size);
//	}
//}

//void mergeUp(int** arr, int size) {
//	for (int i = 0; i < size - 1; i++)
//	{
//		for (int j = 0; j < size; j++)
//		{
//			if (arr[i][j] == arr[i + 1][j]) {
//				arr[i][j] *= 2;
//				arr[i + 1][j] = 0;
//			}
//		}
//	}
//	moveUp(arr, size);
//}

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
				if (arr[i][j] == 0)
				{
					/*for (int row = i; row < size - 1; row++)
					{
						arr[row][j] = arr[row + 1][j];
					}
					arr[size - 1][j] = 0;*/
					int row = i;
					while (row < size - 1 && arr[])
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
					score += arr[i][j];
				}
			}
		}

		/*if (arr[i][j] == arr[i - 1][j])
		{
			arr[i - 1][j] *= 2;
			arr[i][j] = 0;
		}
		else {
			break;
		}*/
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

	initializeBoard(board, dimension);
	drawBoard(board, dimension);


	for (int i = 0; i < dimension; i++) {
		delete[] board[i];
	}
	delete[] board;
	delete[] nickname;
	return 0;
}

