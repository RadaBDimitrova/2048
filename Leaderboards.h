#pragma once

void strCopy(const char* from, char* to);

void updateLeaderBoard(int dimension, char* name, int score, char** nickname, int* scores);

char* getFileName(int dimension);

void fillLeaderboard(char** nickname, int* scores, char* fileName);

void writeToFile(char** nickname, int* scores, char* fileName);

void LeaderBoard(char* name, int score, int dimension);

void printLeaderBoard();