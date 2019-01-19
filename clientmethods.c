#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "clientmethods.h"
#include "networking.h"

#define LEN 63 //don't change this

#define clear printf("\033[H\033[J")

int intro()
{ // prints stuff
  char input[BUFFER_SIZE];

  while(1)
    {
      displayheader();

      displayline("Welcome to GHOST!");
      displayline("Here are your options:");

      displayline("");
      displayline("~~~~~~~~~~~~~~~~~~~~~~~~~");
      displayline("~ [1] Read Instructions ~");
      displayline("~ [2] Join Game         ~");
      displayline("~~~~~~~~~~~~~~~~~~~~~~~~~");
      displayline("");
      
      displayquestion("Choose an option (enter \"1\" or \"2\"): ");

      fgets(input, BUFFER_SIZE, stdin);

      if(!strncmp(input,"1",1))
    	{
    	  displayheader();

    	  displayline("                 :INSTRUCTIONS:");
	  displayline("");
	  
	  displayline("Once again, welcome to GHOST!");
	  displayline("");
	  
	  displayline("You can start playing by selecting option 2 on the menu.");
	  displayline("You will either create a new game or join an existing one.");
	  displayline("If you are player 0, wait for another player to connect.");
	  displayline("Once there are two players present, press enter to continue.");
	  displayline("");
	  
	  displayline("The game will prompt you for a letter.");
	  displayline("You two players will take turns giving letters to the game.");
	  displayline("The objective is to not form a word.");
	  displayline("~Note: invalid word prefixes will cause an error.");
	  displayline("Whichever player forms a word first by giving a letter");
	  displayline("gains a point for doing so.");
	  displayline("");
	  
	  displayline("When a player has five points, they have lost and the other");
	  displayline("player is the winner.");
	  displayline("~Note: You cannot quit the game. If you want to exit you must");
	  displayline("either win or lose.");
	  displayline("~Note: If you enter a word, only the first letter will be taken.");
	  displayline("");
	  displayline("Good luck!");
	  //displayline("");
	  //displayline("");
	  //displayline("");
	  //displayline("");
	  //displayline("");
	  //displayline("");
	  
	  enterblock();

    	  fgets(input, BUFFER_SIZE, stdin);
    	  continue; // goes back to main menu
    	}


      if(!strncmp(input,"2",1))
	{
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
  char temp[BUFFER_SIZE];

  displayline("SCORES:");
  for(int i = 0; i < numplayers; i++) {
    sprintf(temp, "Player %d's score: %d", i, scores[i]);
    //printf("put player's scores in\n");
    displayline(temp);
  }
  
  displayline("");
  
  sprintf(temp, "Letters in play: %s_", letters);
  displayline(temp);
  
  return 0;
}

int waiting(int numplayers, int scores[], char * letters, int activeplayer)
{
  //block until receive message, return the message
  printstate(numplayers, scores, letters, activeplayer);

  char temp[BUFFER_SIZE];
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

  write( server_socket, input, sizeof(input) );

  return 0;
}

int displayheader() {
  clear;
  printf("*********************************************************************\n*                                                                   *\n*      0000      00      00       0000         0000     0000000000  *\n*    00          00      00     00    00     00    00       00      *\n*  00            00      00   00        00   00             00      *\n*  00            0000000000   00        00     0000         00      *\n*  00     0000   00      00   00        00         00       00      *\n*    00    00    00      00     00    00     00    00       00      *\n*      0000      00      00       0000         0000         00      *\n*                                                                   *\n*                                                                   *\n");
  return 0;
  // "*  " + 63 characters + "  *"
  return 0;
//"*  " + 63 characters + "  *"
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
  printf("You are the first round! :)\n");
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

  char temp[BUFFER_SIZE];
  displayline("  <----------------------------------->"); 
  sprintf(temp, "    <-Player %s lost the round.->", buffer);
  displayline(temp);
  displayline("<-Which means you won!!! Keep it going!->");
  displayline("  <----------------------------------->"); 
  
  enterblock();
  return 0;
}

int loseround() {
  displayline("");
  displayline("  <----------------------------------->");
  displayline("<-You lost this round :( Maybe next time?->");
  displayline("  <----------------------------------->");
  displayline("");
  //enterblock();
  return 0;
}

int wingame() {
  displayline("CONGRATULATIONS!");
  displayline("You won the game.");
  //enterblock();
  return 0;
}

int losegame() {
  displayline("Oh no :(");
  displayline("You lost the game.");
  //enterblock();
  return 0;
}

int enterblock() { // "press enter to continue"
  displayline("");
  displayline("--------------------------");
  displayline("Press Enter to continue...");
  char input[BUFFER_SIZE];
  fgets(input, BUFFER_SIZE, stdin);
  return 0;
}

int displayquestion(char * toprint) { //same as displayline(), but for when you want user input after it is printed
  char spacer[LEN];
  for(int i = 0;i < LEN;i++) {
    spacer[i]=0;
  }
  strncpy(spacer,toprint,LEN - 1);
  printf("\n   %s", spacer);
  fflush(stdout);
  return 0;
}

int death(int server_socket, char * buffer)
{
  if(strcmp(buffer, "exit") == 0){

    if (close( server_socket ) == -1)
      {
	printf("error %d: %s\n", errno, strerror(errno));
      }

    printf("\n- - - - - - - - - - - - - - - - - AHHHHHHHHHH!- - - - - - - - - - - - - - - - - -\n");
    printf("We apologize for this inconvenience. The server has been terminated. To play the game restart the server and try again.\n");
    printf("^._____________________________________________________________.^\n\n");

    exit(0);
    printf("successfully exited the client program \n");    
  }

}
