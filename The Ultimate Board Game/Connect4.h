
#ifndef ASSIGNMENT_DEMO_WITHOUT_AI_BONUS_CONNECT4_H
#define ASSIGNMENT_DEMO_WITHOUT_AI_BONUS_CONNECT4_H
#include "BoardGame_Classes.h"

template <typename T>
class Connect4_Board:public Board<T> {
public:
    Connect4_Board();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Connect4_Player : public Player<T> {
public:
    Connect4_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Connect4_Random_Player : public RandomPlayer<T>{
public:
    Connect4_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for Connect4_Board
template <typename T>
Connect4_Board<T>::Connect4_Board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}
template <typename T>
bool Connect4_Board<T>::update_board(int x, int y, T mark) {
    // Check if x, y are within valid bounds
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        return false;
    }

    // Check if the cell is empty
    if (this->board[x][y] != 0) {
        return false; // Cell already occupied
    }

    // For non-bottom rows, ensure the cell below (`x-1`) is occupied
    if (x != this->rows - 1 && this->board[x + 1][y] == 0) {
        cout<<"cell below is not occupied please try again !"<<endl;
        return false; // The cell below isn't occupied
    }

    // Place the piece
    this->board[x][y] = toupper(mark);
    this->n_moves++;
    return true;
}


// Display the board and the pieces on it
template <typename T>
void Connect4_Board<T>::display_board() {
    // Display column indices
    cout << "    ";
    for (int j = 0; j < this->columns; j++) {
        cout << " " << j << "  ";
    }
    cout << "\n   " << string(this->columns * 4 + 1, '-') << "\n";

    // Display the board with row indices
    for (int i = 0; i < this->rows; i++) {
        cout << " " << i << " |";  // Row index
        for (int j = 0; j < this->columns; j++) {
            cout << " " << this->board[i][j] << " |";
        }
        cout << "\n   " << string(this->columns * 4 + 1, '-') << "\n";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool Connect4_Board<T>::is_win() {
    // Check horizontal wins
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 4; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j + 1] == this->board[i][j + 2] &&
                this->board[i][j + 2] == this->board[i][j + 3]) {
                return true;
            }
        }
    }

    // Check vertical wins
    for (int i = 0; i <= this->rows - 4; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i + 1][j] &&
                this->board[i + 1][j] == this->board[i + 2][j] &&
                this->board[i + 2][j] == this->board[i + 3][j]) {
                return true;
            }
        }
    }

    // Check diagonal (bottom-left to top-right)
    for (int i = 0; i <= this->rows - 4; i++) {
        for (int j = 0; j <= this->columns - 4; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i + 1][j + 1] == this->board[i + 2][j + 2] &&
                this->board[i + 2][j + 2] == this->board[i + 3][j + 3]) {
                return true;
            }
        }
    }

    // Check diagonal (top-left to bottom-right)
    for (int i = 3; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 4; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i - 1][j + 1] &&
                this->board[i - 1][j + 1] == this->board[i - 2][j + 2] &&
                this->board[i - 2][j + 2] == this->board[i - 3][j + 3]) {
                return true;
            }
        }
    }

    // No win found
    return false;
}


// Return true if 9 moves are done and no winner
template <typename T>
bool Connect4_Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool Connect4_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
Connect4_Player<T>::Connect4_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Connect4_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 5) for rows and (0 to 6) for columns separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
Connect4_Random_Player<T>::Connect4_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 6;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Connect4_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}




#endif //ASSIGNMENT_DEMO_WITHOUT_AI_BONUS_CONNECT4_H
