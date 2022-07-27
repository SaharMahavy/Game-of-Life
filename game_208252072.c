#include "game.h"

/* this function is not declared in game.h since it is
   internal to game.c; it is even defined as static -- 
   so the linker won't allow using it outside of game.c */
static unsigned count_neighbors(unsigned i, unsigned j,struct game_state *gs)
{
    int neighbors = 0;
    for (int r = -1; r < 2; r++) {
         for (int c = -1; c < 2; c++) {
             if (r == 0 && c == 0)
                continue;
             if ((gs->board[(r + i + gs->n_rows ) % gs->n_rows][(c + j + gs->n_cols ) % gs->n_cols] == ALIVE))
                neighbors += 1;
         } }
    return neighbors; 
}

void update(struct game_state *gs)
{

    for (unsigned i = 0; i < gs->n_rows; ++i) {
        for (unsigned j = 0; j < gs->n_cols-1; ++j) {
            gs->n_neighbors[i][j] = count_neighbors(i, j, gs);
        }
    }

    for (unsigned i = 0; i < gs->n_rows; ++i) {
        for (unsigned j = 0; j < gs->n_cols; ++j) {
            unsigned nn = gs->n_neighbors[i][j];
            if (nn < 2 || nn > 3)
                gs->board[i][j] = DEAD;
            else if (nn == 3)
                gs->board[i][j] = ALIVE;
            // when nn == 2, the previous value is retained
        }
    }
}
