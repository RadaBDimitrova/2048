
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

void updateBoard(int** arr, int size) {
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

int main()
{
    char nickname[100];
    int dimension = 0;
    std::cout << "Enter your nickname:";
    std::cin >> nickname;
    std::cout << "Enter dimension";
    std::cin >> dimension;
    while (true)
    {
        printBoard(board, dimension);
        char command;
        std::cin >> command;
    }
}

