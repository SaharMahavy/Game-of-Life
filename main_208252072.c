#include "game.h"
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define EXAMPLE_LOAF {  \
    "......",           \
    "..OO..",           \
    ".O..O.",           \
    "..O.O.",           \
    "...O..",           \
    "......"}

#define EXAMPLE_BEACON {\
    "......",           \
    ".OO...",           \
    ".OO...",           \
    "...OO.",           \
    "...OO.",           \
    "......"}

#define EXAMPLE_GLIDER {\
    "......",           \
    "...O..",           \
    ".O.O..",           \
    "..OO..",           \
    "......",           \
    "......"}

// try all 3 examples! 
// e.g. change EXAMPLE_LOAF TO EXAMPLE_BEACON
// and rebulid

void free_game_state(struct game_state *gs){
    // printf("starting free_game_state\n");
    int i;
    for (i = 0; i < gs->n_rows; i++) {
        // fprintf(stdout ,"free -> board[%d] -> %p\n", i, gs->board[i]);
        free(gs->board[i]); }
    for (i = 0; i < gs->n_rows; i++) {
        // fprintf(stdout ,"free -> n_neigbors[%d] -> %p\n", i, gs->n_neighbors[i]);
        free(gs->n_neighbors[i]); }
    free(gs->board);
    free(gs->n_neighbors);
}

int main(int argc, char *argv[])
{
    bool interactive = true;
    if (argc == 1) {
        printf("Usage: call program and supply a name of a file\n");
        return 1; }
    int num_gen = -1;
    if (argc == 3){
        if (strcmp(argv[2], "noninteractive") == 0){
            interactive = false; }
        else {num_gen = atoi(argv[2]);} }
    else if (argc == 4){
        if (strcmp(argv[2], "noninteractive") == 0){
            interactive = false;
            num_gen = atoi(argv[3]);}
        else if (strcmp(argv[3], "noninteractive") == 0){
            interactive = false;
            num_gen = atoi(argv[2]);}
            else { printf("Did you mean to insert \"noninteractive\" as an argument? please try again...\n");
            return 2;} }
    if (num_gen == -1) {
        num_gen = N_GENERATIONS_DEFAULT; }
    // struct game_state gs1 = {.board = NULL, .generations = num_gen, .n_rows = 0, .n_cols = 0, .n_neighbors = NULL};
    // struct game_state *gs = &gs1;
    struct game_state *gs = malloc(sizeof *gs);
    if (gs == NULL){
        fprintf(stderr,"pointer failed\n");
        return 1; }
    gs->board = NULL;
    gs->n_neighbors = NULL;
    gs->generations = num_gen;
    int load_file = load(gs, argv[1]);
    // fprintf(stdout, "%d...\n", load_file);
    if (load_file != 0){
        fprintf(stderr, "load failed...\n");
        if (load_file == 1)
            free_game_state(gs);
        free(gs);
        return 2; }
    int gen;
    for (gen = 1; gen <= num_gen; ++gen) {
        update(gs);
        if (interactive) {
            // display intermediate boards
            clear();
            display(gen, gs);
            sleep(1); // one second
        }
    }
    gen -= 1;
    if (!interactive) // display only final board
        display(gen, gs);
    free_game_state(gs);
    free(gs);
    return 0;
}
