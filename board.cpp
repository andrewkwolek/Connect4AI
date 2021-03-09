#include "board.h"

Board::Board() {
    for (int row = 0; row < NUM_ROWS; row++){
        for (int col = 0; col < NUM_COLS; col++){
            data[row][col] = Empty;
        }
    }
    nextPlayer_to_move = Player1;
}

Board::Board(const string &fen) {
    for (int row = 0; row < NUM_ROWS; row++) {      //Creates blank board
        for (int col = 0; col < NUM_COLS; col++) {
            data[row][col] = Empty;
        }
    }
    int currRow = 0;
    int currCol = 0;
    
    for (int i = 0; i < fen.length(); i++) {        //Creates board as fen string
        if (fen[i] == PLAYER1_TOKEN) {
            if (currCol < NUM_COLS) {
                data[currRow][currCol] = Player1;
            }
            nextPlayer_to_move = Player1;
            currCol++;
        }
        else if (fen[i] ==  PLAYER2_TOKEN) {
            if (currCol < NUM_COLS) {
                data[currRow][currCol] = Player2;
            }
            nextPlayer_to_move = Player2;
            currCol++;
        }
        else if (fen[i] >= '1' && fen[i] <= '7') {
            currCol += fen[i] - '0';
        }
        else if (fen[i] == '/') {
            currRow++;
            currCol = 0;
        }
    }
}

void Board::printBoard_as_FENstring(ostream &os) const {
    for (int row = 0; row < NUM_ROWS; row++) {      //Prints board as fen string
        int num = 0;                                //by going through all elements of data
        for (int col = 0; col < NUM_COLS; col++) {
            if (data[row][col] ==  Player1) {
                if (num != 0){
                    os << num;
                    num = 0;
                }
                os << PLAYER1_TOKEN;
            }
            else if (data[row][col] == Player2) {
                if (num != 0){
                    os << num;
                    num = 0;
                }
                os << PLAYER2_TOKEN;
            }
            else if (data[row][col] == Empty) {
                num++;
            }
        }
        if (num != 0) {
            os << num;
        }
        if (row != NUM_ROWS - 1) {
            os << '/';
        }
    }
    if (nextPlayer_to_move ==  Player1) {
        os << ' ' << PLAYER1_TOKEN;
    }
    else {
        os << ' ' << PLAYER2_TOKEN;
    }
}

PieceType Board::atLocation(int row, int col) {
    return data[row][col];
}

void Board::prettyPrintBoard(ostream &os) const {
	os << endl;
    for (int row = NUM_ROWS - 1; row >= 0; --row)  {
        os << "     +---+---+---+---+---+---+---+"
           << endl
           << "    ";
        
        for (int col = 0; col < NUM_COLS; col++)   {
            os << " | " ;
            if ( data[row][col] == Player1)
                os <<  PLAYER1_TOKEN;
            else if (data[row][col] == Player2)
                os << PLAYER2_TOKEN;
            else
                os << EMPTY_TOKEN;
        }
        os << " |" << endl;
    }
    os << "     +---+---+---+---+---+---+---+" << endl
       <<"  col  1   2   3   4   5   6   7" << endl;
    return;
}

int Board::toMove() const {
    if (nextPlayer_to_move == Player1) {
        return 1;
    }
    else {
        return 2;
    }
}

Result Board::makeMove(int col) {
    if (col > NUM_COLS - 1 || col < 0) {//Checks for illegal move
        return IllegalMove;
    }
    int row = getFirstFreeRow(col);
    if (!inBounds(row, col)) {
        return IllegalMove;
    }
    data[row][col] = updateToMove();//Checks for win
    if (isWin(row, col)) {
        return Win;
    }
    if (isBoardFull()) { //Checks for draw
        return Draw;
    }
    return NoResult;
}

int Board::getFirstFreeRow(int col) const {
    for (int row = 0; row < NUM_ROWS; row++) {
        if (data[row][col] == Empty) {
            return row;
        }
    }
    return NUM_ROWS;
}

PieceType Board::updateToMove() {
    if (nextPlayer_to_move == Player1) {//Changes to player 2
        nextPlayer_to_move = Player2;
        return Player1;
    }
    if (nextPlayer_to_move == Player2) {//Changes to player 1
        nextPlayer_to_move = Player1;
        return Player2;
    }
    return Player1;
}

bool Board::isBoardFull() const {
    for (int col = 0; col < NUM_COLS; col++) {
        if (data[NUM_ROWS - 1][col] == Empty) {
            return false;
        }
    }
    return true;
}

bool Board::inBounds(int row, int col) const {
    if (row < NUM_ROWS && col < NUM_COLS && row >= 0 && col >= 0) {
        return true;
    }
    return false;
}

int Board::piecesInDirection(int row, int col, int dRow, int dCol) const {
    int count = 0;
    int row_check;
    int col_check;
    row_check = row + dRow;
    col_check = col + dCol;
    while (inBounds(row_check, col_check)){
        if (data[row][col] == data[row_check][col_check]){
            row_check+=dRow;
            col_check+=dCol;
            count++;
        }
        else{
            return count;
        }
    }
    return count;
}

bool Board::isWin(int row, int col) const {
    if ((piecesInDirection(row, col, 1, 0) + piecesInDirection(row, col, -1, 0)) >= 3) {
         return true;
    }
    else if ((piecesInDirection(row, col, 0, 1) + piecesInDirection(row, col, 0, -1)) >= 3) {
        return true;
    }
    else if ((piecesInDirection(row, col, 1, -1) + piecesInDirection(row, col, -1, 1)) >= 3) {
        return true;
    }
    else if ((piecesInDirection(row, col, 1, 1) + piecesInDirection(row, col, -1, -1)) >= 3) {
        return true;
    }
    return false;
}


