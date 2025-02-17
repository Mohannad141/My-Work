
#ifndef ASSIGNMENT_DEMO_WITHOUT_AI_BONUS_WORDTICTACTOE_H
#define ASSIGNMENT_DEMO_WITHOUT_AI_BONUS_WORDTICTACTOE_H




#include "BoardGame_Classes.h"
#include <bits/stdc++.h>

template <typename T>
class Word_Board:public Board<T> {
public:
    Word_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Word_Player : public Player<T> {
public:
    Word_Player (string name, T symbol);
    void getmove(int& x, int& y); ;

};

template <typename T>
class Word_Random_Player : public RandomPlayer<T>{
public:
    Word_Random_Player (T symbol);
    void getmove(int &x, int &y); ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for Word_Board
template <typename T>
Word_Board<T>::Word_Board() {
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
bool Word_Board<T>::update_board(int x, int y, T mark) {
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
void Word_Board<T>::display_board() {
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
bool Word_Board<T>::is_win() {
    vector<string> v;
    ifstream infile("dic.txt");

    if (!infile) {
        cerr << "ERROR: Could not open input file!" << endl;
        return false;
    }

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string word;
        while (ss >> word) {
            if (word.length() == 3) {
                v.push_back(word);
            }
        }
    }
    infile.close();

    // Check rows
    for (int i = 0; i < this->rows; i++) {
        string board_word = "";
        for (int j = 0; j < this->columns; j++) {
            board_word += this->board[i][j];
        }
        for (const string& x : v) {
            if (board_word == x) {
                return true;
            }
        }
    }

    // Check columns
    for (int i = 0; i < this->columns; i++) {
        string board_word = "";
        for (int j = 0; j < this->rows; j++) {
            board_word += this->board[j][i];
        }
        for (const string& x : v) {
            if (board_word == x) {
                return true;
            }
        }
    }

    // Check diagonals
    string diag1 = "", diag2 = "";
    for (int i = 0; i < this->rows; i++) {
        diag1 += this->board[i][i];
        diag2 += this->board[i][this->columns - 1 - i];
    }
    for (const string& x : v) {
        if (diag1 == x || diag2 == x) {
            return true;
        }
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Word_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Word_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for Word_Player
template <typename T>
Word_Player<T>::Word_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Word_Player<T>::getmove(int& x, int& y) {
    T mark;
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    cout << "Please enter your letter: ";
    cin >> mark;
    this->symbol = mark;
}

// Constructor for Word_Random_Player
template <typename T>
Word_Random_Player<T>::Word_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Word_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int index = rand() % 26;  // Generate a random index between 0 and 25
    this->symbol = letters[index];
}





#endif //ASSIGNMENT_DEMO_WITHOUT_AI_BONUS_WORDTICTACTOE_H
