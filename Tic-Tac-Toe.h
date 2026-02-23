#ifndef TicTacToe_H
#define TicTacToe_H
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif
signed char minimax(unsigned char* board, unsigned char maxSymbol, unsigned char minSymbol, unsigned char depth, bool isMaximizing, bool* isAbort);
unsigned char isWinner(unsigned char* board, unsigned char player);
bool isBoardFull(unsigned char *board);
int smartChoice(unsigned char * board, unsigned char player, bool* isAbort);
#ifdef __cplusplus
}
#endif
#endif
