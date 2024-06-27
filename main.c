#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <assert.h>

#include "common.h"
#include "board.h"
#include "move.h"

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

    /*
    // Initialize ncurses
    initscr();            // Start curses mode
    noecho();             // Disable echoing of characters
    keypad(stdscr, TRUE); // Enable function keys
    */

    char buf[256];
    char command[256];
    int ch, idx = 0;

    while (1) {
        // Clear the screen
        clear();

        // Get and print the board string
        get_board_string(pieces, buf);
        printf("%s", buf); // Print the board
        pboard(occupancy(pieces));
        //refresh(); // Print it on to the real screen

        // Show input prompt
        //mvprintw(LINES - 1, 0, "Enter move: ");
        //refresh();

        // Get user input character by character
        idx = 0;

        fgets(command, sizeof(command), stdin);
        // Null-terminate the command
        command[strcspn(command, "\n")] = '\0';
        // Exit condition
        if (strcmp(command, "exit") == 0) {
            break;
        }
        
        move_command(pieces, command);
    }

    // End ncurses mode
    //endwin();

    return 0;
}

