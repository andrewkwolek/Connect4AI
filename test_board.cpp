#include<iostream>
#include "board.h"

using namespace std;

// Test suite for the Board class
// We highly encourage that you implement these functions
// using your test cases for each function to make sure 
// that your Board functions comply RMEs.

void test_default_Constructor();
void test_fenString_Constructor();
void test_printBoard_as_FENstring();
void test_toMove();
void test_makeMove();
void test_getFirstFreeRow();
void test_updateToMove();
void test_isBoardFull();
void test_inBounds();
void test_piecesInDirection();
void test_isWin();

int main() {
    test_default_Constructor();
	return 0;
}

// Sample test case for the default constructor
void test_default_Constructor() {
   cout << "Testing default constructor" << endl;
   Board board;
   board.prettyPrintBoard(cout);
}
