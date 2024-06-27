https://www.chessprogramming.org/

- curses is hard to work with right now, prefer a simple print to stdout style app for now


BITBOARDS
- keep a bitboard to keep track of location of each piece
- OR together all piece boards to calculate an occupancy board 

- bitboards are fast because of SIMD instructions --> Single Instruction, Multiple Data
  - bitboards can operate on all squares in parallel using bitwise instructions. 
  - operations like generating moves can be done on a per square basis in parallel?
- bit operations are composed of atomic patterns
  - bitScanForward
  - rayAttack
  - need to build up a libary of primitives

  - operations rely on using an index of pre-computed bitboards that represent various useful patterns
    - patterns represent specific things under a specific context, context could be current square + type of piece, board state, etc.

- bitboard index to coord(square) is bijective (1:1) , but can be formatted in many ways
 - https://www.chessprogramming.org/Square_Mapping_Considerations
- xor is used to clear some bits
