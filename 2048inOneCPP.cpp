/**
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Rada Dimitrova
* @idnumber 8MI0600227 @compiler VS
*
* <Main File>
*
*/


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>

const int LEADERBOARD_SIZE = 5;
const int MAX_NICKNAME = 101;
void startMenu();
void LeaderBoard(char* name, int score, int dimension);

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

void mergeUp(int** arr, int size) {
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
					break;
				}
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
		//LeaderBoard(name, score(arr, size), size);
		afterWin();

	}
	else if (!checkPossibleMoves(arr, size))
	{
		//LeaderBoard(name, score(arr, size), size);
		afterLoss();
	}
	else
	{
		clearConsole();
		std::cout << "Score: " << score(arr, size) << std::endl;
		drawBoard(arr, size);
	}
}

void strCopy(const char* from, char* to) {
	int i = 0;
	while (from[i] != '\0')
	{
		to[i] = from[i];
		i++;
	}
	to[i] = '\0';
}

void updateLeaderBoard(int dimension, char* name, int score, char** nickname, int* scores) {
	for (int i = 0; i < LEADERBOARD_SIZE; i++) {
		if (score > scores[i]) {
			for (int j = LEADERBOARD_SIZE - 1; j > i; j--) {
				scores[j] = scores[j - 1];
				strCopy(nickname[j - 1], nickname[j]);
			}
			scores[i] = score;
			nickname[i] = name;
			break;
		}
	}
}

char* getFileName(int dimension) {
	char* filename = new char[100];
	switch (dimension)
	{
	case 4:
		strCopy("leaderboard4.txt", filename);
		break;
	case 5:
		strCopy("leaderboard5.txt", filename);
		break;
	case 6:
		strCopy("leaderboard6.txt", filename);
		break;
	case 7:
		strCopy("leaderboard7.txt", filename);
		break;
	case 8:
		strCopy("leaderboard8.txt", filename);
		break;
	case 9:
		strCopy("leaderboard9.txt", filename);
		break;
	case 10:
		strCopy("leaderboard10.txt", filename);
		break;
	default:
		break;
	}
	return filename;
}

void fillLeaderboard(char** nickname, int* scores, char* fileName) {
	std::ifstream leaderboard;
	leaderboard.open(fileName);

	if (!leaderboard.is_open())
	{
		std::cout << "Error! Failed to open file\n";
		return;
	}

	for (int i = 0; !leaderboard.eof(); ++i)
	{
		leaderboard >> nickname[i] >> scores[i];
	}
	leaderboard.close();
}

void writeToFile(char** nickname, int* scores, char* fileName) {
	std::ofstream newLeaderboard(fileName);
	if (!newLeaderboard.is_open()) {
		return;
	}
	for (int i = 0; i < LEADERBOARD_SIZE; ++i)
	{
		if (scores[i] != 0)
		{
			newLeaderboard << nickname[i] << " " << scores[i] << " ";
		}
		else {
			break;
		}
	}
	newLeaderboard.close();
}

void LeaderBoard(char* name, int score, int dimension) {
	int scores[LEADERBOARD_SIZE] = {};
	char** nickname = new char* [LEADERBOARD_SIZE];
	for (int i = 0; i < LEADERBOARD_SIZE; i++)
	{
		nickname[i] = new char[LEADERBOARD_SIZE];
	}
	char* fileName = getFileName(dimension);
	fillLeaderboard(nickname, scores, fileName);
	updateLeaderBoard(dimension, name, score, nickname, scores);
	writeToFile(nickname, scores, fileName);

	for (int i = 0; i < LEADERBOARD_SIZE; i++) {
		delete[] nickname[i];
	}
	delete[] nickname;
	delete[] fileName;
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

	drawBoard(board, dimension);
	LeaderBoard(nickname, score(board, dimension), dimension);

	for (int i = 0; i < dimension; i++) {
		delete[] board[i];
	}
	delete[] board;
	startMenu();
	return;
}

void printLeaderBoard() {
	int scores[LEADERBOARD_SIZE] = {};
	char** nickname = new char* [LEADERBOARD_SIZE];
	for (int i = 0; i < LEADERBOARD_SIZE; i++)
	{
		nickname[i] = new char[LEADERBOARD_SIZE];
	}
	int dimension;
	std::cout << "Enter dimension: ";
	std::cin >> dimension;
	std::ifstream leaderboard;
	char* fileName = getFileName(dimension);
	leaderboard.open(fileName);

	if (!leaderboard.is_open())
	{
		std::cout << "Error! Failed to open file\n";
		for (int i = 0; i < LEADERBOARD_SIZE; i++) {
			delete[] nickname[i];
		}
		delete[] nickname;
		delete[] fileName;
		return;
	}
	int countOfPeople = 0;
	for (int i = 0; !leaderboard.eof(); ++i)
	{
		leaderboard >> nickname[i] >> scores[i];
		if (scores[i] != 0) {
			std::cout << nickname[i] << " " << scores[i] << std::endl;
			countOfPeople++;
		}
		else {
			break;
		}
	}
	leaderboard.close();

	delete[] nickname;
	delete[] fileName;
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

int main()
{
	startMenu();
}

