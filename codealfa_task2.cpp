#include <iostream>
#include <vector>

using namespace std;

const int N = 9;

// Function to print the Sudoku board
void printSudoku(const vector<vector<int>>& sudoku) 
{
    for (int i = 0; i < N; ++i) 
    {
        for (int j = 0; j < N; ++j) 
        {
            cout << sudoku[i][j] << " ";
            if ((j + 1) % 3 == 0 && j < N - 1) cout << "| ";
        }
        cout << endl;
        if ((i + 1) % 3 == 0 && i < N - 1) cout << "------+-------+------" << endl;
    }
}

// Function to check if it's safe to place a number in a cell
bool isSafe(vector<vector<int>>& sudoku, int row, int col, int num) 
{
    // Check if 'num' is not present in the current row and column
    for (int x = 0; x < N; ++x)
        if (sudoku[row][x] == num || sudoku[x][col] == num)
            return false;

    // Check if 'num' is not present in the current 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (sudoku[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Function to find an empty cell in the Sudoku board
bool findEmptyCell(const vector<vector<int>>& sudoku, int& row, int& col) 
{
    for (row = 0; row < N; ++row)
        for (col = 0; col < N; ++col)
            if (sudoku[row][col] == 0)
                return true;
    return false;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int>>& sudoku) 
{
    int row, col;

    // If there is no empty cell, the Sudoku is solved
    if (!findEmptyCell(sudoku, row, col))
        return true;

    // Try placing a number from 1 to 9 in the empty cell
    for (int num = 1; num <= 9; ++num) {
        if (isSafe(sudoku, row, col, num)) {
            sudoku[row][col] = num;

            // Recursively solve the rest of the Sudoku
            if (solveSudoku(sudoku))
                return true;

            // If placing 'num' in the current cell doesn't lead to a solution, backtrack
            sudoku[row][col] = 0;
        }
    }

    // No number can be placed in the current cell, backtrack
    return false;
}

int main() 
{
    vector<vector<int>> sudoku
    {
        {0, 8, 0, 0, 0, 1, 4, 9, 3},
        {0, 1, 2, 0, 0, 0, 0, 0, 7},
        {4, 0, 0, 7, 0, 0, 8, 0, 0},
        {0, 0, 1, 0, 6, 0, 2, 4, 5},
        {0, 6, 9, 0, 1, 0, 3, 7, 0},
        {2, 4, 8, 0, 3, 0, 9, 0, 0},
        {0, 0, 6, 0, 0, 4, 0, 0, 2},
        {8, 0, 0, 0, 0, 0, 6, 3, 0},
        {7, 5, 3, 6, 0, 0, 0, 8, 0}
    };

    cout << "Sudoku Puzzle:" << endl;
    printSudoku(sudoku);

    if (solveSudoku(sudoku)) 
    {
        cout << "\nSudoku Solution:" << endl;
        printSudoku(sudoku);
    } else {
        cout << "\nNo solution exists." << endl;
    }

    return 0;
}
