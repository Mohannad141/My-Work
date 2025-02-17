#ifndef SUS_H
#define SUS_H
#include <vector>
#include <fstream>
#include <unordered_set>
#include <set>
#include"BoardGame_Classes.h"

using namespace std;

int a , b;
int splayer_counter = 0;
int uplayer_counter = 0;
bool diag1_iscounted = false;
bool diag2_iscounted = false;

template <typename T>
class SUS_Board:public Board<T> {
public:
    SUS_Board ();
    void SUS_count(int& c, int& d);

    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    ~SUS_Board ();


};

template <typename T>
class SUS_Player : public Player<T> {
public:
    SUS_Player (string name, T symbol);
    void getmove(int& x, int& y) ;



};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T>{

public:
    SUS_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include<bits/stdc++.h>

using namespace std;

// Constructor for X_O_Board
template <typename T>
SUS_Board<T>::SUS_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

////////////////////////////////////
template <typename T>
bool SUS_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == ' '|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            a = x;
            b = y;
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void SUS_Board<T>::display_board() {
    cout << "  ";
    for (int j = 0; j < this->columns; j++) {
        cout << "  " << j << "  ";
    }
    cout << "\n";

    for (int i = 0; i < this->rows; i++) {
        cout << i << " "; // Row header
        for (int j = 0; j < this->columns; j++) {
            cout << "| " << this->board[i][j] << " ";
        }
        cout << "|\n";
        cout << "  " << string(this->columns * 4, '-') << "\n";
    }
    SUS_count(splayer_counter, uplayer_counter);
    cout << endl;
}

template <typename T>
void SUS_Board<T>::SUS_count(int& c, int& d) {
    // Check rows and columns
            if (this->board[a][0] == this->board[a][2] && this->board[a][0] == 'S' && this->board[a][1] == 'U')
            {
                if (this->n_moves % 2 == 0) (uplayer_counter)++;
                else (splayer_counter)++;
            }
            if (this->board[0][b] == this->board[2][b] && this->board[0][b] == 'S' && this->board[1][b] == 'U')
            {
                if (this->n_moves % 2 == 0) (uplayer_counter)++;
                else (splayer_counter)++;
            }


    // Check diagonals
    if((a == 0 && b == 0) || (a == 1 && b == 1) || (a == 0 && b == 2) || (a == 2 && b == 0) || (a == 2 && b == 2))
        {
            if (this->board[0][0] == this->board[2][2] && this->board[0][0] == 'S' && this->board[1][1] == 'U')
            {
                if(!diag1_iscounted)
                    {
                        diag1_iscounted = true;
                        if (this->n_moves % 2 == 0) (uplayer_counter)++;
                        else (splayer_counter)++;
                    }

            }
            if (this->board[0][2] == this->board[2][0] && this->board[0][2] == 'S' && this->board[1][1] == 'U')
            {
                if(!diag2_iscounted)
                {
                    diag2_iscounted = true;
                    if (this->n_moves % 2 == 0) (uplayer_counter)++;
                    else (splayer_counter)++;
                }
            }
        }
}

template <typename T>
bool SUS_Board<T>::is_win() {
    if (this->n_moves < 9) return false;
    SUS_count(splayer_counter, uplayer_counter);

    if (splayer_counter > uplayer_counter) {
            cout << "Player S wins with " << splayer_counter << endl;
            return true;
        }
        else if (uplayer_counter > splayer_counter) {
            cout << "Player U wins with " << uplayer_counter << endl;
            return true;
        }
        return false;
}



template <typename T>
bool SUS_Board<T>::is_draw() {
    if (this->n_moves < 9)
        return false;
    return (splayer_counter == uplayer_counter);
}

template <typename T>
bool SUS_Board<T>::game_is_over() {
    if (this->n_moves < 9)
        return false;

    return (is_win() || is_draw());
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
SUS_Player<T>::SUS_Player(string name, T mark ) : Player<T>(name, mark) {}



template <typename T>
void SUS_Player<T>::getmove(int& x, int& y) {
    x=y=3;
    cout << "\nPlease player( "<<this->getsymbol()<<" )enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;

}

// Constructor for X_O_Random_Player
template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void SUS_Random_Player<T>::getmove(int& x, int& y) {
    // Generate a random move
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;


}

template <typename T>
SUS_Board<T>::~SUS_Board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}



#endif // SUS_H
