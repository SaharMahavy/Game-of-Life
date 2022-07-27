#include "game.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// clear terminal screen
void clear()
{
    printf("\e[2J\e[H"); // magic!
}

// display board and current generation
void display(unsigned gen, struct game_state *gs)
{
    printf("Game generation %u\n", gen);
    for (unsigned i = 0; i < gs->n_rows; ++i) {
        puts(gs->board[i]);
    }
    fflush(stdout); // make sure it gets displayed
}

// returns true if load was successful
int load(struct game_state *gs, char const *filename)
{   
    if (gs == NULL || filename == NULL)
        return 2;
    FILE *fp = fopen(filename, "r");;
    if (!fp) {
        perror(__func__);
        printf("Cannot open '%s'!\n", filename);
        return 2; }
    char tav= '\0';
    int num = 0;
    fscanf(fp,"%c", &tav);
    while (tav >= '0' && tav <= '9'){
        num = num*10 + (tav - '0');
        fscanf(fp,"%c", &tav);}
    gs->n_rows = num;
    num = 0;
    fscanf(fp,"%c", &tav);
     while (tav >= '0' && tav <= '9'){
        num = num*10 + (tav - '0');
        fscanf(fp,"%c", &tav); }
    gs->n_cols = num+1;
    char **arr = malloc(gs->n_rows * sizeof(char*));
    if (arr == NULL){
        fclose(fp);
        return 2; }
    for (int i = 0; i < gs->n_rows; i++){
        arr[i] = malloc(gs->n_cols * sizeof(char));
        if (arr[i] == NULL){
            for (int j = i; j >= 0; j--){
                free(arr[j]); }
            fclose(fp);
            free(arr);
            return 2; } }
    unsigned **arr_n = malloc(gs->n_rows * sizeof(unsigned*));
    if (arr_n == NULL){
        fclose(fp);
        for (int i = 0; i < gs->n_rows; i++){
            free(arr[i]); }
            free(arr);
            free(arr_n);
            return 2; }
    for (int i = 0; i < gs->n_rows; i++){
        arr_n[i] = malloc((gs->n_cols - 1) * sizeof(unsigned));
        if (arr_n[i] == NULL){
            for (int j = i; j >= 0; j--){
                free(arr_n[j]); }
            free(arr_n);
            for (int m = 0; m < gs->n_rows; m++) {
                free(arr[m]); }
            free(arr);
            fclose(fp);
            return 2; } }
    gs->board = arr;
    gs->n_neighbors = arr_n;
    int r = 0;
    int c = 0;
    fscanf(fp,"%c", &tav);
    while(!feof(fp)){
        if (tav != ALIVE && tav != DEAD && tav != '\0' && tav != 10 && tav != EOF){
            fclose(fp);
            // fprintf(stderr, "now1...\n");
            return 1; }
        while (c < gs->n_cols -1)
        {
            // printf("tav = %c\n", tav);
            if (tav != ALIVE && tav != DEAD){
                fclose(fp);
                // fprintf(stderr, "now2...\n");
                return 1; }
            gs->board[r][c] = tav;
            c += 1; 
            fscanf(fp,"%c", &tav); }
        // printf("tav = %c\n", tav);
        if (tav != '\n' && tav != EOF) {
            fclose(fp);
            // fprintf(stderr, "now3...\n");
            return 1; }
        r += 1;
        // printf("%d\n", r);
        if ((int)tav == EOF){
            fclose(fp);
            if (r != gs->n_rows) {
                // fprintf(stderr, "now4...\n");
                return 1;}
            return 0; } 
        // printf("ok\n");
        if (r < gs->n_rows)
            gs->board[r][c] = '\0';
        c = 0;
        // printf("No\n");
        fscanf(fp,"%c", &tav);
        } 
        if (r != gs->n_rows) {
                // fprintf(stderr, "now5...\n");
                fclose(fp);
                return 1;}
            fclose(fp);
            return 0; } 