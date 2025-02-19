#ifndef REVERSE_TIC_TAC_TOE_H
#define REVERSE_TIC_TAC_TOE_H
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Base Classes
class Board6 {
public:
    virtual void display_Board6() = 0;
    virtual bool update_Board6(int x, int y, char symbol) = 0;
    virtual bool is_loss(char symbol) = 0; // Reversed condition: Losing instead of winning
    virtual bool is_draw() = 0;
    virtual bool game_is_over() = 0;
    virtual bool is_valid_move(int x, int y) = 0; // To validate moves
    virtual ~Board6() {}
};

class Player6 {
public:
    string name;
    char symbol;

    Player6(string name, char symbol) : name(name), symbol(symbol) {}

    virtual void get_move(int &x, int &y) = 0;
    virtual ~Player6() {}
};

class RandomPlayer6 : public Player6 {
public:
    RandomPlayer6(string name, char symbol) : Player6(name, symbol) {
        srand(time(0));
    }

    void get_move(int &x, int &y) override {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (!is_valid_move(x, y)); // Ensure the move is valid
    }

private:
    bool is_valid_move(int x, int y) {
        return x >= 0 && x < 3 && y >= 0 && y < 3;
    }
};

class HumanPlayer6 : public Player6 {
public:
    HumanPlayer6(string name, char symbol) : Player6(name, symbol) {}

    void get_move(int &x, int &y) override {
        cout << name << ", your move ex(0 0 ,0 1,1 0....): ";
        cin >> x >> y;
    }
};

class GameManager6 {
    Board6 *board;
    vector<Player6 *> Player6s;

public:
    GameManager6(Board6 *board, vector<Player6 *> Player6s) : board(board), Player6s(Player6s) {}

    void run() {
        board->display_Board6();
        while (!board->game_is_over()) {
            for (size_t i = 0; i < Player6s.size(); i++) {
                Player6 *Player6 = Player6s[i];
                int x, y;
                Player6->get_move(x, y);
                while (!board->update_Board6(x, y, Player6->symbol)) {
                    cout << "Invalid move. Try again.\n";
                    Player6->get_move(x, y);
                }
                board->display_Board6();
                if (board->is_loss(Player6->symbol)) { // Check for losing condition
                    cout << Player6->name << " DIED!\n";
                    cout << Player6s[(i + 1) % Player6s.size()]->name << " WINS!\n"; // Announce the winner
                    return;
                }
                if (board->is_draw()) {
                    cout << "Draw!\n";
                    return;
                }
            }
        }
    }
};

// Derived Classes for Reverse Tic Tac Toe
class ReverseTicTacToeBoard6 : public Board6 {
    vector<vector<char>> grid;

public:
    ReverseTicTacToeBoard6() : grid(3, vector<char>(3, ' ')) {}

    void display_Board6() override {
        for (const auto &row : grid) {
            for (const auto &cell : row) {
                cout << (cell == ' ' ? '.' : cell) << " ";
            }
            cout << "\n";
        }
    }

    bool update_Board6(int x, int y, char symbol) override {
        if (!is_valid_move(x, y)) {
            return false;
        }
        grid[x][y] = symbol;
        return true;
    }

    bool is_valid_move(int x, int y) override {
        return x >= 0 && x < 3 && y >= 0 && y < 3 && grid[x][y] == ' ';
    }

    bool is_loss(char symbol) override {
        // Check rows and columns
        for (int i = 0; i < 3; i++) {
            if ((grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol) ||
                (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol))
                return true;
        }
        // Check diagonals
        if ((grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol) ||
            (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol))
            return true;

        return false;
    }

    bool is_draw() override {
        for (const auto &row : grid) {
            for (const auto &cell : row) {
                if (cell == ' ') return false;
            }
        }
        return true;
    }

    bool game_is_over() override {
        return is_draw() || is_loss('X') || is_loss('O');
    }
};

// Function to start the game
void play_game6() {
    char playAgain;
    do {
        cout << "=================Welcome to Reverse Tic Tac Toe!==================\n";
        cout << "Choose Game Mode:\n";
        cout << "1. User vs User\n";
        cout << "2. User vs AI\n";
        int choice;
        cin >> choice;

        ReverseTicTacToeBoard6 board;
        Player6 *Player61 = new HumanPlayer6("Player6 1", 'X');
        Player6 *Player62;

        if (choice == 1) {
            Player62 = new HumanPlayer6("Player6 2", 'O');
        } else {
            Player62 = new RandomPlayer6("AI", 'O');
        }

        GameManager6 game(&board, {Player61, Player62});
        game.run();

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

        delete Player61;
        delete Player62;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thank you for playing!\n";
}

#endif // REVERSE_TIC_TAC_TOE_H
