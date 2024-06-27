#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "move.h"
#include "board.h"
#include "common.h"

uint64_t move_piece(uint64_t board, int row, int col, int nrow, int ncol) {
  SET_BIT(board, nrow, ncol);
  CLEAR_BIT(board, row, col);
  return board;
}

// Function to convert algebraic notation to board indices
void parse_position(const char* pos, int* row, int* col) {
    *col = pos[0] - 'a';
    *row = 7 - (pos[1] - '1');
}

// Main move function
void move_command(uint64_t pieces[], const char* command) {
    // Example command: "e2e4" or "Ne2e4"
    int src_row, src_col, dst_row, dst_col;
    int piece_type;
    
    if (strlen(command) == 5) { // e.g., "Ne2e4"
        switch (command[0]) {
            case 'N': piece_type = WHITE_KNIGHT; break;
            case 'B': piece_type = WHITE_BISHOP; break;
            case 'R': piece_type = WHITE_ROOK; break;
            case 'Q': piece_type = WHITE_QUEEN; break;
            case 'K': piece_type = WHITE_KING; break;
            default: piece_type = WHITE_PAWN; // Assume pawn if no piece is specified
        }
        parse_position(command + 1, &src_row, &src_col);
        parse_position(command + 3, &dst_row, &dst_col);
    } else if (strlen(command) == 4) { // e.g., "e2e4"
        piece_type = WHITE_PAWN; // Assume pawn if no piece is specified
        parse_position(command, &src_row, &src_col);
        parse_position(command + 2, &dst_row, &dst_col);
    } else {
        printf("Invalid command\n");
        return;
    }
    // Identify the piece at the source position
    int identified_piece = identify_piece(pieces, src_row, src_col);
    if (identified_piece == -1) {
        printf("No piece at the source position\n");
        return;
    }
    // Check if the identified piece matches the expected piece type
    if (identified_piece != piece_type && identified_piece != piece_type + 6) {
        printf("Incorrect piece at the source position\n");
        return;
    }
    // Move the piece
    pieces[identified_piece] = move_piece(pieces[identified_piece], src_row, src_col, dst_row, dst_col);
}
