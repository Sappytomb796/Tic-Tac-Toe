/**********************************************************
 * game.c
 * Author: Alice Michael
 **********************************************************/
#include "game.h"

int  initialize(struct state * board)
{
  if(!board)
    return 0;
  int i;
  for(i = 0; i <=9; i++)
    board->token[i] = i + '0';

  return 1;
}

int player(char check)
{
  if(check == 'X')
    return 1;
  else if(check == 'O')
    return 2;
  else
    return 0;
}

/* return 1 for player 1, return 2 for player 2 */
int  check_win(struct state * board)
{
  int i;

  if(board->token[0] == board->token[1] &
     board->token[0] == board->token[2])
    return player(board->token[0]);

  if(board->token[3] == board->token[4] &
     board->token[3] == board->token[5])
    return player(board->token[3]);  

  if(board->token[6] == board->token[7] &
     board->token[6] == board->token[8])
    return player(board->token[6]);

  if(board->token[0] == board->token[3] &
     board->token[0] == board->token[6])
    return player(board->token[0]);

  if(board->token[1] == board->token[4] &
     board->token[1] == board->token[7])
    return player(board->token[1]);

  if(board->token[2] == board->token[5] &
     board->token[2] == board->token[8])
    return player(board->token[2]);

  if(board->token[0] == board->token[4] &
     board->token[0] == board->token[8])
    return player(board->token[0]);

  if(board->token[2] == board->token[4] &
     board->token[2] == board->token[6])
    return player(board->token[2]);

  for(i=0; i <9; i++)
    if(board->token[i] != 'O' & board->token[i] != 'X')
      return 0;

  return 3;
}

void display(struct state * piece)
{
  printf("         |       | \n");
  printf("    %c    |   %c   |    %c     \n", 
	 piece->token[0], piece->token[1], piece->token[2]);
  printf("         |       |         \n");
  printf("---------+-------+---------\n");
  printf("         |       | \n");
  printf("    %c    |   %c   |    %c     \n", 
	 piece->token[3], piece->token[4], piece->token[5]);
  printf("         |       | \n");
  printf("---------+-------+---------\n");
  printf("         |       | \n");
  printf("    %c    |   %c   |    %c     \n", 
	 piece->token[6], piece->token[7], piece->token[8]);
  printf("         |       | \n");
}

int get_input(struct state * board, char input)
{
  int space;
  printf("What space would you like to use? ");
  scanf("%d", &space);
  if(check_input(board, input, space)){
    board->token[space] = input;
    return 1;
  }
  else
    return 0;
}

int  check_input(struct state * board, char input, int space)
{
  if(board->token[space] != 'X' && board->token[space] != 'O')
    return 1;
  else
    return 0;
}
