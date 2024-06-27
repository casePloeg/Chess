// common.h

#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

#define SET_BIT(board, row, col)    (board |= (1ULL << (((7 - (row)) * 8) + (7 - (col)))))
#define CLEAR_BIT(board, row, col)  (board &= ~(1ULL << (((7 - (row)) * 8) + (7 - (col)))))
#define GET_BIT(board, row, col)    ((board >> (((7 - (row)) * 8) + (7 - (col)))) & 1ULL)


typedef enum {
  WHITE_KING,
  WHITE_QUEEN,
  WHITE_PAWN, // 2
  WHITE_KNIGHT,
  WHITE_BISHOP,
  WHITE_ROOK,
  BLACK_KING,
  BLACK_QUEEN,
  BLACK_PAWN, // 8
  BLACK_KNIGHT,
  BLACK_BISHOP,
  BLACK_ROOK,
  PIECE_TYPE_COUNT, // 12
} PieceType;

#endif

