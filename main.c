#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define SET_BIT(board, row, col)    (board |= (1ULL << ((row) * 8 + (col))))
#define CLEAR_BIT(board, row, col)  (board &= ~(1ULL << ((row) * 8 + (col))))
#define GET_BIT(board, row, col)    ((board >> ((row) * 8 + (col))) & 1ULL)

typedef enum {
  WHITE_KING,
  WHITE_QUEEN,
  WHITE_PAWN,
  WHITE_KNIGHT,
  WHITE_BISHOP,
  WHITE_ROOK,
  BLACK_KING,
  BLACK_QUEEN,
  BLACK_PAWN,
  BLACK_KNIGHT,
  BLACK_BISHOP,
  BLACK_ROOK,
} PieceType;

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


uint64_t move_piece(uint64_t board, int row, int col, int nrow, int ncol) {
  SET_BIT(board, nrow, ncol);
  CLEAR_BIT(board, row, col);
  /*
  for (int i=0; i<8; i++) {
    for (int j=0; j<8; j++) {
      CLEAR_BIT(board, j, i);
      printf("%d %d\n", j, i);
      pboard(board);
    }
  }
  */
  return board;
}

int main() {
  // INIITIAL POSITIONS
  char* bps = "0000000011111111000000000000000000000000000000000000000000000000";
  char* brs = "1000000100000000000000000000000000000000000000000000000000000000";
  char* bns = "0100001000000000000000000000000000000000000000000000000000000000";
  char* bbs = "0010010000000000000000000000000000000000000000000000000000000000";
  char* bqs = "0000100000000000000000000000000000000000000000000000000000000000";
  char* bks = "0001000000000000000000000000000000000000000000000000000000000000";
  char* wps = "0000000000000000000000000000000000000000000000001111111100000000";
  char* wrs = "0000000000000000000000000000000000000000000000000000000010000001";
  char* wns = "0000000000000000000000000000000000000000000000000000000001000010";
  char* wbs = "0000000000000000000000000000000000000000000000000000000000100100";
  char* wqs = "0000000000000000000000000000000000000000000000000000000000001000";
  char* wks = "0000000000000000000000000000000000000000000000000000000000010000";

  uint64_t wpb = stoint64(wps); 
  uint64_t wrb = stoint64(wrs); 
  uint64_t wnb = stoint64(wns); 
  uint64_t wbb = stoint64(wbs); 
  uint64_t wqb = stoint64(wqs); 
  uint64_t wkb = stoint64(wks); 

  uint64_t bpb = stoint64(bps); 
  uint64_t brb = stoint64(brs); 
  uint64_t bnb = stoint64(bns); 
  uint64_t bbb = stoint64(bbs); 
  uint64_t bqb = stoint64(bqs); 
  uint64_t bkb = stoint64(bks); 

  uint64_t pieces[12] = {
    wkb, wqb, wpb, wnb, wbb, wrb,
    bkb, bqb, bpb, bnb, bbb, brb
  };

  // Initialize ncurses
    initscr();            // Start curses mode
    noecho();             // Disable echoing of characters
    keypad(stdscr, TRUE); // Enable function keys

    char buf[256];
    char command[256];
    int ch, idx = 0;

    while (1) {
        // Clear the screen
        clear();

        // Get and print the board string
        get_board_string(pieces, buf);
        printw("%s", buf); // Print the board
        refresh(); // Print it on to the real screen

        // Show input prompt
        mvprintw(LINES - 1, 0, "Enter move: ");
        refresh();

        // Get user input character by character
        idx = 0;
        while ((ch = getch()) != '\n') {
            if (ch == KEY_BACKSPACE || ch == 127) {
                if (idx > 0) {
                    idx--;
                    command[idx] = '\0';
                    mvprintw(LINES - 1, 12 + idx, " "); // Clear the character on the screen
                    move(LINES - 1, 12 + idx); // Move the cursor back
                }
            } else {
                command[idx++] = ch;
                command[idx] = '\0';
                mvprintw(LINES - 1, 12, "%s", command); // Show the input as it's being typed
            }
            refresh();
        }

        // Null-terminate the command
        command[idx] = '\0';

        printf("%s\n", command);
        // Exit condition
        if (strcmp(command, "exit") == 0) {
            break;
        }

        // Move the piece based on the command (this function should be implemented)
        if (strcmp(command, "w") == 0) {
            pieces[WHITE_KING] = move_piece(pieces[WHITE_KING], 0, 4, 4, 4);
        }
    }

    // End ncurses mode
    endwin();

    return 0;
}





