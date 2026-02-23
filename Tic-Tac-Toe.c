#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Tic-Tac-Toe.h"


int smartChoice(unsigned char * board, unsigned char player, bool* isAbort){
   
  /*   ''' Returns a smart choice using an AI algorithm
    ''' */

    int pos;
    int bestMove = 0, i;              // # initialize bestMove
    unsigned char dupBoard[9];
    signed char score, bestScore = SCHAR_MIN;
    srand(time(NULL));
    pos = (int)(rand() % 9);
    memcpy(dupBoard, board, sizeof(unsigned char) * 9);
    for (i = 0; i< 9; ++i){
        pos = (pos + 1) % 9;
        if (dupBoard[pos] != ' ') continue;
        //# Simulate the move
        dupBoard[pos] = player;


        //# Find score using Minimax algorithm
        score = minimax(dupBoard,        // # use board's copy
                        player,         // # maximize for Computer (O)
                        player == 'O'? 'X': 'O',       //  # minimize for Human (X)
                        1,               // # depth of search tree
                        false
                        ,isAbort);  //  # is the next move for O
        
        //# Undo the move for simulation
        dupBoard[pos] = ' ';
        
        //# Update bestScore if appropriate
        if (score > bestScore){
            bestScore = score;
            bestMove = pos;
        }
    }
    //# Return the best move
    return bestMove;
}

signed char minimax(unsigned char* board, unsigned char maxSymbol, unsigned char minSymbol, unsigned char depth, bool isMaximizing, bool* isAbort){
   /*  ''' Minimax algorithm for the recursion
    ''' */
    //# Terminal conditions for recursion
    signed char bestScore = isMaximizing? SCHAR_MIN: SCHAR_MAX , score;
    char position, value;
    if (isWinner(board, maxSymbol))
        return 10 - depth;
    if (isWinner(board, minSymbol))
        return depth - 10;
    if (isBoardFull(board) || *isAbort)
        return 0;
    //# You may use the isWinner and isBoardFull functions if you want
    
    //# Keep track of scores at this depth
    //# Go through all available positions
    for (position = 0; position < 9; ++position){
        if (board[position] != ' ')
            continue;
        ///# Simulate the appropriate move
        board[position] = isMaximizing?maxSymbol : minSymbol;
        
        //# Find the score for the move
        score = minimax(board, maxSymbol, minSymbol, depth+1, !isMaximizing, isAbort);
        if (isMaximizing? score> bestScore: score < bestScore) {
            bestScore = score;
        }
        
        //# Undo the move for simulation
        board[position] = ' '; // # Fill in all the missing pieces in this code segment
        // # Simulate the appropriate move
        // # Find the score for the move
        // # Undo the move for simulation
    }
    return bestScore;
    // Return max or min as per the level
    //return max(scores) if isMaximizing else min(scores)
    //# Fill in the return logic for recursion as per level
    
    //# Remove the following exception when you complete this function
}

unsigned char isWinner(unsigned char* board, unsigned char player){
    /* ''' Checks if Player has Won the game
    '''
    # Check for 3 valid marks denoting a Win */
    if ((board[0] == player) && (board[1] == player) && (board[2] == player)) //Top Row
      return 1;
    if ((board[3] == player) && (board[4] == player) && (board[5] == player)) //Middle Row
      return 2;
    if ((board[6] == player) && (board[7] == player) && (board[8] == player))  //Bottom Row
      return 3;
    if ((board[0] == player) && (board[3] == player) && (board[6] == player)) //Left Column
      return 4;
    if ((board[1] == player) && (board[4] == player) && (board[7] == player)) //Center Column
      return 5;
    if  ((board[2] == player) && (board[5] == player) && (board[8] == player)) //Right Column
      return 6;
    if ((board[0] == player) && (board[4] == player) && (board[8] == player)) //Diagonal
      return 7;
    if ((board[6] == player) && (board[4] == player) && (board[2] == player)) //Diagonal
      return 8;
    return 0;
}

bool isBoardFull(unsigned char *board) {
    /* ''' Checks if the Board is Full
    ''' */
    int i;
    for (i = 0; i < 9; ++i) {
        if(board[i] == ' ') return false;
    }
    return true;
}
