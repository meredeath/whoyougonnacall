#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "clientmethods.h"
#include "networking.h"


#define clear printf("\033[H\033[J")

int intro()
{ // prints stuff
  char input[BUFFER_SIZE];

  while(1)
    {
      clear;

      printf("Welcome to GHOST!\nHere are your options:\n\n[1] Read Instructions\n[2] Join Game\n\nChoose an option (enter \"1\" or \"2\"): ");
      fflush(stdout);
      fgets(input, BUFFER_SIZE, stdin);

      if(!strncmp(input,"1",1))
	{
	  clear;

	  printf("Insert Instructions Here\n"); // What do we want to put here?
	  printf("Press Enter to return to the main menu.");

	  fgets(input, BUFFER_SIZE, stdin);
	  continue; // goes back to main menu
	}
      
      if(!strncmp(input,"2",1)) {
	break;
	// should now go to wait after intro() is done
      }
      
      clear;
      printf("░░░░▄▄▄▄▀▀▀▀▀▀▀▀▄▄▄▄▄▄\n░░░░█░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░▀▀▄\n░░░█░░░▒▒▒▒▒▒░░░░░░░░▒▒▒░░█\n░░█░░░░░░▄██▀▄▄░░░░░▄▄▄░░░█\n░▀▒▄▄▄▒░█▀▀▀▀▄▄█░░░██▄▄█░░░█\n█▒█▒▄░▀▄▄▄▀░░░░░░░░█░░░▒▒▒▒▒█\n█▒█░█▀▄▄░░░░░█▀░░░░▀▄░░▄▀▀▀▄▒█\n░█▀▄░█▄░█▀▄▄░▀░▀▀░▄▄▀░░░░█░░█\n░░█░░▀▄▀█▄▄░█▀▀▀▄▄▄▄▀▀█▀██░█\n░░░█░░██░░▀█▄▄▄█▄▄█▄████░█\n░░░░█░░░▀▀▄░█░░░█░███████░█\n░░░░░▀▄░░░▀▀▄▄▄█▄█▄█▄█▄▀░░█\n░░░░░░░▀▄▄░▒▒▒▒░░░░░░░░░░█\n░░░░░░░░░░▀▀▄▄░▒▒▒▒▒▒▒▒▒▒░█\n░░░░░░░░░░░░░░▀▄▄▄▄▄░░░░░█\nPlease follow directions\n");
      break;
  }
  return 0;
}

int printstate(int numplayers, int scores[], char * letters, int activeplayer)
{ // helper function
  clear;
  
  for(int i = 0; i < numplayers; i++)
    {
      printf("Player %d's score: %d\n", i, scores[i]);
    }
  
  printf("\nLetters in play: %s_\n", letters);

  return 0;
}

int waiting(int server_socket, int numplayers, int scores[], char * letters, int activeplayer)
{
  //block until receive message, return the message
  printstate(numplayers, scores, letters, activeplayer);
  printf("\nWaiting for Player %d...\n", activeplayer);

  /*
  char buffer[BUFFER_SIZE];
  int err = read( server_socket, buffer, sizeof(buffer) );
  if(err == -1)
    {
      strncpy(buffer, "error", BUFFER_SIZE);
      return -1;
    }
  */
  return 0;
}

int playround(int server_socket, int numplayers, int scores[], char * letters, int activeplayer)
{  
  //print game state, ask for a letter, send it to server
  printstate( numplayers, scores, letters, activeplayer );
  
  char input[BUFFER_SIZE];
  
  printf("\nEnter a letter: ");
  fflush(stdout);
  fgets(input, BUFFER_SIZE, stdin);
  input[1] = 0;

  if (input[0]>='A' && input[0]<='Z') {
    input[0] = input[0] + 'a' - 'A';
  }

  write( server_socket, input, sizeof(input) ); // should add some formatting / message standardization

  return 0;
}

//TESTING
// int main()
// {
//   intro();

//   int scores[3];

//   scores[0] = 3;
//   scores[1] = 5;
//   scores[2] = 4;


//   waiting(2019, 3, scores, "bla", 2 );

//   playround(2019, 3, scores, "bla", 2 );

//   return 0;
// }


int firstplay(int server_socket, int numplayers, int scores[], char * letters, int activeplayer)
{
  printf("You are the first round!\n");
  enterblock();
  playround( server_socket, numplayers, scores, letters, activeplayer);
    
  return 0;
}

int normround(int server_socket, int numplayers, int scores[], char * letters, int activeplayer)
{
  printf("It is your round!\n");
  enterblock();
  playround( server_socket, numplayers, scores, letters, activeplayer);
    
  return 0;
}

int winround( int server_socket) {
  char buffer[BUFFER_SIZE];
  int err = read( server_socket, buffer, sizeof(buffer) );
  printf("Player %s lost the round.\n", buffer);
  enterblock();
}

int loseround() {
  printf("You lost the round.\n");
  enterblock();
}

char * enterblock() { // "press enter to continue"
  printf("Press Enter to continue...\n");
  char input[BUFFER_SIZE];
  char * i = (char *) fgets(input, BUFFER_SIZE, stdin);
  return i;
}
