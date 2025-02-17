#include <iostream>
#include "BoardGame_Classes.h"
#include "Connect4.h"
#include "pyramids.h"
#include "wordtictactoe.h"
#include "numericaltictactoe.h"
#include "SUS.h"
#include <Pyramid_MinMaxPlayer.h>
#include <Connect4_MinMaxPlayer.h>
using namespace std;



int main() {
    while (true)
    {
        cout << "welcome to my games \n please choose the game u want to play \n 1) pyramids \n 2) connect 4\n 4) Word Tic-tac-toe\n 5) Numerical Tic-tac-toe\n 9) SUS\n ";
        int menu;
        cin>>menu;



        if ( menu == 1) {
            int choice;
            Player<char> *players[2];
            Pyramids_boards<char> *P = new Pyramids_boards<char>();
            string playerXName, player2Name;

            // Set up player 1
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[0] = new pyramids_Player<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new pyramids_Random_Player<char>('X');
                    break;
                case 3:
                    players[0] = new Pyramid_MinMax_Player<char>('X');
                    players[0]->setBoard(P);
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    return 1;
            }

            // Set up player 2
            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[1] = new pyramids_Player<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new pyramids_Random_Player<char>('O');
                    break;
                case 3:
                    players[1] = new Pyramid_MinMax_Player<char>('O');
                    players[1]->setBoard(P);
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

            // Create the game manager and run the game
            GameManager<char> Pyramid(P, players);
            Pyramid.run();

            // Clean up
            delete P;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }

        }
        else if ( menu == 2) {
            int choice;
            Player<char> *players[2];
            Connect4_Board<char> *C = new Connect4_Board<char>();
            string playerXName, player2Name;

            // Set up player 1
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[0] = new Connect4_Player<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new Connect4_Random_Player<char>('X');
                    break;
                case 3:
                    players[0] = new Pyramid_MinMax_Player<char>('X');
                    players[0]->setBoard(C);
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    return 1;
            }

            // Set up player 2
            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[1] = new Connect4_Player<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new Connect4_Random_Player<char>('O');
                    break;
                case 3:
                    players[1] = new Pyramid_MinMax_Player<char>('O');
                    players[1]->setBoard(C);
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

            // Create the game manager and run the game
            GameManager<char> connect4(C, players);
            connect4.run();

            // Clean up
            delete C;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }

        }
        else if (menu == 4) {
            int choice;
            Player<char> *players[2];
            Word_Board<char> *W = new Word_Board<char>();
            string playerXName, player2Name;

            // Set up player 1
            cout << "Enter Player 1 name: ";
            cin >> playerXName;
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[0] = new Word_Player<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new Word_Random_Player<char>('X');
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    return 1;
            }

            // Set up player 2
            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[1] = new Word_Player<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new Word_Random_Player<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

            // Create the game manager and run the game
            GameManager<char> Word(W, players);
            Word.run();

            // Clean up
            delete W;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }



        }
        else if (menu == 5) {
            int choice;
            Player<char> *players[2];
            Numerical_Board<char> *N = new Numerical_Board<char>();
            string playerXName, player2Name;

            // Set up player 1
            cout << "Enter Player 1 name: ";
            cin >> playerXName;
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[0] = new Numerical_Player<char>(playerXName, ' ');
                    break;
                case 2:
                    players[0] = new Numerical_Random_Player<char>('1');

                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    return 1;
            }

            // Set up player 2
            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[1] = new Numerical_Player<char>(player2Name, ' ');
                    break;
                case 2:
                    players[1] = new Numerical_Random_Player<char>('2');

                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

            // Create the game manager and run the game
            GameManager<char> Numerical(N, players);
            Numerical.run();

            // Clean up
            delete N;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
        }
        else if (menu == 9)
        {
            int choice;
            Player<char> *players[2];
            SUS_Board<char> *S = new SUS_Board<char>();
            string playerXName, player2Name;

            // Set up player 1
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[0] = new SUS_Player<char>(playerXName, 'S');
                    break;
                case 2:
                    players[0] = new SUS_Random_Player<char>('S');
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    return 1;
            }

            // Set up player 2
            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[1] = new SUS_Player<char>(player2Name, 'U');
                    break;
                case 2:
                    players[1] = new SUS_Random_Player<char>('U');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

            // Create the game manager and run the game
            GameManager<char> connect4(S, players);
            connect4.run();

            // Clean up
            delete S;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
        }

    }



}