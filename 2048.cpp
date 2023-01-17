
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

}

int main()
{
    std::cout << "Hello World!\n";
    while (true)
    {
        printBoard(board, N);
        char command;
        std::cin >> command;
    }
}

