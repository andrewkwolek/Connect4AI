#include "ai.h"
#include "board.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

//Andrew Kwolek, Ryan Hertz, Matt Sutton, and Max Czyzycki

int RightSeverity(int row, int col, const Board& board, PieceType player);
int LeftSeverity(int row, int col, const Board& board, PieceType player);
int VerticalSeverity(int row, int col, const Board& board, PieceType player);
int DiagonalRightSeverity(int row, int col, const Board& board, PieceType player);
int DiagonalLeftSeverity(int row, int col, const Board& board, PieceType player);
int RightMove(int row, int col, const Board& board, PieceType player, int severity);
int LeftMove(int row, int col, const Board& board, PieceType player, int severity);
int VerticalMove(int row, int col, const Board& board, PieceType player, int severity);
int DiagonalRightMove(int row, int col, const Board& board, PieceType player, int severity);
int DiagonalLeftMove(int row, int col, const Board& board, PieceType player, int severity);
int ChooseMove(const Board& board);

int connect4AI(const Board& board){
    return ChooseMove(board);
}
/* Assings a severity of 4 if AI can win, a 3 if the opponent has 3 in a row,
to the right, a 2 for 2 in a row, and 1 for just one piece */
int RightSeverity(int row, int col, const Board& board, PieceType player) {
    Board brd = board;
        if (brd.atLocation(row, col + 1) == player) {
            if (col + 2 < NUM_COLS && brd.atLocation(row, col + 2) == player) {
                if ((col + 3 < NUM_COLS && brd.atLocation(row, col + 3) == Empty) && (row == 0 || (row - 1 >= 0 && brd.atLocation(row - 1, col + 3) != Empty))) {
                    if (player == Player2) {
                        return 4;
                    }
                    else {
                        return 3;
                    }
                }
            }
            else if ((col + 2 < NUM_COLS && brd.atLocation(row, col + 2) == Empty) && (col + 3 < NUM_COLS && brd.atLocation(row, col + 3) == player) && (row == 0 || (row - 1 >= 0 && brd.atLocation(row - 1, col + 2) != Empty))) {
                if (player == Player2) {
                    return 4;
                }
                else {
                    return 3;
                }
            }
            else if ((col + 2 < NUM_COLS && brd.atLocation(row, col + 2) == Empty) && (row == 0 || (row - 1 >= 0 && brd.atLocation(row - 1, col + 2) != Empty)))
                return 2;
        }
        else if (brd.atLocation(row, col + 1) == Empty && ((row - 1 >= 0 && brd.atLocation(row - 1, col + 1) != Empty) || row == 0)) {
            if ((col + 2 < NUM_COLS && brd.atLocation(row, col + 2) == player) && (col + 3 < NUM_COLS && brd.atLocation(row, col + 3) == player)) {
                if (player == Player2) {
                    return 4;
                }
                else {
                    return 3;
                }
            }
            else if ((col + 2 < NUM_COLS && brd.atLocation(row, col + 2) == player) && (col + 3 < NUM_COLS && brd.atLocation(row, col + 3) == Empty)) {
                return 2;
            }
            else if ((col + 2 < NUM_COLS && brd.atLocation(row, col + 2) == Empty) && (col + 3 < NUM_COLS && brd.atLocation(row, col + 3) == Empty)){
                return 1;
            }
        }
    return 0;
}
/* Assings a severity of 4 if AI can win, a 3 if the opponent has 3 in a row,
 to the left, a 2 for 2 in a row, and 1 for just one piece */
int LeftSeverity(int row, int col, const Board& board, PieceType player) {
    Board brd = board;
        if (col - 1 >= 0 && brd.atLocation(row, col - 1) == player) {
            if (col - 2 >= 0 && brd.atLocation(row, col - 2) == player) {
                if ((col - 3 >= 0 && brd.atLocation(row, col - 3) == Empty) && (row == 0 || (row - 1 >= 0 && brd.atLocation(row - 1, col - 3) != Empty))) {
                    if (player == Player2) {
                        return 4;
                    }
                    else {
                        return 3;
                    }
                }
            }
            else if ((col - 2 >= 0 && brd.atLocation(row, col - 2) == Empty) && (col - 3 >= 0 && brd.atLocation(row, col - 3) == player) && (row == 0 || (row - 1 >= 0 && brd.atLocation(row - 1, col -2) != Empty))) {
                if (player == Player2) {
                    return 4;
                }
                else {
                    return 3;
                }
            }
            else if ((col - 2 >= 0 && brd.atLocation(row, col - 2) == Empty) && (row == 0 || (row - 1 >= 0 && brd.atLocation(row - 1, col - 2) != Empty)))
                return 2;
        }
        else if (brd.atLocation(row, col - 1) == Empty && ((row - 1 >= 0 && brd.atLocation(row - 1, col - 1) != Empty) || row == 0)) {
            if ((col - 2 >= 0 && brd.atLocation(row, col - 2) == player) && (col - 3 >= 0 && brd.atLocation(row, col - 3) == player)) {
                if (player == Player2) {
                    return 4;
                }
                else {
                    return 3;
                }
            }
            else if ((col - 2 >= 0 && brd.atLocation(row, col - 2) == player)) {
                return 2;
            }
            else {
                return 1;
            }
        }
    return 0;
}
/* Assings a severity of 4 if AI can win, a 3 if the opponent has 3 in a row,
 vertically, a 2 for 2 in a row, and 1 for just one piece */
int VerticalSeverity(int row, int col, const Board& board, PieceType player) {
    Board brd = board;
    if (brd.atLocation(row, col) == player) {
        if (row + 1 < NUM_ROWS && brd.atLocation(row + 1, col) == player) {
            if (row + 2 < NUM_ROWS && brd.atLocation(row + 2, col) == player && (row + 3 < NUM_ROWS && brd.atLocation(row + 3, col) == Empty)) {
                if (player == Player2) {
                    return 4;
                }
                else {
                    return 3;
                }
            }
            else if ((row + 2 < NUM_ROWS && brd.atLocation(row + 2, col) == Empty))
                return 2;
        }
        else if ((row + 1 < NUM_ROWS && brd.atLocation(row + 1, col) == Empty)) {
            return 1;
        }
    }
    return 0;
}
/* Assings a severity of 4 if AI can win, a 3 if the opponent has 3 in a row,
 diagonally to the right, a 2 for 2 in a row, and 1 for just one piece */
int DiagonalRightSeverity(int row, int col, const Board& board, PieceType player) {
    Board brd = board;
        if (row + 1 < NUM_ROWS && col + 1 < NUM_COLS && brd.atLocation(row + 1, col + 1) == player) {
            if (row + 2 < NUM_ROWS && col + 2 < NUM_COLS && brd.atLocation(row + 2, col + 2) == player) {
                if ((row + 3 < NUM_ROWS && col + 3 < NUM_COLS && brd.atLocation(row + 3, col + 3) == Empty) && (brd.atLocation(row + 2, col + 3) != Empty)) {
                    if (player == Player2) {
                        return 4;
                    }
                    else {
                        return 3;
                    }
                }
            }
            else if ((col + 2 < NUM_COLS && row + 2 < NUM_ROWS && brd.atLocation(row + 2, col + 2) == Empty) && (row + 1 < NUM_ROWS && brd.atLocation(row + 1, col + 2) != Empty)) {
                if (col + 3 < NUM_COLS && row + 3 < NUM_ROWS && brd.atLocation(row + 3, col + 3) == player) {
                    if (player == Player2) {
                        return 4;
                    }
                    else {
                        return 3;
                    }
                }
                else if (col + 3 < NUM_COLS && row + 3 < NUM_ROWS && brd.atLocation(row + 3, col + 3) == Empty && brd.atLocation(row + 2, col + 2) == Empty) {
                    return 2;
                }
            }
        }
        else if ((col + 1 < NUM_COLS && row + 1 < NUM_ROWS && brd.atLocation(row + 1, col + 1) == Empty) && (brd.atLocation(row, col + 1) != Empty)) {
            if ((col + 2 < NUM_COLS && row + 2 < NUM_ROWS && brd.atLocation(row + 2, col + 2) == player) && (col + 3 < NUM_COLS && row + 3 < NUM_ROWS && brd.atLocation(row + 3, col + 3) == player)) {
                if (player == Player2) {
                    return 4;
                }
                else {
                    return 3;
                }
            }
            else if ((col + 2 < NUM_COLS && row + 2 < NUM_ROWS && brd.atLocation(row + 2, col + 2) == player) && (col + 3 < NUM_COLS && row + 3 < NUM_ROWS && brd.atLocation(row + 3, col + 3) == Empty)) {
                return 2;
            }
            else if ((col + 3 < NUM_COLS && row + 3 < NUM_ROWS && brd.atLocation(row + 3, col + 3) == Empty) && (col + 2 < NUM_COLS && row + 2 < NUM_ROWS && brd.atLocation(row + 2, col + 2) == Empty)){
                return 1;
            }
        }
    return 0;
}

int DiagonalLeftSeverity(int row, int col, const Board& board, PieceType player) {
    Board brd = board;
        if (row + 1 < NUM_ROWS && col - 1 >= 0 && brd.atLocation(row + 1, col - 1) == player) {
            if (row + 2 < NUM_ROWS && col - 2 >= 0 && brd.atLocation(row + 2, col - 2) == player) {
                if ((row + 3 < NUM_ROWS && col - 3 >= 0 && brd.atLocation(row + 3, col - 3) == Empty) && (brd.atLocation(row + 2, col - 3) != Empty)) {
                    if (player == Player2) {
                        return 4;
                    }
                    else {
                        return 3;
                    }
                }
            }
            else if ((row + 2 < NUM_ROWS && col - 2 >= 0 && brd.atLocation(row + 2, col - 2) == Empty) && (brd.atLocation(row + 1, col - 2) != Empty)) {
                if (col + 3 < NUM_COLS && row - 3 >= 0 && brd.atLocation(row + 3, col - 3) == player) {
                    if (player == Player2) {
                        return 4;
                    }
                    else {
                        return 3;
                    }
                }
                else if (col + 3 < NUM_COLS && row - 3 >= 0 && brd.atLocation(row + 3, col - 3) == Empty) {
                    return 2;
                }
            }
        }
        else if ((col - 1 >= 0 && row + 1 < NUM_ROWS && brd.atLocation(row + 1, col - 1) == Empty) && (brd.atLocation(row, col + 1) != Empty)) {
            if ((col - 2 >= 0 && row + 2 < NUM_ROWS && brd.atLocation(row + 2, col - 2) == player) && (col - 3 >= 0 && row + 3 < NUM_ROWS && brd.atLocation(row + 3, col - 3) == player)) {
                if (player == Player2) {
                    return 4;
                }
                else {
                    return 3;
                }
            }
            else if ((col - 2 >= 0 && row + 2 < NUM_ROWS && brd.atLocation(row + 2, col - 2) == player) && (col - 3 >= 0 && row + 3 < NUM_ROWS && brd.atLocation(row + 3, col - 3) == Empty)) {
                return 2;
            }
            else if ((col - 2 >= 0 && row + 2 < NUM_ROWS && brd.atLocation(row + 2, col - 2) == Empty) && (col - 3 >= 0 && row + 3 < NUM_ROWS && brd.atLocation(row + 3, col - 3) == Empty)){
                return 1;
            }
        }
    return 0;
}
/* Moves appropriately to the right if right move is chosen in the chose move
 function */
int RightMove(int row, int col, const Board& board, PieceType player, int severity) {
    Board brd = board;
        if (col + 1 < NUM_COLS && brd.atLocation(row, col + 1) == player) {
            if (col + 2 < NUM_COLS && brd.atLocation(row, col + 2) == player) {
                if ((col + 3 < NUM_COLS && brd.atLocation(row, col + 3) == Empty) && (row == 0 || (row - 1 >= 0 && brd.atLocation(row - 1, col + 3) != Empty))) {
                    if(severity == 4){
                        return col + 3;
                    }
                    else if (severity == 3) {
                        return col + 3;
                    }
                }
            }
            else if ((col + 2 < NUM_COLS && brd.atLocation(row, col + 2) == Empty) && (row == 0 || (row - 1 >= 0 && brd.atLocation(row - 1, col + 2) != Empty))) {
                if (col + 3 < NUM_COLS && brd.atLocation(row, col + 3) == player) {
                    if(severity == 4){
                        return col + 2;
                    }
                    else if (severity == 3) {
                        return col + 2;
                    }
                }
                else if (col + 3 < NUM_COLS && brd.atLocation(row, col + 3) == Empty){
                    if (severity == 2) {
                        return col + 2;
                    }
                }
            }
        }
        else if (col + 1 < NUM_COLS && brd.atLocation(row, col + 1) == Empty && (row == 0 || (row - 1 >= 0 && brd.atLocation(row - 1, col + 1) != Empty))) {
            if ((col + 2 < NUM_COLS && brd.atLocation(row, col + 2) == player) && (col + 3 < NUM_COLS && brd.atLocation(row, col + 3) == player)) {
                if (severity == 4){
                    return col + 1;
                }
                else if (severity == 3) {
                    return col + 1;
                }
            }
            else if ((col + 2 < NUM_COLS && brd.atLocation(row, col + 2) == player) && (col + 3 < NUM_COLS && brd.atLocation(row, col + 3) == Empty)) {
                if (severity == 2) {
                    return col + 1;
                }
            }
            else if ((col + 2 < NUM_COLS && brd.atLocation(row, col + 2) == Empty) && (col + 3 < NUM_COLS && brd.atLocation(row, col + 3) == Empty)) {
                if (severity == 1) {
                    return col + 1;
                }
            }
        }
    return -1;
}
/* Moves appropriately to the left if left move is chosen in the chose move
 function */
int LeftMove(int row, int col, const Board& board, PieceType player, int severity) {
    Board brd = board;
        if (col - 1 >= 0 && brd.atLocation(row, col - 1) == player) {
            if (col - 2 >= 0 && brd.atLocation(row, col - 2) == player) {
                if ((col - 3 >= 0 && brd.atLocation(row, col - 3) == Empty) && (row == 0 || (row - 1 >= 0 && brd.atLocation(row - 1, col - 3) != Empty))) {
                    if(severity == 4){
                        return col - 3;
                    }
                    else if (severity == 3) {
                        return col - 3;
                    }
                }
            }
            else if ((col - 2 >= 0 && brd.atLocation(row, col - 2) == Empty) && (row == 0 || (row - 1 >= 0 && brd.atLocation(row - 1, col - 2) != Empty))) {
                if (col - 3 >= 0 && brd.atLocation(row, col - 3) == player) {
                    if (severity == 4){
                        return col - 2;
                    }
                    else if (severity == 3) {
                        return col - 2;
                    }
                }
                else if (col - 3 >= 0 && brd.atLocation(row, col - 3) == Empty){
                    if (severity == 2) {
                        return col - 2;
                    }
                }
            }
        }
        else if (col - 1 >= 0 && brd.atLocation(row, col - 1) == Empty && (row == 0 || (row - 1 >= 0 && brd.atLocation(row - 1, col - 1) != Empty))) {
            if ((col - 2 >= 0 && brd.atLocation(row, col - 2) == player) && (col - 3 >= 0 && brd.atLocation(row, col - 3) == player)) {
                if (severity == 4) {
                    return col - 1;
                }
                else if (severity == 3) {
                    return col - 1;
                }
            }
            else if ((col - 2 >= 0 && brd.atLocation(row, col - 2) == player) && (col - 3 >= 0 && brd.atLocation(row, col - 3) == Empty)) {
                if (severity == 2) {
                    return col - 1;
                }
            }
            else if ((col - 2 >= 0 && brd.atLocation(row, col - 2) == Empty) && (col - 3 >= 0 && brd.atLocation(row, col - 3) == Empty)) {
                if (severity == 1) {
                    return col - 1;
                }
            }
        }
    return -1;
}
/* Moves appropriately vertically if veritcal move is chosen in the chose move
 function */
int VerticalMove(int row, int col, const Board& board, PieceType player, int severity) {
    Board brd = board;
    if (row + 1 < NUM_ROWS && brd.atLocation(row, col) == player) {
        if (row + 1 < NUM_ROWS && brd.atLocation(row + 1, col) == player) {
            if (row + 2 < NUM_ROWS && brd.atLocation(row + 2, col) == player) {
                if ((row + 3 < NUM_ROWS && brd.atLocation(row + 3, col) == Empty)) {
                    if(severity == 4){
                        return col;
                    }
                    else if (severity == 3) {
                        return col;
                    }
                }
            }
            else if ((row + 2 < NUM_ROWS && brd.atLocation(row + 2, col) == Empty)) {
                if (severity == 2) {
                    return col;
                }
            }
        }
        else if ((row + 1 < NUM_ROWS && brd.atLocation(row + 1, col) == Empty)) {
            if (severity == 1) {
                return col;
            }
        }
    }
    return -1;
}
/* Moves appropriately diagonally to the right if diagonal right move is chosen
 in the chose movefunction */
int DiagonalRightMove(int row, int col, const Board& board, PieceType player, int severity) {
    Board brd = board;
        if (row + 1 < NUM_ROWS && col + 1 < NUM_COLS && brd.atLocation(row + 1, col + 1) == player) {
            if (row + 2 < NUM_ROWS && col + 2 < NUM_COLS && brd.atLocation(row + 2, col + 2) == player) {
                if ((row + 3 < NUM_ROWS && col + 3 < NUM_COLS && brd.atLocation(row + 3, col + 3) == Empty) && (brd.atLocation(row + 2, col + 3) != Empty)) {
                    if(severity == 4){
                        return col + 3;
                    }
                    else if (severity == 3) {
                        return col + 3;
                    }
                }
            }
            else if ((row + 2 < NUM_ROWS && col + 2 < NUM_COLS && brd.atLocation(row + 2, col + 2) == Empty) && (brd.atLocation(row + 1, col + 2) != Empty)) {
                if (col + 3 < NUM_COLS && row + 3 && brd.atLocation(row + 3, col + 3) == player) {
                    if (severity == 4){
                        return col + 2;
                    }
                    else if (severity == 3) {
                        return col + 2;
                    }
                }
                else if (col + 3 < NUM_COLS && row + 3 && brd.atLocation(row + 3, col + 3) == player){
                    if (severity == 2) {
                        return col + 2;
                    }
                }
            }
        }
        else if ((col + 1 < NUM_COLS && row + 1 < NUM_ROWS && brd.atLocation(row + 1, col + 1) == Empty) && (brd.atLocation(row, col + 1) != Empty)) {
            if ((col + 2 < NUM_COLS && row + 2 < NUM_ROWS && brd.atLocation(row + 2, col + 2) == player) && (col + 3 < NUM_COLS && row + 3 < NUM_ROWS && brd.atLocation(row + 3, col + 3) == player)) {
                if (severity == 4){
                    return col + 1;
                }
                else if (severity == 3) {
                    return col + 1;
                }
            }
            else if ((col + 2 < NUM_COLS && row + 2 < NUM_ROWS && brd.atLocation(row + 2, col + 2) == player) && (col + 3 < NUM_COLS && row + 3 < NUM_ROWS && brd.atLocation(row + 3, col + 3) == Empty)) {
                if (severity == 2) {
                    return col + 1;
                }
            }
            else if ((col + 2 < NUM_COLS && row + 2 < NUM_ROWS && brd.atLocation(row + 2, col + 2) == Empty) && (col + 3 < NUM_COLS && row + 3 < NUM_ROWS && brd.atLocation(row + 3, col + 3) == Empty)) {
                if (severity == 1) {
                    return col + 1;
                }
            }
        }
    return -1;
}
/* Moves appropriately diagonally to the left if diagonal left move is chosen
 in the chose movefunction */
int DiagonalLeftMove(int row, int col, const Board& board, PieceType player, int severity) {
    Board brd = board;
    if (row + 1 < NUM_ROWS && col - 1 >= 0 && brd.atLocation(row + 1, col - 1) == player) {
        if (row + 1 < NUM_ROWS && col - 1 >= 0 && brd.atLocation(row + 1, col - 1) == player) {
            if (row + 2 < NUM_ROWS && col - 2 >= 0 && brd.atLocation(row + 2, col - 2) == player) {
                if ((row + 3 < NUM_ROWS && col - 3 >= 0 && brd.atLocation(row + 3, col - 3) == Empty) && (brd.atLocation(row + 2, col - 3) != Empty)) {
                    if (severity == 4){
                        return col - 3;
                    }
                    else if (severity == 3) {
                        return col - 3;
                    }
                }
            }
            else if ((row + 2 < NUM_ROWS && col - 2 >= 0 && brd.atLocation(row + 2, col - 2) == Empty) && (brd.atLocation(row + 1, col - 2) != Empty)) {
                if (col + 3 < NUM_COLS && row - 3 >= 0 && brd.atLocation(row + 3, col - 3) == player) {
                    if (severity == 4){
                        return col - 2;
                    }
                    else if (severity == 3) {
                        return col - 2;
                    }
                }
                else if ((col + 3 < NUM_COLS && row - 3 >= 0 && brd.atLocation(row + 3, col - 3) == Empty)) {
                    if (severity == 2) {
                        return col - 2;
                    }
                }
            }
        }
        else if ((col - 1 >= 0 && row + 1 < NUM_ROWS && brd.atLocation(row + 1, col - 1) == Empty) && (brd.atLocation(row, col + 1) != Empty)) {
            if ((col - 2 >= 0 && row + 2 < NUM_ROWS && brd.atLocation(row + 2, col - 2) == player) && (col - 3 >= 0 && row + 3 < NUM_ROWS && brd.atLocation(row + 3, col - 3) == player)) {
                if (severity == 4){
                    return col - 1;
                }
                else if (severity == 3) {
                    return col - 1;
                }
            }
            else if ((col - 2 >= 0 && row + 2 < NUM_ROWS && brd.atLocation(row + 2, col - 2) == player) && (col - 3 >= 0 && row + 3 < NUM_ROWS && brd.atLocation(row + 3, col - 3) == Empty)) {
                if (severity == 2) {
                    return col - 1;
                }
            }
            else if ((col - 2 >= 0 && row + 2 < NUM_ROWS && brd.atLocation(row + 2, col - 2) == Empty) && (col - 3 >= 0 && row + 3 < NUM_ROWS && brd.atLocation(row + 3, col - 3) == Empty) ){
                if (severity == 1) {
                    return col - 1;
                }
            }
        }
    }
    return -1;
}
// Choses which move function to use based on which severity is the greatest //
int ChooseMove(const Board& board) {
    Board brd = board;
    PieceType player;
    PieceType opponent;
    int dSevR = 0;
    int dSevL = 0;
    int dSevV = 0;
    int dSevDR = 0;
    int dSevDL = 0;
    int dSev = 0;
    int dR = 0;
    int dC = 0;
    //Move Type: 1.Right 2.Left 3.Vertical 4.Diagonal Right 5.Diagonal Left
    int moveTypeD = 0;
    int oSevR = 0;
    int oSevL = 0;
    int oSevV = 0;
    int oSevDR = 0;
    int oSevDL = 0;
    int oSev = 0;
    int oR = 0;
    int oC = 0;
    //Move Type: 1.Right 2.Left 3.Vertical 4.Diagonal Right 5.Diagonal Left
    int moveTypeO = 0;

    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            if (brd.atLocation(row, col) == Player1) {
                player = Player1;
                dSevR = RightSeverity(row, col, board, player);
                dSevL = LeftSeverity(row, col, board, player);
                dSevV = VerticalSeverity(row, col, board, player);
                dSevDR = DiagonalRightSeverity(row, col, board, player);
                dSevDL = DiagonalLeftSeverity(row, col, board, player);
                if (dSevR == fmax(dSevR, fmax(dSevL, fmax(dSevV, fmax(dSevDR, dSevDL)))) && dSevR > dSev) {
                    if (RightMove(row, col, board, player, dSevR) != -1) {
                        moveTypeD = 1;
                        dR = row;
                        dC = col;
                        dSev = dSevR;
                    }
                }
                else if (dSevL == fmax(dSevR, fmax(dSevL, fmax(dSevV, fmax(dSevDR, dSevDL)))) && dSevL > dSev) {
                    if (LeftMove(row, col, board, player, dSevL) != -1) {
                        moveTypeD = 2;
                        dR = row;
                        dC = col;
                        dSev = dSevL;
                    }
                }
                else if (dSevV == fmax(dSevR, fmax(dSevL, fmax(dSevV, fmax(dSevDR, dSevDL)))) && dSevV > dSev) {
                    if (VerticalMove(row, col, board, player, dSevV) != -1) {
                        moveTypeD = 3;
                        dR = row;
                        dC = col;
                        dSev = dSevV;
                    }
                }
                else if (dSevDR == fmax(dSevR, fmax(dSevL, fmax(dSevV, fmax(dSevDR, dSevDL)))) && dSevDR > dSev) {
                    if (DiagonalRightMove(row, col, board, player, dSevDR) != -1) {
                        moveTypeD = 4;
                        dR = row;
                        dC = col;
                        dSev = dSevDR;
                    }
                }
                else if (dSevDL == fmax(dSevR, fmax(dSevL, fmax(dSevV, fmax(dSevDR, dSevDL)))) && dSevDL > dSev) {
                    if (DiagonalLeftMove(row, col, board, player, dSevDL) != -1) {
                        moveTypeD = 5;
                        dR = row;
                        dC = col;
                        dSev = dSevDL;
                    }
                }
            }
            else if (brd.atLocation(row, col) == Player2) {
                player = Player2;
                oSevR = RightSeverity(row, col, board, player);
                oSevL = LeftSeverity(row, col, board, player);
                oSevV = VerticalSeverity(row, col, board, player);
                oSevDR = DiagonalRightSeverity(row, col, board, player);
                oSevDL = DiagonalLeftSeverity(row, col, board, player);
                if (oSevR == fmax(oSevR, fmax(oSevL, fmax(oSevV, fmax(oSevDR, oSevDL)))) && oSevR > oSev) {
                    if (RightMove(row, col, board, player, oSevR) != -1) {
                        moveTypeO = 1;
                        oR = row;
                        oC = col;
                        oSev = oSevR;
                    }
                }
                else if (oSevL == fmax(oSevR, fmax(oSevL, fmax(oSevV, fmax(oSevDR, oSevDL)))) && oSevL > oSev) {
                    if (LeftMove(row, col, board, player, oSevL) != -1) {
                        moveTypeO = 2;
                        oR = row;
                        oC = col;
                        oSev = oSevL;
                    }
                }
                else if (oSevV == fmax(oSevR, fmax(oSevL, fmax(oSevV, fmax(oSevDR, oSevDL)))) && oSevV > oSev) {
                    if (VerticalMove(row, col, board, player, oSevV) != -1) {
                        moveTypeO = 3;
                        oR = row;
                        oC = col;
                        oSev = oSevV;
                    }
                }
                else if (oSevDR == fmax(oSevR, fmax(oSevL, fmax(oSevV, fmax(oSevDR, oSevDL)))) && oSevDR > oSev) {
                    if (DiagonalRightMove(row, col, board, player, oSevDR) != -1) {
                        moveTypeO = 4;
                        oR = row;
                        oC = col;
                        oSev = oSevDR;
                    }
                }
                else if (oSevDL == fmax(oSevR, fmax(oSevL, fmax(oSevV, fmax(oSevDR, oSevDL)))) && oSevDL > oSev) {
                    if (DiagonalLeftMove(row, col, board, player, oSevDL) != -1) {
                        moveTypeO = 5;
                        oR = row;
                        oC = col;
                        oSev = oSevDL;
                    }
                }
            }
        }
    }
    dSevR = RightSeverity(dR, dC, board, Player1);
    dSevL = LeftSeverity(dR, dC, board, Player1);
    dSevV = VerticalSeverity(dR, dC, board, Player1);
    dSevDR = DiagonalRightSeverity(dR, dC, board, Player1);
    dSevDL = DiagonalLeftSeverity(dR, dC, board, Player1);
    oSevR = RightSeverity(oR, oC, board, Player2);
    oSevL = LeftSeverity(oR, oC, board, Player2);
    oSevV = VerticalSeverity(oR, oC, board, Player2);
    oSevDR = DiagonalRightSeverity(oR, oC, board, Player2);
    oSevDL = DiagonalLeftSeverity(oR, oC, board, Player2);
    if (dSev >= oSev) {
        player = Player1;
        opponent = Player2;
        if (moveTypeD == 1) {
            return RightMove(dR, dC, board, player, dSev);
        }
        else if (moveTypeD == 2) {
            return LeftMove(dR, dC, board, player, dSev);
        }
        else if (moveTypeD == 3) {
            return VerticalMove(dR, dC, board, player, dSev);
        }
        else if (moveTypeD == 4) {
            return DiagonalRightMove(dR, dC, board, player, dSev);
        }
        else if (moveTypeD == 5) {
            return DiagonalLeftMove(dR, dC, board, player, dSev);
        }
    }
    else if (dSev < oSev) {
        player = Player2;
        opponent = Player1;
        if (moveTypeO == 1) {
            return RightMove(oR, oC, board, player, oSev);
        }
        else if (moveTypeO == 2) {
            return LeftMove(oR, oC, board, player, oSev);
        }
        else if (moveTypeO == 3) {
            return VerticalMove(oR, oC, board, player, oSev);
        }
        else if (moveTypeO == 4) {
            return DiagonalRightMove(oR, oC, board, player, oSev);
        }
        else if (moveTypeO == 5) {
            return DiagonalLeftMove(oR, oC, board, player, oSev);
        }
    }
    int count = 0;
    int min = 10;
    int fin = 0;
    for (int j = 0; j < NUM_COLS; j++) {
        count = 0;
        for (int i = 0; i < NUM_ROWS; i++) {
            if (brd.atLocation(i, j) != Empty) {
                count++;
           }
        }
        if (count < min) {
            min = count;
            fin = j;
        }
    }
    return fin;
}
