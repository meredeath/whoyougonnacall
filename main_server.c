#include "networking.h"

void process(char *s);
void subserver(int from_client);

int main() {

  int listen_socket;
  int f;
  listen_socket = server_setup();

  int num_players = 2;
  
  int players[num_players];
  int player_points[num_players];
  char buffer[BUFFER_SIZE];
  
  for (int i = 0; i < num_players; i++)
    {
      players[i] = server_connect(listen_socket);
      player_points[i] = 0;
      
      sprintf(buffer, "Welcome Player %d! Please patiently wait for all other players to connect.\n", i);
      
      write( players[i], buffer, sizeof(buffer) );
    }

  for (int i = 0; i < num_players; i++)
    {
      sprintf(buffer, "All players have connected!\n");
      
      write( players[i], buffer, sizeof(buffer) );
    }

  int current_player = 0;
  sprintf(buffer, "ghghghghghgghg");
    
  while (1)
    {
      printf("Current player: %d\n", current_player);
      
      if (strcmp(buffer, "ghghghghghgghg") == 0)
	{
	  sprintf(buffer, "Congrats! You are the first player!\n");
	  
	  write( players[current_player], buffer, sizeof(buffer) );
	}
      else
	{
	  int prev_player = current_player - 1;

	  if (prev_player < 0)
	    prev_player = num_players - 1;

	  char temp[BUFFER_SIZE];
	  read( players[prev_player], temp, sizeof(buffer) );
	  
	  sprintf(buffer, "This is what the previous player has said: %s\n", temp);

	  write( players[current_player], buffer, sizeof(buffer) );
      
	}
	
      sprintf(buffer, "Please say something to the next player: ");
      
      write( players[current_player], buffer, sizeof(buffer) );

      current_player = (current_player + 1) % num_players;
    }
}
