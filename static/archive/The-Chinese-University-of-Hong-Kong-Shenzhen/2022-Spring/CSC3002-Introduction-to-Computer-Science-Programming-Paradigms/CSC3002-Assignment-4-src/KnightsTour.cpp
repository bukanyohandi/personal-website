/*
 * File: KnightsTour.cpp
 * ---------------------
 * This program find a knight's tour on an N x M chessboard.
 */

#include "KnightsTour.h"

/*
 * Function: solveKnightsTour
 * Usage: solveKnightsTour(n, m);
 * ------------------------------
 * Solves the knight's tour problem for a n x m chessboard.
 */

void solveKnightsTour(int n, int m) {
   Grid<int> board(n, m);
   if (findKnightsTour(board, 0, 0, 1)) {
      displayBoard(board);
   } else {
      cout << "No tour exists for this board." << endl;
   }
}

/*
 * Function: displayBoard
 * Usage: displayBoard(board);
 * ---------------------------
 * Displays each of the squares in the board along with its sequence
 * number in the tour.
 */

void displayBoard(Grid<int> & board) {
   for (int i = board.numRows() - 1; i >= 0; i--) {
      for (int j = 0; j < board.numCols(); j++) {
         cout << " " << setw(2) << board[i][j];
      }
      cout << endl;
   }
}

const int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
const int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

bool findKnightsTour(Grid<int> & board, int row, int col, int seq){
    //    * 1. The position is off the board.
    if(row < 0 || row >= board.numRows() || col < 0 || col >= board.numCols()){
        return false;
    }

    //    * 2. The position has been previously visited.
    if(board[row][col] != 0){
        return false;
    }

    //    * 3. The tour is complete.
    if(seq == board.size()){
        board[row][col] = seq;
        return true;
    }

    for(int idx = 0; idx < 8; ++idx){
        board[row][col] = seq;
        if(findKnightsTour(board, row + dx[idx], col + dy[idx], seq + 1) == true){
            return true;
        }
        board[row][col] = 0;
    }
    return false;
}
