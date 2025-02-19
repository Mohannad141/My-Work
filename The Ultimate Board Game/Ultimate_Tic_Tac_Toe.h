#ifndef PROBLEM8_ULTIMATE_TIC_TAC_TOE_H
#define PROBLEM8_ULTIMATE_TIC_TAC_TOE_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Base class representing a player8
class player8 {
public:
    string name;
    char symbol;
    player8(const string& name, char symbol) : name(name), symbol(symbol) {}
    virtual void get_move(int& x, int& y) = 0; // Pure virtual function for player8 moves
};

// Abstract class for the game board
class Board8 {
public:
    virtual void display() = 0; // Display the board
    virtual bool update(int x, int y, char symbol) = 0; // Update the board with a move
    virtual bool is_win() = 0; // Check if there's a winner
    virtual bool is_draw() = 0; // Check if the game is a draw
    virtual bool is_valid_move(int x, int y) = 0; // Validate a move
    virtual ~Board8() {}
};

// Manages the flow of the game
class GameManager8 {
    Board8* board;
    player8* player8s[2];
public:
    GameManager8(Board8* board, player8* player81, player8* player82) : board(board) {
        player8s[0] = player81;
        player8s[1] = player82;
    }

    void run() {
        int x, y;
        board->display();
        while (!board->is_win() && !board->is_draw()) {
            for (int i = 0; i < 2; ++i) {
                player8s[i]->get_move(x, y); // Get the player8's move
                while (!board->update(x - 1, y - 1, player8s[i]->symbol)) { // Ensure the move is valid
                    cout << "Invalid move. Try again.\n";
                    player8s[i]->get_move(x, y);
                }
                board->display(); // Display the board after the move
                if (board->is_win()) {
                    cout << player8s[i]->name << " wins!\n";
                    return;
                }
                if (board->is_draw()) {
                    cout << "It's a draw!\n";
                    return;
                }
            }
        }
    }
};

// Specific implementation of the Ultimate Tic Tac Toe board
class UltimateBoard : public Board8 {
    struct SmallBoard {
        char grid[3][3];

        // Check if a player8 has won this small board
        bool is_win(char symbol) {
            for (int i = 0; i < 3; ++i) {
                if ((grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol) ||
                    (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol)) {
                    return true;
                }
            }
            return (grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol) ||
                   (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol);
        }

        // Check if this small board is a draw
        bool is_draw() {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (grid[i][j] == ' ') return false;
                }
            }
            return true;
        }

        SmallBoard() {
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    grid[i][j] = ' '; // Initialize the grid with empty spaces
        }
    };

    SmallBoard small_boards[3][3]; // 3x3 grid of small boards
    char main_board[3][3]; // Main board showing the status of each small board

public:
    UltimateBoard() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                main_board[i][j] = ' '; // Initialize the main board with empty spaces
    }

    void display() override {
        cout << "\nMain Board (3x3):\n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << " " << (main_board[i][j] == ' ' ? '-' : main_board[i][j]);
            }
            cout << "\n";
        }

        cout << "\nSmaller Boards (3x3 each):\n";
        for (int big_row = 0; big_row < 3; ++big_row) {
            for (int small_row = 0; small_row < 3; ++small_row) {
                for (int big_col = 0; big_col < 3; ++big_col) {
                    for (int small_col = 0; small_col < 3; ++small_col) {
                        char cell = small_boards[big_row][big_col].grid[small_row][small_col];
                        cout << (cell == ' ' ? '-' : cell);
                        if (small_col < 2) cout << " ";
                    }
                    cout << " | ";
                }
                cout << "\n";
            }
            if (big_row < 2) cout << "---------------------\n";
        }
        cout << "\n";
    }

    // Updates the state of the board with the player8's move
    bool update(int x, int y, char symbol) override {
        int board_x = x / 3, board_y = y / 3;
        int cell_x = x % 3, cell_y = y % 3;

        // Check if the move is within bounds and the cell is empty
        if (board_x < 0 || board_x >= 3 || board_y < 0 || board_y >= 3 ||
            cell_x < 0 || cell_x >= 3 || cell_y < 0 || cell_y >= 3) {
            return false;
        }

        if (small_boards[board_x][board_y].grid[cell_x][cell_y] == ' ') {
            small_boards[board_x][board_y].grid[cell_x][cell_y] = symbol;

            // Update the main board if the small board is won
            if (small_boards[board_x][board_y].is_win(symbol)) {
                main_board[board_x][board_y] = symbol;
            }
            return true;
        }
        return false;
    }

    // Check if the main board has a winner
    bool is_win() override {
        for (int i = 0; i < 3; ++i) {
            if ((main_board[i][0] != ' ' && main_board[i][0] == main_board[i][1] && main_board[i][1] == main_board[i][2]) ||
                (main_board[0][i] != ' ' && main_board[0][i] == main_board[1][i] && main_board[1][i] == main_board[2][i])) {
                return true;
            }
        }
        return (main_board[0][0] != ' ' && main_board[0][0] == main_board[1][1] && main_board[1][1] == main_board[2][2]) ||
               (main_board[0][2] != ' ' && main_board[0][2] == main_board[1][1] && main_board[1][1] == main_board[2][0]);
    }

    // Check if the main board is a draw
    bool is_draw() override {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (main_board[i][j] == ' ') return false;
            }
        }
        return true;
    }

    // Check if a move is valid
    bool is_valid_move(int x, int y) override {
        int board_x = x / 3, board_y = y / 3;
        int cell_x = x % 3, cell_y = y % 3;
        return small_boards[board_x][board_y].grid[cell_x][cell_y] == ' ';
    }
};

// Human player8 class
class Ultimateplayer8 : public player8 {
public:
    Ultimateplayer8(const string& name, char symbol) : player8(name, symbol) {}
    void get_move(int& x, int& y) override {
        cout << name << " (" << symbol << "), your move ex(1 1 ,1 2,2 1....,9 9): ";
        cin >> x >> y;
    }
};

// Random AI player8 class
class UltimateRandomplayer8 : public player8 {
public:
    UltimateRandomplayer8(const string& name, char symbol) : player8(name, symbol) {}
    void get_move(int& x, int& y) override {
        do {
            x = rand() % 9;
            y = rand() % 9;
        } while (!UltimateBoard().is_valid_move(x, y)); // Ensure a valid random move
        cout << name << " (" << symbol << ") random move: " << x + 1 << " " << y + 1 << "\n";
    }
};

void play_game8() {
    srand(static_cast<unsigned>(time(0))); // Seed random number generator

    // Ask the user if they want to play against AI or another player8
    int choice;
    cout << "Welcome to Ultimate Tic Tac Toe!\n";
    cout << "Choose your game mode:\n";
    cout << "1. Play with random computer \n";
    cout << "2. Play with another real player\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    player8* player81;
    player8* player82;

    if (choice == 1) {
        // Play with AI
        player81 = new Ultimateplayer8("player 1", 'X');
        player82 = new UltimateRandomplayer8("random ", 'O');
    } else {
        // Play with another player8
        cout << "Enter the name of player 2: ";
        player81 = new Ultimateplayer8("player 1", 'X');
        player82 = new Ultimateplayer8("player 2", 'O');
    }

    // Create game board
    UltimateBoard* board = new UltimateBoard();

    // Start the game
    GameManager8 game(board, player81, player82);
    game.run();

    delete board;
    delete player81;
    delete player82;
}

#endif // PROBLEM8_ULTIMATE_TIC_TAC_TOE_H