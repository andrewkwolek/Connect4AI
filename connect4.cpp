#include "connect4.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;
void terminalPlay() {
    string Player1;
    string Player2;
    int n;
    char c;
    Board brd = getBoard(Player1, Player2);
    //getBoard(Player1, Player2);
    bool endGame = false;
    while (!endGame) {
        brd.prettyPrintBoard(cout);
        cout << "\nEnter: the column to move, q to quit, s to save" << endl;
        if (brd.toMove() == 1) {        //Chooses Player to move
            cout << Player1 << " enter your move: ";
        }
        else {
            cout << Player2 << " enter your move: ";
        }
        cin >> n;
        if (cin.good()) {       //Checks if input is good
            if (n < 1 || n > NUM_COLS) {    //Sees if the move is Illegal
                cout << "ILLEGAL MOVE: Try again" << endl;
            }
            else if (n >= 1 && n <= NUM_COLS) {     //Runs move and checks for winner
                int move = n - 1;
                Result result = brd.makeMove(move);
                if (result == IllegalMove) {
                    cout << "ILLEGAL MOVE: Try again" << endl;
                }
                else if (result == Win) {
                    if (brd.toMove() == 1) {
                        cout << "Congratulations " << Player2;
                        cout << "! You won!" << endl;
                    }
                    else {
                        cout << "Congratulations " << Player1;
                        cout << "! You won!" << endl;
                    }
                    endGame = true;
                }
                else if (result == Draw) {
                    cout << "Draw!" << endl;
                    endGame = true;
                }
                else if (result == NoResult) {
                }
            }
        }
        else {
            cin.clear();
            cin >> c;
            if (c == 'q') {
                cout << "Thanks for playing!" << endl;
                return;
            }
            else if (c == 's') {
                saveBoard(Player1, Player2, brd);
            }
        }
    }
    brd.prettyPrintBoard(cout);
    return;
}

Board getBoard(string &p1, string &p2) {
    char s;
    string fen;
    Board brd;
    cout << "Enter L to load a game, or P to play: " << flush;
    cin >> s;
    s = toupper(s);
    if (s == 'P') {         //Branch for Play
        string Junk;
        getline(cin, Junk);
        cout << "Player 1, enter your name: " << flush;
        getline(cin, p1);
        cout << endl << "Player 2, enter your name: " << flush;
        getline(cin, p2);
        brd = Board();
    }
    else if (s == 'L') {    //Branch for Load 
        string filename;
        cout << "Enter the filename: " << flush;
        cin >> filename;
        ifstream ous;
        ous.open(filename);
        getline(ous, p1);
        getline(ous, p2);
        getline(ous, fen);
        brd = Board(fen);
    }
    else{
        cout << "Whoops" << endl;
    }
    return brd;
}

void saveBoard(string p1, string p2, const Board &board) {
    cout << "Enter the filename: " << flush;
    string file_name;
    cin >> file_name;
    ofstream outs;
    outs.open(file_name.c_str());
    outs << p1 << endl;
    outs << p2 << endl;
    board.printBoard_as_FENstring(outs);
}
