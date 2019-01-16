#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "clientmethods.h"
#include "networking.h"

#define LEN 63 //don't change this

#define clear printf("\033[H\033[J")

int intro()
{ // prints stuff
  char input[BUFFER_SIZE];

  while(1) {
    displayheader();

    displayline("Welcome to GHOST!");
    displayline("Here are your options:");
    displayline("");
    displayline("  [1] Read Instructions");
    displayline("  [2] Join Game");
    displayline("");
    displayquestion("Choose an option (enter \"1\" or \"2\"): ");
    fgets(input, BUFFER_SIZE, stdin);

    if(!strncmp(input,"1",1))
    	{
    	  displayheader();

    	  displayline("Insert Instructions Here"); // What do we want to put here?
        enterblock();

    	  fgets(input, BUFFER_SIZE, stdin);
    	  continue; // goes back to main menu
    	}
      
    if(!strncmp(input,"2",1)) {
    	break;
    	// should now go to wait after intro() is done
    }
    // trolling for idiots
    clear;
    printf("░░░░▄▄▄▄▀▀▀▀▀▀▀▀▄▄▄▄▄▄\n░░░░█░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░▀▀▄\n░░░█░░░▒▒▒▒▒▒░░░░░░░░▒▒▒░░█\n░░█░░░░░░▄██▀▄▄░░░░░▄▄▄░░░█\n░▀▒▄▄▄▒░█▀▀▀▀▄▄█░░░██▄▄█░░░█\n█▒█▒▄░▀▄▄▄▀░░░░░░░░█░░░▒▒▒▒▒█\n█▒█░█▀▄▄░░░░░█▀░░░░▀▄░░▄▀▀▀▄▒█\n░█▀▄░█▄░█▀▄▄░▀░▀▀░▄▄▀░░░░█░░█\n░░█░░▀▄▀█▄▄░█▀▀▀▄▄▄▄▀▀█▀██░█\n░░░█░░██░░▀█▄▄▄█▄▄█▄████░█\n░░░░█░░░▀▀▄░█░░░█░███████░█\n░░░░░▀▄░░░▀▀▄▄▄█▄█▄█▄█▄▀░░█\n░░░░░░░▀▄▄░▒▒▒▒░░░░░░░░░░█\n░░░░░░░░░░▀▀▄▄░▒▒▒▒▒▒▒▒▒▒░█\n░░░░░░░░░░░░░░▀▄▄▄▄▄░░░░░█\n Follow directions\n");
    break;
  }
  return 0;
}

int printstate(int numplayers, int scores[], char * letters, int activeplayer)
{ // helper function
  displayheader();
  char * temp;
  for(int i = 0; i < numplayers; i++) {
    sprintf(temp, "Player %d's score: %d", i, scores[i]);
    displayline(temp);
  }

  displayline("");
  
  sprintf(temp, "Letters in play: %s_", letters);
  displayline(temp);

  return 0;
}

int waiting( int numplayers, int scores[], char * letters, int activeplayer)
{
  //block until receive message, return the message
  printstate(numplayers, scores, letters, activeplayer);
  char * temp;
  displayline("");
  sprintf(temp, "Waiting for Player %d...", activeplayer);
  displayline(temp);

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
  
  displayquestion("Enter a letter: ");
  fgets(input, BUFFER_SIZE, stdin);
  input[1] = 0;

  if (input[0]>='A' && input[0]<='Z') {
    input[0] = input[0] + 'a' - 'A';
  }

  write( server_socket, input, sizeof(input) ); // should add some formatting / message standardization

  return 0;
}


int firstplay(int server_socket, int numplayers, int scores[], char * letters, int activeplayer)
{
  displayline("You are the first round!");
  enterblock();
  playround( server_socket, numplayers, scores, letters, activeplayer);
    
  return 0;
}

int normround(int server_socket, int numplayers, int scores[], char * letters, int activeplayer)
{
  displayline("It is your round!");
  enterblock();
  playround( server_socket, numplayers, scores, letters, activeplayer);
  return 0;
}

int winround( int server_socket) {
  char buffer[BUFFER_SIZE];
  int err = read( server_socket, buffer, sizeof(buffer) );
  
  char * temp;
  sprintf(temp, "Player %s lost the round.", buffer);
  displayline(temp);
  enterblock();
  return 0;
}

int loseround() {
  displayline("You lost the round.");
  enterblock();
  return 0;
}

int wingame() {
  displayline("You won the game.");
  enterblock();
  return 0;
}

int losegame() {
  displayline("You lost the game.");
  enterblock();
  return 0;
}

int enterblock() { // "press enter to continue"
  displayline("Press Enter to continue...");
  char input[BUFFER_SIZE];
  fgets(input, BUFFER_SIZE, stdin);
  return 0;
}

int displayheader() {
  clear;
  printf("*********************************************************************\n*                                                                   *\n*      0000      00      00       0000         0000     0000000000  *\n*    00          00      00     00    00     00    00       00      *\n*  00            00      00   00        00   00             00      *\n*  00            0000000000   00        00     0000         00      *\n*  00     0000   00      00   00        00         00       00      *\n*    00    00    00      00     00    00     00    00       00      *\n*      0000      00      00       0000         0000         00      *\n*                                                                   *\n*                                                                   *\n");
  return 0;
  // "*  " + 63 characters + "  *"
}

int displayline(char * toprint) { //toprint must be shorter than 64 (not null) characters
  char spacer[LEN + 1];
  for(int i = 0;i < LEN;i++) {
    spacer[i]=' ';
  }
  spacer[LEN]=0;
  int tocopy = LEN;
  if(strlen(toprint)<LEN ) {
    tocopy = strlen(toprint);
  }
  strncpy(spacer,toprint,tocopy);
  printf("*  %s  *\n", spacer);
  return 0;
}

int displayquestion(char * toprint) { //same as displaylie(), but for when you want user input after it is printed
  char spacer[LEN];
  for(int i = 0;i < LEN;i++) {
    spacer[i]=0;
  }
  strncpy(spacer,toprint,LEN - 1);
  printf("\n   %s", spacer);
  fflush(stdout);
  return 0;
}

int gameover() {
  displayheader();
  displayline("The game is over.");
  displayline("");
  displayline("Good bye. Thanks for playing. Move on with your life.");
  return 0;
}


//TESTING
// int main()
// {
//   displayheader();
//   displayline("blahasdfasdfasdf");
//   displayline("012345670123456701234567012345670123456701234567012345670123456701234567012345670123456701234567");
  // intro();

//   int scores[3];

//   scores[0] = 3;
//   scores[1] = 5;
//   scores[2] = 4;


//   waiting(2019, 3, scores, "bla", 2 );

//   playround(2019, 3, scores, "bla", 2 );
//   return 0;
// }


