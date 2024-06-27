#include "board.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <ncurses.h>

#include "board.h"
#include "common.h"

// print the binary representation of a 64 bit board
void pboard(uint64_t board) {
  char buf[65];
  uint64_t mask = 1; 
  int i = 63;
  while (i >= 0) {
    buf[i] = (board & mask) + '0';
    board = board >> 1;
    i -= 1;
  }
  buf[64] = '\0';
  printf("%s\n",buf);
  refresh();
}

void pallboards(uint64_t boards[]) {
  for (int i=0; i<PIECE_TYPE_COUNT; i++) {
    pboard(boards[i]);
  }
}

void get_board_string(uint64_t pieces[], char *buf) {
    char board[8][8];
    // Initialize board with empty squares
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = '.';
        }
    }
    // Place pieces on the board based on the bitboards
    for (int pt = 0; pt < 12; pt++) {
      for (int i = 0; i < 64; ++i) {
        int row = 7 - (i / 8);
        int col = i % 8;
        switch (pt) {
          case WHITE_KING:
            if (pieces[pt] & (1ULL << i)) board[row][col] = 'K';
            break;
          case WHITE_QUEEN:
            if (pieces[pt] & (1ULL << i)) board[row][col] = 'Q';
            break;
          case WHITE_PAWN:
            if (pieces[pt] & (1ULL << i)) board[row][col] = 'P';
            break;
          case WHITE_KNIGHT:
            if (pieces[pt] & (1ULL << i)) board[row][col] = 'N';
            break;
          case WHITE_BISHOP:
            if (pieces[pt] & (1ULL << i)) board[row][col] = 'B';
            break;
          case WHITE_ROOK:
            if (pieces[pt] & (1ULL << i)) board[row][col] = 'R';
            break;
          case BLACK_KING:
            if (pieces[pt] & (1ULL << i)) board[row][col] = 'k';
            break;
          case BLACK_QUEEN:
            if (pieces[pt] & (1ULL << i)) board[row][col] = 'q';
            break;
          case BLACK_PAWN:
            if (pieces[pt] & (1ULL << i)) board[row][col] = 'p';
            break;
          case BLACK_KNIGHT:
            if (pieces[pt] & (1ULL << i)) board[row][col] = 'n';
            break;
          case BLACK_BISHOP:
            if (pieces[pt] & (1ULL << i)) board[row][col] = 'b';
            break;
          case BLACK_ROOK:
            if ((pieces[pt] & (1ULL << i)) != 0) {
              board[row][col] = 'r';
            }
            break;
          default:
            break;
        }
      }
    }
    
    int pos = 0;
    pos += sprintf(&buf[pos], "%c ", board[0][0]);
    // Print the board
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            buf += sprintf(buf, "%c ", board[i][j]);
        }
        buf[0] = '\n';
        buf++;
    }
}

// convert a string representation for a bit board
// to the int64 version
uint64_t stoint64(const char *s) {
  int exp = 0;
  uint64_t val = 0;
  for (int i = 63; i >= 0; i -= 1) {
    // convert ascii value to int value
    val += (s[i] - '0') * pow(2,exp);
    exp += 1;
  }
  return val;
}

// Function to identify the piece at the given position
int identify_piece(uint64_t pieces[], int row, int col) {
    for (int i = 0; i < PIECE_TYPE_COUNT; i++) {
        if (GET_BIT(pieces[i], row, col)) {
            return i;
        }
    }
    return -1; // No piece found
}

uint64_t occupancy(uint64_t pieces[]) {
  uint64_t oc = 0;
  for (int i=0; i<PIECE_TYPE_COUNT; i++) {
    oc |= pieces[i]; 
  }
  return oc;
}
