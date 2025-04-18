#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main()
{
   char winner = ' ';
   char response = ' ';
   srand(time(0));  //creates a seed based on current time

   do
   {
      winner = ' ';
      response = ' ';
      resetBoard();    // Initialize the board

      printf("Welcome to Tic-Tac-Toe!\n");
      printf("Player is 'X' and Computer is 'O'.\n\n");

      while(winner == ' ' && checkFreeSpaces() != 0)
      {
         printBoard();

         playerMove();
         winner = checkWinner();   // Check if player wins
         if(winner != ' ' || checkFreeSpaces() == 0)
         {
            break;
         }

         computerMove();  // Computer's turn
         winner = checkWinner();  // Check if computer wins
         if(winner != ' ' || checkFreeSpaces() == 0)
         {
            break;
         }
      }

      printBoard();
      printWinner(winner);

      printf("\nWould you like to play again? (Y/N): ");
      scanf(" %c", &response);   // `scanf(" %c")` skips trailing whitespace

      response = toupper(response);

   } while (response == 'Y');

   printf("Thanks for playing!");
   return 0;
}



void resetBoard()
{
   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         board[i][j] = ' ';  // Initialize all cells to empty
      }
   }
}

void printBoard()
{
   printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);

   printf("\n---|---|---\n");

   printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);

   printf("\n---|---|---\n");

   printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);

   printf("\n");
}

int checkFreeSpaces()
{
   int freeSpaces = 9;

   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         if(board[i][j] != ' ')
         {
            freeSpaces--;
         }
      }
   }
   return freeSpaces;
}

void playerMove()
{
   int x;
   int y;

   do
   {
      printf("Enter row #(1-3): ");
      scanf("%d", &x);

      printf("Enter column #(1-3): ");
      scanf("%d", &y);

      if (x < 1 || x > 3 || y < 1 || y > 3) { // Check if input is out of range
         printf("Invalid input! Please enter numbers between 1 and 3.\n");
         continue;
      }

      
      x--; // Convert 1-based input to 0-based indexing
      y--;

      if(board[x][y] != ' ')
      {
         printf("Invalid move!Cell already occupied.\n");
      }
      else
      {
         board[x][y] = PLAYER;
         break;
      }
   } while (board[x][y] != ' ');
}

void computerMove()
{
   int x;
   int y;

   if(checkFreeSpaces() > 0)
   {
      do
      {
         x = rand() % 3;  // Generate random row (0-2)
         y = rand() % 3;

      } while (board[x][y] != ' ');  // Repeat until an empty space is found

      board[x][y] = COMPUTER;
   }
   else
   {
      printWinner(' ');   //If no free spaces, it's a tie
   }
}

char checkWinner()
{
   //check rows
   for(int i = 0; i < 3; i++)
   {
      if(board[i][0] == board[i][1] && board[i][0] == board[i][2])
      {
         return board[i][0];
      }
   }

   //check columns
   for(int i = 0; i < 3; i++)
   {
      if(board[0][i] == board[1][i] && board[0][i] == board[2][i])
      {
         return board[0][i];
      }
   }

   //check diagonals
   if(board[0][0] == board[1][1] && board[0][0] == board[2][2])
   {
      return board[0][0];
   }
   if(board[0][2] == board[1][1] && board[0][2] == board[2][0])
   {
      return board[0][2];
   }

   return ' ';  // Return ' ' if no winner
}

void printWinner(char winner)
{
   if(winner == PLAYER)
   {
      printf("YOU WIN!");
   }
   else if(winner == COMPUTER)
   {
      printf("YOU LOSE!");
   }
   else{
      printf("IT'S A TIE!");
   }
}