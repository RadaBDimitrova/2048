#pragma once

void clearConsole();

void printBoard(int** arr, int size);

int score(int** arr, int size);

bool emptyArray(int** arr, int size);

bool checkPossibleMoves(int** arr, int size);

bool isEmptySpace(int** arr, int size);

void checkInput(int& num);

bool win(int** arr, int size);
