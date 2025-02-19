#ifndef PROBLEM3_5X5_TIC_TAC_TOE_H
#define PROBLEM3_5X5_TIC_TAC_TOE_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;

// Base Classes
class Board3 {
public:
    virtual void display_board() const = 0;
    virtual bool update_board(int x, int y, char symbol) = 0;
    virtual bool is_win() const = 0;
    virtual bool is_draw() const = 0;
    virtual bool game_is_over() const = 0;
    virtual ~Board3() = default;
};

class Player3 {
public:
    string name;
    char symbol;

    Player3(string name, char symbol) : name(name), symbol(symbol) {}
    virtual void get_move(int &x, int &y) const = 0;
    virtual ~Player3() = default;
};

class RandomPlayer3 : public Player3 {
public:
    int grid_size;

    RandomPlayer3(string name, char symbol, int grid_size)
            : Player3(name, symbol), grid_size(grid_size) {}

    void get_move(int &x, int &y) const override {
        x = rand() % grid_size;
        y = rand() % grid_size;
    }
};

class GameManager3 {
    Board3 *board;
    Player3 *Player3s[2];

public:
    GameManager3(Board3 *board, Player3 *p1, Player3 *p2) {
        this->board = board;
        Player3s[0] = p1;
        Player3s[1] = p2;
    }

    void run() {
        int x, y;
        board->display_board();

        while (!board->game_is_over()) {
            for (int i = 0; i < 2; ++i) {
                do {
                    Player3s[i]->get_move(x, y);
                } while (!board->update_board(x, y, Player3s[i]->symbol));

                board->display_board();
                if (board->is_win()) {
                    cout << Player3s[i]->name << " wins!" << endl;
                    return;
                }
                if (board->is_draw()) {
                    cout << "Draw!" << endl;
                    return;
                }
            }
        }
    }
};

// Derived Classes for the 5x5 Tic-Tac-Toe Variant

class TicTacToe5x5Board : public Board3 {
    vector<vector<char>> grid;
    int grid_size;
    map<char, int> scores;

public:
    TicTacToe5x5Board() : grid_size(5), grid(5, vector<char>(5, ' ')) {
        scores['X'] = 0;
        scores['O'] = 0;
    }

    void reset_board() {
        grid.assign(grid_size, vector<char>(grid_size, ' '));
        scores['X'] = 0;
        scores['O'] = 0;
    }

    void display_board() const override {
        for (const auto &row : grid) {
            for (const auto &cell : row) {
                cout << (cell == ' ' ? '.' : cell) << " ";
            }
            cout << endl;
        }
        cout << "Score: X = " << scores.at('X') << ", O = " << scores.at('O') << endl;
    }

    bool update_board(int x, int y, char symbol) override {
        if (x < 0 || x >= grid_size || y < 0 || y >= grid_size || grid[x][y] != ' ') {
            return false;
        }
        grid[x][y] = symbol;
        update_scores(symbol);
        return true;
    }

    bool is_win() const override {
        return false; // Winning is determined after the final scores are calculated.
    }

    bool is_draw() const override {
        for (const auto &row : grid) {
            for (const auto &cell : row) {
                if (cell == ' ') return false;
            }
        }
        return true;
    }

    bool game_is_over() const override {
        return is_draw();
    }

    void update_scores(char symbol) {
        scores[symbol] = count_three_in_a_rows(symbol);
    }

    int count_three_in_a_rows(char symbol) const {
        int count = 0;

        // Check rows for 3-in-a-row
        for (int i = 0; i < grid_size; ++i) {
            for (int j = 0; j <= grid_size - 3; ++j) {
                if (grid[i][j] == symbol && grid[i][j + 1] == symbol && grid[i][j + 2] == symbol)
                    ++count;
            }
        }

        // Check columns for 3-in-a-row
        for (int i = 0; i <= grid_size - 3; ++i) {
            for (int j = 0; j < grid_size; ++j) {
                if (grid[i][j] == symbol && grid[i + 1][j] == symbol && grid[i + 2][j] == symbol)
                    ++count;
            }
        }

        // Check diagonals for 3-in-a-row
        for (int i = 0; i <= grid_size - 3; ++i) {
            for (int j = 0; j <= grid_size - 3; ++j) {
                // Diagonal from top-left to bottom-right
                if (grid[i][j] == symbol && grid[i + 1][j + 1] == symbol && grid[i + 2][j + 2] == symbol)
                    ++count;
                // Diagonal from top-right to bottom-left
                if (grid[i][j + 2] == symbol && grid[i + 1][j + 1] == symbol && grid[i + 2][j] == symbol)
                    ++count;
            }
        }

        return count;
    }
};

class TicTacToe5x5Player3 : public Player3 {
public:
    TicTacToe5x5Player3(string name, char symbol) : Player3(name, symbol) {}

    void get_move(int &x, int &y) const override {
        cout << name << " (" << symbol << "), your move ex(0 0 ,0 1,1 0....): ";
        cin >> x >> y;
    }
};

void play_game3() {
    srand(static_cast<unsigned>(time(nullptr)));

    int choice;
    cout << "===========Welcome in 5 x 5 Tic Tac Toe Game===========\n";
    cout << "Choose an option:\n";
    cout << "1. Play with another Player3\n";
    cout << "2. Play with AI\n";
    cout << "Enter your choice: ";
    cin >> choice;

    TicTacToe5x5Board board;
    Player3 *Player31 = new TicTacToe5x5Player3("Player3 1", 'X');
    Player3 *Player32;

    if (choice == 1) {
        Player32 = new TicTacToe5x5Player3("Player3 2", 'O');
    } else {
        Player32 = new RandomPlayer3("Computer", 'O', 5);
    }

    GameManager3 game(&board, Player31, Player32);
    game.run();

    cout << "Game Over. Do you want to play again? (y/n): ";
    char play_again;
    cin >> play_again;

    if (play_again == 'n' || play_again == 'N') {
        delete Player31;
        delete Player32;
        return;
    }

    board.reset_board();
    delete Player31;
    delete Player32;
    play_game3();  // Recursively play again
}

#endif // PROBLEM3_5X5_TIC_TAC_TOE_H

