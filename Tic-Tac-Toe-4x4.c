#include <limits.h>
#include <stdbool.h>
#include <string.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

signed char minimax(unsigned char* board, unsigned char maxSymbol, unsigned char minSymbol, char depth, bool isMaximizing, unsigned char depthLimit);
unsigned char  EMSCRIPTEN_KEEPALIVE isWinner(unsigned char* board, unsigned char player);
bool EMSCRIPTEN_KEEPALIVE isBoardFull(unsigned char *board);
extern double random2(void);


int EMSCRIPTEN_KEEPALIVE smartChoice(unsigned char * board, unsigned char player, unsigned char depthLimit){
  /*   ''' Returns a smart choice using an AI algorithm
    ''' */
    int pos = (int)(random2() * 9);
    int bestMove = 0;              // # initialize bestMove
    unsigned char dupBoard[16];
    signed char score, bestScore = SCHAR_MIN;
    int i;
    memcpy(dupBoard, board, sizeof(unsigned char) * 16);
    for (i = 0; i< 16; ++i){
        pos = (pos + 1) % 16;
        if (dupBoard[pos] != ' ') continue;
        //# Simulate the move
        dupBoard[pos] = player;


        //# Find score using Minimax algorithm
        score = minimax(dupBoard,        // # use board's copy
                        player,         // # maximize for Computer (O)
                        player == 'O'? 'X': 'O',       //  # minimize for Human (X)
                        1,               // # depth of search tree
                        false, //  # is the next move for O
                        depthLimit); 
        
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

signed char minimax(unsigned char* board, unsigned char maxSymbol, unsigned char minSymbol,  char depth, bool isMaximizing, unsigned char depthLimit){
   /*  ''' Minimax algorithm for the recursion
    ''' */
    //# Terminal conditions for recursion
    signed char bestScore = isMaximizing? SCHAR_MIN: SCHAR_MAX , score;
    char position, value;
    if (isWinner(board, maxSymbol))
        return 10 - depth;
    if (isWinner(board, minSymbol))
        return depth - 10;
    if (isBoardFull(board) || depth >= depthLimit)
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
        score = minimax(board, maxSymbol, minSymbol, depth+1, !isMaximizing, depthLimit);
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
    if ((board[0] == player) && (board[1] == player) && ( board[2] == player) && ( board[3] == player)) //Top Row
      return 1;
    if ((board[4] == player) && ( board[5] == player) && ( board[6] == player) && ( board[7] == player)) //Middle Top Row
      return 2;
    if ((board[8] == player) && ( board[9] == player) && ( board[10] == player) && ( board[11] == player)) //Middle Bottom Row
      return 3;
    if ((board[12] == player) && ( board[13]  == player) && ( board[14] == player) && ( board[15] == player)) //Bottom Row
      return 4;
    if ((board[0] == player) && ( board[4] == player) && ( board[8] == player) && ( board[12] == player)) //Left Column
      return 5;
    if ((board[1] == player) && ( board[5] == player) && ( board[9]  == player) && ( board[13] == player)) //Center left Column
      return 6;
    if ((board[2] == player) && ( board[6] == player) && ( board[10]  == player) && ( board[14] == player)) //Center right Column
      return 7;
    if ((board[3] == player) && ( board[7]  == player) && ( board[11] == player) && ( board[15] == player)) //Right Column
      return 8;
    if ((board[0] == player) && ( board[5] == player) && ( board[10] == player) && ( board[15] == player)) //Diagonal
      return 9;
    if ((board[3] == player) && ( board[6] == player) && ( board[9] == player) && ( board[12] == player))   //Diagonal
      return 10;
    return 0;
}

bool isBoardFull(unsigned char *board) {
    /* ''' Checks if the Board is Full
    ''' */
    int i;
    for (i = 0; i < 16; ++i) {
        if  (board[i] == ' ') return false;
    }
    return true;
}