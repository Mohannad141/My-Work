#ifndef CONNECT4_MINMAXPLAYER_H
#define CONNECT4_MINMAXPLAYER_H

#include "BoardGame_Classes.h"
#include <limits>
#include <algorithm> // For std::max and std::min
#include <iostream>  // For debug output
#include <utility>   // For std::pair

template <typename T>
class X_O_MinMax_Player : public Player<T> {
public:
    X_O_MinMax_Player(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    std::pair<int, int> getBestMove();
    void printBoard();  // For debugging purposes
};

//--------------------------------------- IMPLEMENTATION

using namespace std;

// Constructor for the templated class
template <typename T>
X_O_MinMax_Player<T>::X_O_MinMax_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

// Method to get the best move for the player
template <typename T>
void X_O_MinMax_Player<T>::getmove(int& x, int& y) {
    std::pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
    cout << "AI Player chooses move: (" << x << ", " << y << ")" << endl; // Debug output
}

// Minimax algorithm to evaluate the board of connect 4
template <typename T>
int X_O_MinMax_Player<T>::calculateMinMax(T s, bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    } else if (this->boardPtr->is_draw()) {
        return 0;
    }

    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int j = 0; j < 7; ++j) {
        for (int i = 5; i >= 0; --i) {
            if (this->boardPtr->update_board(i, j, s)) {
                int value = calculateMinMax(opponentSymbol, !isMaximizing);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (isMaximizing) {
                    bestValue = std::max(bestValue, value);
                } else {
                    bestValue = std::min(bestValue, value);
                }

                // Since a move was made in column `j`, we can skip checking higher rows in this column
                break;
            }
        }
    }

    return bestValue;
}

// Find the best move using the minimax algorithm
template <typename T>
std::pair<int, int> X_O_MinMax_Player<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};
    T opponentSymbol = (this->symbol == 'X') ? 'O' : 'X';

    // First, check if we can win in the next move
    for (int j = 0; j < 7; ++j) {
        for (int i = 5; i >= 0; --i) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0); // Undo move
                    cout << "AI Player can win by moving to: (" << i << ", " << j << ")" << endl; // Debug output
                    return {i, j}; // Winning move found
                }
                this->boardPtr->update_board(i, j, 0); // Undo move
                break; // No need to check higher rows in this column
            }
        }
    }

    // Second, check if the opponent can win in their next move and block them
    for (int j = 0; j < 7; ++j) {
        for (int i = 5; i >= 0; --i) {
            if (this->boardPtr->update_board(i, j, opponentSymbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0); // Undo move
                    cout << "AI Player blocks opponent at: (" << i << ", " << j << ")" << endl; // Debug output
                    return {i, j}; // Block opponent's winning move
                }
                this->boardPtr->update_board(i, j, 0); // Undo move
                break; // No need to check higher rows in this column
            }
        }
    }

    // If no immediate win or block, use MinMax to find the best move
    for (int j = 0; j < 7; ++j) {
        for (int i = 5; i >= 0; --i) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int moveValue = calculateMinMax(this->symbol, false);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                    cout << "AI Player evaluates move: (" << i << ", " << j << ") with value: " << moveValue << endl; // Debug output
                }
                break; // No need to check higher rows in this column
            }
        }
    }

    return bestMove;
}

template <typename T>
void X_O_MinMax_Player<T>::printBoard() {
    cout << "Current board state:" << endl;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            cout << this->boardPtr->get_cell(i, j) << " ";
        }
        cout << endl;
    }
}

#endif // CONNECT4_MINMAXPLAYER_H
