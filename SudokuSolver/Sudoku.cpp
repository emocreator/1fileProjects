#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

const int N = 9;

bool is_valid(vector<vector<int>>& board, int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solve_sudoku(vector<vector<int>>& board) {
    int row = -1, col = -1;
    bool isEmpty = true;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                row = i;
                col = j;
                isEmpty = false;
                break;
            }
        }
        if (!isEmpty) {
            break;
        }
    }

    if (isEmpty) {
        return true;
    }

    for (int num = 1; num <= N; num++) {
        if (is_valid(board, row, col, num)) {
            board[row][col] = num;
            if (solve_sudoku(board)) {
                return true;
            }
            board[row][col] = 0;
        }
    }

    return false;
}

bool solve_sudoku_stochastic(vector<vector<int>>& board, int max_iterations) {
    vector<pair<int, int>> empty_cells;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                empty_cells.push_back({i, j});
            }
        }
    }

    random_device rd;
    mt19937 gen(rd());

    for (int iteration = 0; iteration < max_iterations; iteration++) {
        shuffle(empty_cells.begin(), empty_cells.end(), gen);

        for (auto& cell : empty_cells) {
            int row = cell.first, col = cell.second;
            vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            shuffle(numbers.begin(), numbers.end(), gen);

            for (int num : numbers) {
                if (is_valid(board, row, col, num)) {
                    board[row][col] = num;
                    break;
                }
            }
        }

        // Check if the board is solved
        bool solved = true;
        for (int i = 0; i < N && solved; i++) {
            for (int j = 0; j < N && solved; j++) {
                if (board[i][j] == 0) {
                    solved = false;
                }
            }
        }

        if (solved) {
            return true;
        }
    }

    return false;
}
