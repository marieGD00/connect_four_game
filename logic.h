#ifndef LOGIC_H
#define LOGIC_H

#include "board.h"


enum turn {
    BLACK_NEXT,
    WHITE_NEXT
};

typedef enum turn turn;


enum outcome {
    BLACK_WIN,
    WHITE_WIN,
    DRAW,
    IN_PROGRESS
};

typedef enum outcome outcome;


enum direction {
    CW, CCW
};

typedef enum direction direction;


struct game {
    unsigned int run;
    board* b;
    turn next;
};

typedef struct game game;


game* new_game(unsigned int run, unsigned int width, unsigned int height,
               enum type type);

int full_row_number(game* g,unsigned int col);
int helper_row(game* g,int j, int i, cell compare_cell);
int helper_column(game* g, int j, int i, cell compare_cell);
int helper_diagonal_down(game* g, int j, int i, cell compare_cell);
int helper_diagonal_up(game* g, int j, int i,cell compare_cell);

void game_free(game* g);
cell drop_right_character(game* g);
int drop_piece(game* g, unsigned int col);
void gravity(board* b);
void twist(game* g, direction d);
outcome horizontal_win(game* g);
outcome vertical_win(game* g);
outcome diagonal_down_win(game* g);
outcome diagonal_up_win(game* g);
outcome game_outcome(game* g);

#endif /* LOGIC_H */
