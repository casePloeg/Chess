#include <stdint.h>

/*
U64 nort = C64(0x0101010101010100);
for (int sq=0; sq < 64; sq++, nort <<= 1)
   rayAttacks[sq][Nort] = nort;
*/

void lineAttackNorth() {
  uint64_t northattack = uint64_t 0x0101010101010100;
  // start at square a1, iterate to h8
  // starting attack line represents a2 a3 ... a8 
  // shift left 1 time --> b2 b3 ... b8
  // shift left 8 time --> a3 a4 ... a8
  for (int sq = 0; sq < 64; sq++, northattack <<= 1)
    rayAttacks[sq][NORTH] = northattack;
}

typedef enum { 
  NORTH,
  NORTH_EAST,
  EAST,
  SOUTH_EAST
  SOUTH,
  SOUTH_WEST,
  WEST,
  NORTH_WEST,
  DIRECTION_TYPE_COUNT,
} Direction;


// Function to perform bit scan forward using GCC built-in
int bit_scan_forward(uint64_t board) {
  if (board == 0) return -1; // Return -1 if no bits are set
    return __builtin_ctzll(board);
}



uint64_t get_positive_ray_attacks(uint64_t occupied, Direction dir, int square) {
  attacks = ray_attack[dir][square];
  blocker = attacks & occupied;
  if ( blocker ) {
    square = bitScanForward(blocker);
    // clear out all possible moves that come after the first hit
    attacks ^= rayAttacks[dir][square];
  }
  return attacks;
}
