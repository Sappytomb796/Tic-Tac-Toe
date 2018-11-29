#include "game.h"

/* TODO: Lawlz, emulate pass by reff on the board dummy... */

int main()
{
  struct state * board = (struct state *)malloc(sizeof(struct state));
  int turn;
  int valid;
  int winner = 0;
  char input;

  initialize(&(*board));

  for(turn = 1; !winner; turn++){
    display(board);
    if(turn%2 == 1){
      printf("Player 1 it is your turn\n");
      input = 'X'; }
    else{
      printf("Player 2 it is your turn\n");
      input = 'O'; }
   
    valid = get_input(&(*board), input);
    while(!valid){
      printf("That space is already taken, please try again\n");
      valid = get_input(&(*board), input);
    }

    winner = check_win(&(*board));
  }

  display(board);
  if(winner == 3){
    printf("Game over; draw\n");
    printf("Thank you for playing.\nEXITING\n\n");}
  else{
    printf("Congrats Player %d, you win!", winner);
    printf("Thank you for playing.\nEXITING\n\n");}


  if(board)
    free(board);
  return 0;
}
