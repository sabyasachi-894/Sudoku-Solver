#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int SIZE = 9;

// Function to print the Sudoku grid
void printSudoku(const std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to check if a number can be placed at a particular position
bool isSafe(const std::vector<std::vector<int>>& grid, int row, int col, int num) {
    // Check if the number is not already present in the current row and column
    for (int i = 0; i < SIZE; ++i) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Checking if the number is not present in the 3x3 grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using recursive backtracking
bool solveSudoku(std::vector<std::vector<int>>& grid) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (grid[row][col] == 0) {
                for (int num = 1; num <= SIZE; ++num) {
                    if (isSafe(grid, row, col, num)) {
                        grid[row][col] = num;

                        if (solveSudoku(grid)) {
                            return true;
                        }

                        grid[row][col] = 0;
                    }
                }

                return false;
            }
        }
    }

    return true;
}

// Function to generate a random solved Sudoku puzzle
void generateRandomSolvedSudoku(std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            grid[i][j] = (i * 3 + i / 3 + j) % SIZE + 1;
        }
    }

    // Shuffling rows and columns to create a valid Sudoku grid
    for (int i = 0; i < SIZE; ++i) {
        int randRow = std::rand() % SIZE;
        int randCol = std::rand() % SIZE;

        // Swap rows
        std::swap(grid[i], grid[randRow]);

        // Swap columns
        for (int j = 0; j < SIZE; ++j) {
            std::swap(grid[j][i], grid[j][randCol]);
        }
    }
}

// Function to create a solvable unfilled Sudoku puzzle with a random number of cells removed
void createUnfilledSudoku(std::vector<std::vector<int>>& grid) {
    int numToRemove = SIZE * SIZE / 2; // Adjust the number of cells to remove as needed

    for (int k = 0; k < numToRemove; ++k) {
        int i = std::rand() % SIZE;
        int j = std::rand() % SIZE;

        // Ensuring that the cell is not already empty
        while (grid[i][j] == 0) {
            i = std::rand() % SIZE;
            j = std::rand() % SIZE;
        }

        int temp = grid[i][j];
        grid[i][j] = 0;

        // Ensuring the puzzle remains solvable
        std::vector<std::vector<int>> tempGrid = grid;
        if (!solveSudoku(tempGrid)) {
            grid[i][j] = temp; // Revert the change if it makes the puzzle unsolvable
        }
    }
}

int main() {
    std::vector<std::vector<int>> solvedSudoku(SIZE, std::vector<int>(SIZE, 0));

    // Random seed is set based on the current time
    std::srand(static_cast<unsigned int>(std::time(0)));

    // A random solved Sudoku puzzle is generated
    generateRandomSolvedSudoku(solvedSudoku);

    // A solvable unfilled Sudoku puzzle with a random number of cells removed, is created
    std::vector<std::vector<int>> unsolvedSudoku = solvedSudoku;
    createUnfilledSudoku(unsolvedSudoku);

    std::cout << "Sudoku Puzzle with Removed Cells:" << std::endl;
    printSudoku(unsolvedSudoku);

    // The Sudoku puzzle is solved
    std::vector<std::vector<int>> solvedGrid = unsolvedSudoku;
    if (solveSudoku(solvedGrid)) {
        std::cout << "\nSolved Sudoku Puzzle:" << std::endl;
        printSudoku(solvedGrid);
    } else {
        std::cout << "\nError: Unable to solve the Sudoku puzzle." << std::endl;
    }

    return 0;
}
