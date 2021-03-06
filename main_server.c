#include "networking.h"
#include "bsearch.h"
#include "main_server.h"
#include <signal.h>
#include <unistd.h>

int listen_socket;
int f;
  
int players[NUM_PLAYERS];
int player_points[NUM_PLAYERS];
char buffer[BUFFER_SIZE];

int num_players;

static void sighandler(int signo)
{
  if (signo == SIGINT)
  {
    for (int i = 0; i < NUM_PLAYERS; i++)
      {
	//send kill signals to players
	sprintf( buffer, "%s", "exit" );
	
	if (write( players[i], buffer, sizeof(buffer) )==-1 ){
	  printf("error writing to players to exit\n");
	}
	
	printf("i right now is: %d\n", i);
	//printf("num_players right now is: %d\n", num_players);

	//close sockets to players
	
	if (close(players[i])==-1){
	  printf("error closing sockets to player\n");
	}

      }
    printf("got out of for loop in sighandler\n");
    exit(0);//kill server
  }
}

int main()
{
  signal(SIGINT, sighandler);
  
  num_players = NUM_PLAYERS;
  listen_socket = server_setup();
  
  
  for (int i = 0; i < num_players; i++)
    {
      players[i] = server_connect(listen_socket);
      player_points[i] = 0;
      
      // sprintf(buffer, "Welcome Player %d! Please patiently wait for all other players to connect.\n", i);
      
      // write( players[i], buffer, sizeof(buffer) );
    }
  
  for (int i = 0; i < num_players; i++)
    {
      sprintf( buffer, "%d", i );
      printf("%s\n", buffer);
      write( players[i], buffer, sizeof(buffer) );
      
      sprintf( buffer, "%d", num_players );
      printf("%s\n", buffer);
      write( players[i], buffer, sizeof(buffer) );
    }

    
  int prev_player = 0;
  int curr_player = 0;

  char inplay_letters[BUFFER_SIZE];

  while(num_players > 1)
    {
  
      while (1)
	{
	  // taking in scores first
	  printf("\n\nPrinting scores\n");
	  for (int i = 0; i < num_players; i++)
	    {
	      for (int j = 0; j < num_players; j++)
		{
		  printf("Player %d score: %d\n", i, j);
		  sprintf( buffer, "%d", player_points[j] );
		  write( players[i], buffer, sizeof(buffer) );
		}
	    }
      
	  if (curr_player == prev_player && num_players == 2)
	    {
	      // first play
	  
	      // give to them the letters in play
	      sprintf( buffer, " " );
	      printf("letters: %s\n", buffer);
	      printf("error %d: %s\n", errno, strerror(errno));

	      write( players[curr_player], buffer, sizeof(buffer) );
	      printf("error %d: %s\n", errno, strerror(errno));

	      // signals to every player other than current to wait 
	      players_waiting(curr_player);
	  
	      // signals to curr_player to start first play sequence
	      sprintf( buffer, "first play" );
	      write( players[curr_player], buffer, sizeof(buffer) );

	      // adds a letter to the letters in play
	      read( players[curr_player], buffer, sizeof(buffer) );
	      strcpy( inplay_letters, buffer );

	      // change curr players
	      curr_player = (curr_player + 1) % num_players;
	    }
	  else
	    {
	      // not equal therefore normal round
	  
	      // give to them the letters in play
	      sprintf( buffer, "%s", inplay_letters );
	      write( players[curr_player], buffer, sizeof(buffer) );

	      // signals to every player other than current to wait
	      players_waiting(curr_player);
	  
	      //signals to curr_player to start normal round
	      sprintf( buffer, "round" );
	      write( players[curr_player], buffer, sizeof(buffer) );

	      // adds a letter to the letters in play
	      read( players[curr_player], buffer, sizeof(buffer) );
	      strcat( inplay_letters, buffer );

	      // maybe change position later
	      prev_player = (prev_player + 1) % num_players;

	      printf("letters in play: [%s]\n", inplay_letters);
	      // bsearch
	      int bin = binsearch(inplay_letters);
	      if (bin == -1 || bin == 1)
		{
		  // it is a word
		  // curr is accused of word
		  printf("found word: [%s]", inplay_letters);
		  break;
	      
		}
	      else
		{
		  // change curr players
		  curr_player = (curr_player + 1) % num_players;
		}
	  
	    }
      
	}


      
      // has broken out of while which means a round has ended 
      printf("\n\nPrinting scores\n");
      for (int i = 0; i < num_players; i++)
	{
	  for (int j = 0; j < num_players; j++)
	    {
	      printf("Player %d score: %d\n", i, j);
	      sprintf( buffer, "%d", player_points[j] );
	      write( players[i], buffer, sizeof(buffer) );
	    }

	  sprintf( buffer, " " );
	  write( players[i], buffer, sizeof(buffer) );
	}


      for (int i = 0; i < num_players; i++)
	{
	  if (curr_player == i)
	    {
	      sprintf( buffer, "lose round" );
	      write( players[i], buffer, sizeof(buffer) );

	      // player gains a point for losing
	      player_points[i] += 1;

	      if (player_points[i] == 5)
		{
		  swap(i);
		}
	    }
	  else
	    {
	      sprintf( buffer, "win round" );
	      write( players[i], buffer, sizeof(buffer) );

	      sprintf( buffer, "%d", curr_player );
	      write( players[i], buffer, sizeof(buffer) );
	    }
	}

      
    }

  sprintf( buffer, "win game" );
  write( players[0], buffer, sizeof(buffer) );

  close(0);
}

int players_waiting(int curr)
{
  for (int i = 0; i < num_players; i++)
    {
      if (i != curr)
	{
	  // give players current letters
	  write( players[i], buffer, sizeof(buffer) );
	  
	  // tell player to wait
	  sprintf( buffer, "wait" );
	  write( players[i], buffer, sizeof(buffer) );

	  // stand in for waiting
	  //sprintf( buffer, "standin" );
	  //write( players[i], buffer, sizeof(buffer) );
	}
    }
}

int swap(int player)
{
  int temp = players[player];
  players[player] = players[num_players - 1];

  int tempscores = player_points[player];
  player_points[player] = player_points[num_players - 1];
  player_points[num_players - 1] == tempscores;
  
  // should we tell the player to kill themselves?
  // client file should check that if they have 5 points
  // then they should close socket
  // and die for rn

  // send "lose game"

  sprintf( buffer, "lose game" );
  printf("%s\n", buffer);
  write( temp, buffer, sizeof(buffer) );

  
  close(temp);

  num_players -= 1;

  return 0;
  //if(player == 0){
  //return 1;
  //}else{
  //return 0;
  //}
}

/*
int player_death(char *stuff, int playsock){
  if (strcmp(buffer, "client_killed") == 0){

    //getting player number of player who quit
    read( playsock, buffer, sizeof(buffer) );
    int playnum = atoi(buffer);

    //send lose game to loser, grabs player who won
    int winner = swap(playnum);

    //send win game to winner
    sprintf( buffer, "win game" );
    printf("%s\n", buffer);
    write( players[winner], buffer, sizeof(buffer) ); 
  }
}
*/
