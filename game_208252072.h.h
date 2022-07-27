#include <stdbool.h>
#include <assert.h>
#include <string.h>
#ifndef GAME_H
#define GAME_H
#define MAXSIZE 10
#define N_GENERATIONS_DEFAULT 5

#define ALIVE 'O'
#define DEAD  '.'

// this is a declaration, not a definition,
// of the global variable board
// SIZE + 1 since each row is nul-terminated
struct game_state {
    char **board;
    int generations;
    int n_rows;
    int n_cols;
    unsigned **n_neighbors;

};

void clear();
void display(unsigned gen, struct game_state *gs);
void update(struct game_state *gs);
int load(struct game_state *gs, char const *filename);

#endif