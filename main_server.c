#include "networking.h"
#include "bsearch.h"
#include <signal.h>
#include <unistd.h>

int listen_socket;
int f;
  
int players[NUM_PLAYERS];
int player_points[NUM_PLAYERS];
char buffer[BUFFER_SIZE];

int num_players;

int players_waiting(int wait);
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
	printf("num_players right now is: %d\n", num_players);

	//close sockets to players
	
	if (close(players[i])==-1){
	  printf("error closing sockets to player\n");
	}

      }
    printf("got out of for loop in sighandler\n");
    //exit(1);//kill server
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
	  if (binsearch(inplay_letters))
	    {
	      // it is a word
	      // curr is accused of word
	      printf("found word: [%s]", inplay_letters);

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
			  // write end condition
			  // and break out
			  // start a new game
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
	  else
	    {
	      // change curr players
	      curr_player = (curr_player + 1) % num_players;
	    }
	  
	}
      
    }
      
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
