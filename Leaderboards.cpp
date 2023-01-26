#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include "Game.h"
#include "Helper.h"
#include "Movements.h"
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

const int LEADERBOARD_SIZE = 5;
const int MAX_NICKNAME = 101;

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
			newLeaderboard << "-----" << " " << scores[i] << " ";
			
		}
	}
	newLeaderboard.close();
}

void fillLeaderboard(char** nickname, int* scores, char* fileName) {
	std::ifstream leaderboard;
	leaderboard.open(fileName);

	if (!leaderboard.is_open())
	{
		std::cout << "Error! Failed to open file\n";
		return;
	}

	for (int i = 0; i < LEADERBOARD_SIZE; ++i)
	{
		leaderboard >> nickname[i] >> scores[i];
	}
	leaderboard.close();
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


	/*for (int i = 0; i < LEADERBOARD_SIZE; i++) {
		delete[] nickname[i];
	}
	delete[] nickname;
	delete[] fileName;*/
}

void printLeaderBoard() {
	_CrtDumpMemoryLeaks();
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
		/*for (int i = 0; i < LEADERBOARD_SIZE; i++) {
			delete[] nickname[i];
		}
		delete[] nickname;
		delete[] fileName;*/
		return;
	}
	int countOfPeople = 0;
	for (int i = 0; i < LEADERBOARD_SIZE; ++i)
	{
		leaderboard >> nickname[i] >> scores[i];
		std::cout << nickname[i] << " " << scores[i] << std::endl;
	}
	leaderboard.close();
	/*for (int i = 0; i < LEADERBOARD_SIZE; i++) {
		delete[] nickname[i];
	}
	delete[] nickname;
	delete[] fileName;*/
}
