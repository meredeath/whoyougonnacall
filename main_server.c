#include "networking.h"
#include "bsearch.h"

int listen_socket;
int f;
  
int players[NUM_PLAYERS];
int player_points[NUM_PLAYERS];
char buffer[BUFFER_SIZE];

int num_players;

int waiting(int wait);

int main()
{
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
      
      if (curr_player == prev_player)
	{
	  // first play
	  
	  // give to them the letters in play
	  sprintf( buffer, " " );
	  printf("letters: %s\n", buffer);
	  printf("error %d: %s\n", errno, strerror(errno));

	  write( players[curr_player], buffer, sizeof(buffer) );
	  printf("error %d: %s\n", errno, strerror(errno));

	  // signals to every player other than current to wait 
	  waiting(curr_player);
	  
	  // signals to curr_player to start first play sequence
	  sprintf( buffer, "first play" );
	  write( players[curr_player], buffer, sizeof(buffer) );

	  // adds a letter to the letters in play
	  read( players[curr_player], buffer, sizeof(buffer) );
	  strcat( inplay_letters, buffer );

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
	  waiting(curr_player);
	  
	  //signals to curr_player to start normal round
	  sprintf( buffer, "round" );
	  write( players[curr_player], buffer, sizeof(buffer) );

	  // adds a letter to the letters in play
	  read( players[curr_player], buffer, sizeof(buffer) );
	  strcat( inplay_letters, buffer );

	  // maybe change position later
	  prev_player = (prev_player + 1) % num_players;

	  printf("letters in play: %s\n", inplay_letters);
	  // bsearch
	  if (binsearch(inplay_letters))
	    {
	      // it is a word
	      // curr is accused of word
	      printf("found word: %s", inplay_letters);
	    }
	  else
	    {
	      // change curr players
	      curr_player = (curr_player + 1) % num_players;
	    }
	  
	}

      
      
      
    }
      
}

int waiting(int curr)
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
