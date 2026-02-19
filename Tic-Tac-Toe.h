#ifndef TicTacToe_H
#define TicTacToe_H
#ifdef __cplusplus
extern "C" {
#endif
signed char minimax(unsigned char* board, unsigned char maxSymbol, unsigned char minSymbol,  char depth, bool isMaximizing);
bool isWinner(unsigned char* board, unsigned char player);
bool isBoardFull(unsigned char *board);
int smartChoice(unsigned char * board, unsigned char player);
#ifdef __cplusplus
}
#endif
#endif
