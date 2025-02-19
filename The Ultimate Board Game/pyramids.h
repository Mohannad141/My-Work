
#ifndef ASSIGNMENT_DEMO_WITHOUT_AI_BONUS_PYRAMIDS_H
#define ASSIGNMENT_DEMO_WITHOUT_AI_BONUS_PYRAMIDS_H


#include "BoardGame_Classes.h"

template <typename T>
class Pyramids_boards:public Board<T> {
public:
    Pyramids_boards ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class pyramids_Player : public Player<T> {
public:
    pyramids_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class pyramids_Random_Player : public RandomPlayer<T>{
public:
    pyramids_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for Pyramids_boards
template <typename T>
Pyramids_boards <T>:: Pyramids_boards () {
    this->rows = 3;
    this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this -> board [0][0] = '#';
    this -> board [0][1] = '#';
    this -> board [1][0] = '#';
    this -> board [0][3] = '#';
    this -> board [0][4] = '#';
    this -> board [1][4] = '#';
    this->n_moves = 0;
}

template <typename T>
bool Pyramids_boards<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid

    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0) && (this ->board [x][y] = '#')) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Pyramids_boards<T>::display_board() {
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
bool Pyramids_boards<T>::is_win() {
    // Check horizontal

        if ((this->board[1][1] == this->board[1][2] && this->board[1][2] == this->board[1][3] && this->board[1][1] != 0) ||
            (this->board[2][0] == this->board[2][1] && this->board[2][1] == this->board[2][2] && this->board[2][0] != 0) ||
            (this->board[2][1] == this->board[2][2] && this->board[2][2] == this->board[2][3] && this->board[2][1] != 0) ||
            (this->board[2][2] == this->board[2][3] && this->board[2][3] == this->board[2][4] && this->board[2][2] != 0)) {
            return true;
        }

    // Check diagonals
    if ((this->board[2][0] == this->board[1][1] && this->board[1][1] == this->board[0][2] && this->board[2][0] != 0) ||
        (this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4] && this->board[0][2] != 0)) {
        return true;
    }
    //check vertical
    if ((this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2] && this->board[0][2] != 0))
    {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Pyramids_boards<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Pyramids_boards<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for pyramids_Player
template <typename T>
pyramids_Player<T>::pyramids_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void pyramids_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for pyramids_Random_Player
template <typename T>
pyramids_Random_Player<T>::pyramids_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void pyramids_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}






#endif //ASSIGNMENT_DEMO_WITHOUT_AI_BONUS_PYRAMIDS_H
