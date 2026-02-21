#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "Tic-Tac-Toe-4x4.h"


int smartChoice4(unsigned char * board, unsigned char player, unsigned char depthLimit, int firstPos, bool* isAbort){
  /*   ''' Returns a smart choice using an AI algorithm
    ''' */            // # initialize bestMove
    unsigned char dupBoard[16];
    signed char score, bestScore = SCHAR_MAX;
    int i;
    unsigned char minSymbol = player == 'O'? 'X': 'O';
    memcpy(dupBoard, board, sizeof(unsigned char) * 16);
    dupBoard[firstPos] = player;
    if (isWinner4(dupBoard, player))
        return 9;
    if (isWinner4(dupBoard, minSymbol))
        return -9;
    if (isBoardFull4(dupBoard)|| *isAbort)
        return 0;
    for (i = 0; i< 16; ++i){
        if (dupBoard[i] != ' ') continue;
        //# Simulate the move
        dupBoard[i] = minSymbol;
        //# Find score using Minimax algorithm
        score = minimax4(dupBoard,
                        player,        // # use board's copy
                        minSymbol,         // # maximize for Computer (O)       //  # minimize for Human (X)
                        2,               // # depth of search tree
                        true, //  # is the next move for O
                        depthLimit,
                        isAbort);
        
        //# Undo the move for simulation
        dupBoard[i] = ' ';
        
        //# Update bestScore if appropriate
        if (score < bestScore){
            bestScore = score;
        }
    }
    //# Return the best move
    return bestScore;
}

signed char minimax4(unsigned char* board, unsigned char maxSymbol, unsigned char minSymbol,  char depth, bool isMaximizing, unsigned char depthLimit, bool* isAbort){
   /*  ''' Minimax algorithm for the recursion
    ''' */
    //# Terminal conditions for recursion
    signed char bestScore = isMaximizing? SCHAR_MIN: SCHAR_MAX , score;
    char position, value;
    if (isWinner4(board, maxSymbol))
        return 10 - depth;
    if (isWinner4(board, minSymbol))
        return depth - 10;
    if (isBoardFull4(board) || depth >= depthLimit|| *isAbort)
        return 0;
    //# You may use the isWinner and isBoardFull functions if you want
    
    //# Keep track of scores at this depth
    //# Go through all available positions
    for (position = 0; position < 16; ++position){
        if (board[position] != ' ')
            continue;
        
        ///# Simulate the appropriate move
        board[position] = isMaximizing?maxSymbol : minSymbol;
        
        //# Find the score for the move
        score = minimax4(board, maxSymbol, minSymbol, depth+1, !isMaximizing, depthLimit, isAbort);
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

bool isWinner4(unsigned char* board, unsigned char player){
    /* ''' Checks if Player has Won the game
    '''
    
    # Check for 3 valid marks denoting a Win */
    return (((board[0] == player) && (board[1] == player) && ( board[2] == player) && ( board[3] == player)) || //or # Top Row
           ((board[4] == player) && ( board[5] == player) && ( board[6] == player) && ( board[7] == player)) ||//or # Middle Top Row
           ((board[8] == player) && ( board[9] == player) && ( board[10] == player) && ( board[11] == player)) ||//or # Middle Bottom Row
           ((board[12] == player) && ( board[13]  == player) && ( board[14] == player) && ( board[15] == player)) ||//or # Bottom Row
           ((board[0] == player) && ( board[4] == player) && ( board[8] == player) && ( board[12] == player)) ||//or # Left Column
           ((board[1] == player) && ( board[5] == player) && ( board[9]  == player) && ( board[13] == player)) ||//or # Center left Column
           ((board[2] == player) && ( board[6] == player) && ( board[10]  == player) && ( board[14] == player)) ||//or # Center right Column
           ((board[3] == player) && ( board[7]  == player) && ( board[11] == player) && ( board[15] == player))||//or # Right Column
           ((board[0] == player) && ( board[5] == player) && ( board[10] == player) && ( board[15] == player))||//or # Diagonal
           ((board[3] == player) && ( board[6] == player) && ( board[9] == player) && ( board[12] == player)));   //# Diagonal  
}

bool isBoardFull4(unsigned char *board) {
    /* ''' Checks if the Board is Full
    ''' */
    int i;
    for (i = 0; i < 16; ++i) {
        if  (board[i] == ' ') return false;
    }
    return true;
}
