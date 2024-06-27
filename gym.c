#include <stdio.h>

int coord_to_bitboard_index(char file, int rank) {
    // Validate input
    if (file < 'a' || file > 'h' || rank < 1 || rank > 8) {
        return -1; // Invalid input
    }

    // Calculate the file index (0 for 'a' to 7 for 'h')
    int file_index = file - 'a';

    // Calculate the rank index (0 for 8 to 7 for 1)
    int rank_index = 8 - rank;

    // Calculate the bitboard index
    int index = rank_index * 8 + file_index;

    return index;
}

void print_grid_with_indexes() {
    for (int rank = 8; rank >= 1; rank--) {
        for (char file = 'a'; file <= 'h'; file++) {
            int index = coord_to_bitboard_index(file, rank);
            printf("(%c%d, %2d)", file, rank, index);
            if (file != 'h') {
                printf(", ");
            }
        }
        printf("\n");
    }
}

void print_grid_coords() {
    for (int rank = 8; rank >= 1; rank--) {
        for (char file = 'a'; file <= 'h'; file++) {
            printf("(%c%d) ", file, rank);
        }
        printf("\n");
    }
}

void print_grid_indexes() {
    for (int rank = 8; rank >= 1; rank--) {
        for (char file = 'a'; file <= 'h'; file++) {
            int index = coord_to_bitboard_index(file, rank);
            printf("%2d ", index);
        }
        printf("\n");
    }
}



int main() {
    print_grid_with_indexes();
    print_grid_coords();
    print_grid_indexes();

    return 0;
}

