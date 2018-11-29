/**********************************************************
 * game.h
 * Author: Alice Michael
 * Description: 
 *      Tic-Tac-Toe header file.  This is where all the 
 *      functions for the game logic are stored.  This
 *      makes seperating the game logic and the networking
 *      logic a little easier.
 * Convention note: with Int return types, 0 identifies 
 *                  failure, and anything greater than 0
 *                  notifies success.  Any extra info 
 *                  on a return meaning will be noted in
 *                  game.c with the appropriate function.
 **********************************************************/

/* Includes */
#include <stdio.h>
#include <stdlib.h>

/* This is to allow a state to be passed between everything 
 * and hold the place of the 3 tokens consistently.
 */
struct state{
  char token[9];
};


int  initialize(struct state * board);
void display(struct state * board);

int get_input(struct state * board, char input);

int  check_board(struct state validate);
int  check_win(struct state * board);
int  check_input(struct state * board, char input, int space);
