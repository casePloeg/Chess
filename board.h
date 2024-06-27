// board.h

#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

void pboard(uint64_t board);
void get_board_string(uint64_t pieces[], char *buf);
uint64_t stoint64(const char *s);
int identify_piece(uint64_t pieces[], int row, int col);
uint64_t occupancy(uint64_t pieces[]);

#endif

