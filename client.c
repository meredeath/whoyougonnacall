#include <string.h>
#include <signal.h>
#include "networking.h"
#include "clientmethods.h"

#define clear printf("\033[H\033[J")

char buffer[BUFFER_SIZE];
int me;
int server_socket;

static void sighandler(int signo){
  if (signo == SIGINT){
    /*
    //send server a player has killed themselves
    sprintf( buffer, "%s", "client_killed");
    if (write( server_socket, buffer, sizeof(buffer) ) == -1){
      printf("error writing to server client killed signal\n");
    }

    //send server the number of the dead player
    sprintf( buffer, "%d", me);
    if (write( server_socket, buffer, sizeof(buffer) ) == -1){
      printf("error writing to server player number\n");
    }
    
    //close socket to server
    if (close(server_socket) == -1){
      printf("error closing socket to server");
    }
    printf("You have lost the game automatically by forfeiting.\n");
    exit(0);
    */
    //printf("you cannot quit the game. If you wish to stop playing, just lose on purpose to exit.\n");

    return;
  }
}

int main(int argc, char **argv) {

  //adding signal handling
  signal(SIGINT, sighandler);
  
  // welcome
  clear;
  printf("Welcome to GHOST!\n");
  printf("Here are your options:\n");

  // allow them to join or read instructions
  intro();

  // join the game
  if (argc == 2)
    server_socket = client_setup( argv[1] );
  else
    server_socket = client_setup( TEST_IP );

  printf("connected to server\n");
  printf("Waiting for other players to come join.");
  
  me = 0;
  
  int num_players = 0;

  // get the player's number
  read( server_socket, buffer, sizeof(buffer) );
  death(server_socket, buffer);
  
  me = atoi( buffer );
  printf("error %d: %s\n", errno, strerror(errno));
  printf("i am player %d\n", me);
  
  // get the number of players
  read( server_socket, buffer, sizeof(buffer) );
  death(server_socket, buffer);
  
  num_players = atoi( buffer );
  printf("error %d: %s\n", errno, strerror(errno));
  printf("received the number of players: %d\n", num_players);

  int scores[num_players];
  char letters[BUFFER_SIZE];
  
  while (1)
    {
      // get all the current scores of the players
      for (int i = 0; i < num_players; i++)
	{
	  read( server_socket, buffer, sizeof(buffer) );

	  if(strcmp(buffer, "lose game") == 0){

	    if (close( server_socket ) == -1)
	      {
		printf("error %d: %s\n", errno, strerror(errno));
	      }

	    close(server_socket);
	    losegame();
	    
	    //printf("");
	    exit(0);
	    printf("successfully exited the client program \n");
	  }

	  if(strcmp(buffer, "win game") == 0){

	    if (close( server_socket ) == -1)
	      {
		printf("error %d: %s\n", errno, strerror(errno));
	      }

	    close(server_socket);
	    wingame();
	    
	    //printf("");
	    exit(0);
	    printf("successfully exited the client program \n");
	  }


	  death(server_socket, buffer);
	  scores[i] = atoi( buffer );
      
	  printf("Player %d score: %d\n", i, scores[i]);
	}

      // letters
      read( server_socket, letters, sizeof(buffer) );
      death(server_socket, buffer);
      printf("letters: %s\n", letters);
      
      // find out which prompt it is
      read( server_socket, buffer, sizeof(buffer) );
      death(server_socket, buffer);
      printf("%s\n", buffer);
  
      // first play
      if (strcmp(buffer, "first play") == 0)
	{
	  firstplay( server_socket, num_players, scores, letters, me);
	}
  
      // round
      if (strcmp(buffer, "round") == 0)
	{
	  normround( server_socket, num_players, scores, letters, me);
	}
      
      // challenged

      // win round
      if (strcmp(buffer, "win round") == 0)
	{
	  winround(server_socket);
	}
      
      // lose round
      if (strcmp(buffer, "lose round") == 0)
	{
	  loseround();
	}
      
      // waiting
      if (strcmp(buffer, "wait") == 0)
	{
	  waiting( num_players, scores, letters,  me);
	}
    }
  
  /*
    for (int i = 0; i < 2; i++)
    {
      read( server_socket, buffer, sizeof(buffer) );
      clear;
      printf("%s", buffer);
      fflush(stdout);
    }
  
  while (1)
    {
      read( server_socket, buffer, sizeof(buffer) );
      if ( strcmp( buffer, "first play" ) )
	{
	  
	}
    }
    /*
  // intro
  // *  ____________________
  // * |
  // * | WELCOME PLAYER 0!
  // * | 
  // * | This is GHOST
  // * |
  // * | Options:
  // * | [1] instruction
  // * | [2] join game
  // * |
  // * | Input: _
  // round_face0
  // *  ____________________
  // * |
  // * | Player 0's score: 2
  // * |  
  // * | letters in play: cou_
  // * |
  // * | Options:
  // * | [1] challenge previous player
  // * | [2] input a letter
  // * |
  // * | Input: _
  // round_face1
  // *  ____________________
  // * |
  // * | Player 0's score: 2
  // * |  
  // * | letters in play: cou_
  // * |
  // * | Please input a letter.
  // * | 
  // * | Input: _
  // * | 
  // waiting
  // *  ____________________
  // * |
  // * | Player 0's score: 2
  // * |  
  // * | letters in play: cou_
  // * |
  // * | Waiting for Player 2...
  // * | 
  // * | 
  // * | 
  '''
  for (int i = 0; i < 2; i++)
    {
      read( server_socket, buffer, sizeof(buffer) );
      clear;
      printf("%s", buffer);
      fflush(stdout);
    }
  
  while (1)
    {
      read( server_socket, buffer, sizeof(buffer) );
      printf("%s", buffer);
      fflush(stdout);
      read( server_socket, buffer, sizeof(buffer) );
      clear;
      printf("%s", buffer);
      fflush(stdout);
      
      fscanf(stdin, "%s", buffer);
      write( server_socket, buffer, sizeof(buffer) );
      clear;
      printf("Now waiting for a response.");
      
    }
  '''
  /*
  while (1) {
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(server_socket, buffer, sizeof(buffer));
    read(server_socket, buffer, sizeof(buffer));
    printf("received: [%s]\n", buffer);
  }
  */
}
