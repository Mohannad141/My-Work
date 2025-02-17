//
// Created by mikel on 12/2/2024.
//

#ifndef NUMERICALTICTACTOE_H
#define NUMERICALTICTACTOE_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>

template <typename T>
class Numerical_Board:public Board<T> {
public:
    Numerical_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Numerical_Player : public Player<T> {
public:
    Numerical_Player (string name, T symbol);
    void getmove(int& x, int& y); ;

};

template <typename T>
class Numerical_Random_Player : public RandomPlayer<T>{
public:
    Numerical_Random_Player (T symbol);
    void getmove(int &x, int &y); ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for Numerical_Board
template <typename T>
Numerical_Board<T>::Numerical_Board() {
    this->rows = this->columns = 3;
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
bool Numerical_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
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
void Numerical_Board<T>::display_board() {
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
bool Numerical_Board<T>::is_win() {

    // Define winning sum
    const int winning_sum = 15;

    // Check rows
    for (int i = 0; i < this->rows; i++) {
        int sum = 0;
        for (int j = 0; j < this->columns; j++) {
            sum += this->board[i][j] - '0';
        }
        if (sum == winning_sum) {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < this->columns; i++) {
        int sum = 0;
        for (int j = 0; j < this->rows; j++) {
            sum += this->board[j][i]  - '0';
        }
        if (sum == winning_sum) {
            return true;
        }
    }

    // Check diagonals
    int sum1 = 0;
    int sum2 = 0;
    for (int i = 0; i < this->rows; i++) {
        sum1 += this->board[i][i]  - '0';
        sum2 += this->board[i][this->columns - 1 - i] - '0';
    }
    if (sum1 == winning_sum || sum2 == winning_sum) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Numerical_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Numerical_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for Numerical_Player
template <typename T>
Numerical_Player<T>::Numerical_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Numerical_Player<T>::getmove(int& x, int& y) {
    static const vector<int> odd = {1, 3, 5, 7, 9};
    static const vector<int> even = {2, 4, 6, 8, 10};
    bool flag = true;
    T mark;

    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;

    while (flag) {
        cout << "Please enter your number: ";
        cin >> mark;
        int mark_int = mark - '0';

        if (mark_int % 2 == 1) {
            if (find(odd.begin(), odd.end(), mark_int) != odd.end()) {
                this->symbol = mark;
                flag = false;
            } else {
                cout << "\nInvalid input. Player 1 can only choose an odd number.\n";
            }
        } else if (mark_int % 2 == 0) {
            if (find(even.begin(), even.end(), mark_int) != even.end()) {
                this->symbol = mark;
                flag = false;
            } else {
                cout << "\nInvalid input. Player 2 can only choose an even number.\n";
            }
        }
    }
}


// Constructor for Numerical_Random_Player
template <typename T>
Numerical_Random_Player<T>::Numerical_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Numerical_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    srand(time(0));
    if (((this->symbol) - '0') % 2 == 1) {
        static const vector<int> odd = {1, 3, 5, 7, 9};
        int index = rand() % (odd.size() - 1) ;
        this->symbol = '0' + odd[index];  // Convert int to char and assign
    } else if (((this->symbol) - '0') % 2 == 0) {
        static const vector<int> even = {2, 4, 6, 8, 10};
        int index = rand() % (even.size() - 1);
        this->symbol = '0' + even[index];  // Convert int to char and assign
    }
}







#endif //NUMERICALTICTACTOE_H
