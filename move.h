// move.h

#ifndef MOVE_H
#define MOVE_H

#include <stdint.h>


void move_command(uint64_t pieces[], const char* command);
void parse_position(const char* pos, int* row, int* col);
uint64_t move_piece(uint64_t board, int row, int col, int nrow, int ncol);

#endif

