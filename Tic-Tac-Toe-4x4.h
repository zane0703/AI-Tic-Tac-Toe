#ifndef TicTacToe4x4_H
#define TicTacToe4x4_H
#ifdef __cplusplus
extern "C" {
#endif
signed char minimax4(unsigned char* board, unsigned char maxSymbol, unsigned char minSymbol,  char depth, bool isMaximizing, unsigned char depthLimit);
bool isWinner4(unsigned char* board, unsigned char player);
bool isBoardFull4(unsigned char *board);
int smartChoice4(unsigned char * board, unsigned char player, unsigned char depthLimit);
#ifdef __cplusplus
}
#endif
#endif
