#include "Piezas.h"
#include <vector>
#include <iostream>

using namespace std;

/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
  vector<vector<Piece>> board(BOARD_ROWS,vector<Piece>(BOARD_COLS, Blank)); 
  turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
  for(int i = 0; i < BOARD_ROWS; i++) {
        for(int j = 0; j < BOARD_COLS; j++) {
            board[i][j] = Blank;
        }
    }
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
  if(column < 0 || column >= BOARD_COLS) {
        return Invalid;
    }
    
    for(int i = 0; i < BOARD_ROWS; ++i) {
        if(board[i][column] == Blank) {
            board[i][column] = turn;
            turn = (turn == X) ? O : X;
            return board[i][column];
        }
    }
    
    return Blank;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
  if(row < 0 || row >= BOARD_ROWS || column < 0 || column >= BOARD_COLS) {
        return Invalid;
    }
    return board[row][column];
}

int Piezas::getMax(Piece piece) {
    int maxLength = 0;
    
    // Check horizontally
    for (int i = 0; i < BOARD_ROWS; ++i) {
        int count = 0;
        for (int j = 0; j < BOARD_COLS; ++j) {
            if (board[i][j] == piece) {
                count++;
                maxLength = max(maxLength, count);
            } else {
                count = 0;
            }
        }
    }

    // Check vertically
    for (int j = 0; j < BOARD_COLS; ++j) {
        int count = 0;
        for (int i = 0; i < BOARD_ROWS; ++i) {
            if (board[i][j] == piece) {
                count++;
                maxLength = max(maxLength, count);
            } else {
                count = 0; // reset count if the sequence breaks
            }
        }
    }

    return maxLength;
}



/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
  bool full = true;
    for(int i = 0; i < BOARD_ROWS; ++i) {
        for(int j = 0; j < BOARD_COLS; ++j) {
            if(board[i][j] == Blank) {
                full = false;
            }
        }
    }
    if(!full) {
        return Invalid;
    }

    int max_X = getMax(X);
    int max_O = getMax(O);

    if(max_X > max_O) {
        return X;
    } else if(max_O > max_X) {
        return O;
    } else {
        return Blank;
    }
}