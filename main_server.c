#include "networking.h"
#include "bsearch.h"
#include "main_server.h"
#include <signal.h>

int listen_socket;
int f; //what is f?
int players[NUM_PLAYERS];
int player_points[NUM_PLAYERS];
char buffer[BUFFER_SIZE];
int num_players;

static void sighandler(int signo){
//will not let players close the server with SIGINT, because then the sockets can't close
  if (signo == SIGINT){
    for (int i = 0; i < num_players; i++){
	shutdown(players[i], 2);
    }
  }
}

int main()
{
  //handle C^ signal
  signal(SIGINT, sighandler);

  //setting up player # and listening socket in the server
  num_players = NUM_PLAYERS;
  listen_socket = server_setup();

  //connect players to server
  for (int i = 0; i < num_players; i++){
    players[i] = server_connect(listen_socket);
    player_points[i] = 0;  
      //printf(buffer, "Welcome Player %d! Please patiently wait for all other players to connect.\n", i);
      // write(players[i], buffer, sizeof(buffer) );
  }
  
  //telling players what player number they are
  for (int i = 0; i < num_players; i++){
      write_num_to_player(i);
      /*
      sprintf( buffer, "%d", i );
      printf("%s\n", buffer);
      write( players[i], buffer, sizeof(buffer));
      
      sprintf( buffer, "%d", num_players );
      printf("%s\n", buffer);
      write( players[i], buffer, sizeof(buffer) );
      */
  }

  //setting up current player/prev player for challenge purposes
  int prev_player = 0;
  int curr_player = 0;

  //the word so far in the current round
  char inplay_letters[BUFFER_SIZE];
  
  while (1){
      //printing player scores
      print_scores(num_players);

      //if this is the first round
      if (curr_player == prev_player){
	  
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
	  strcpy( inplay_letters, buffer );

	  // change curr player to next in turn
	  curr_player = (curr_player + 1) % num_players;
      }else{
	  // normal round
	  
	  // give to them the letters in play
	print_inplay(curr_player, inplay_letters);

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

	  //printf("letters in play: [%s]\n", inplay_letters); why is this needed

	  // bsearch
	  if (binsearch(inplay_letters)){
	      // it is a word
	      // curr is accused of word
	      printf("found word: [%s]", inplay_letters);

	      print_scores(num_players);//print the scores

	      //what is this
	      sprintf( buffer, " " );
	      write( players[i], buffer, sizeof(buffer) );
	  }
	      
	  for (int i = 0; i < num_players; i++){
		  if (curr_player == i){
		      sprintf( buffer, "lose round" );
		      write( players[i], buffer, sizeof(buffer) );

		      // player gains a point for losing
		      player_points[i] += 1;

		      //if player has lost 5 times, they are kicked out
		      if (player_points[i] == 5){
			  // write end condition
			  // and break out
			  // start a new game
		      }
		  }else{
		    //if you didn't lose, you won because you survived
		    sprintf( buffer, "win round" );
		    write( players[i], buffer, sizeof(buffer) );

		    sprintf( buffer, "%d", curr_player );
		    write( players[i], buffer, sizeof(buffer) );
		  }
	  }      
	  else{
	      // word was NOT formed, so keep playing. change curr players.
	      curr_player = (curr_player + 1) % num_players;
	  }
	  
      }//closing if normalround/firstround if
      
  }//closing while loop
  
}//closing main

int write_num_to_player(int k){
  sprintf(buffer, "%d", k );
  printf("%s\n", buffer);
  if (write(players[k], buffer, sizeof(buffer)) == -1){
    printf("error %d: %s\n", errno, strerror(errno));
  }
}

int print_inplay(int cur, char *letters){
  sprintf(buffer, "%s", letters );
  if (write( players[cur], buffer, sizeof(buffer)) == -1){
    printf("error %d: %s\n", errno, strerror(errno));
  }
}

int clear_inplay(char *letters){
  sprintf( buffer, " " );
  if(write( players[i], buffer, sizeof(buffer)) == -1){
    printf("error on clearing inplay letters %d: %s\n", errno, strerror(errno);
  }
}

void print_scores(int numplayers){
  printf("\n\nPrinting scores\n");
  for(int i = 0; i < num_players; i++){
    for (int j = 0; j < num_players; j++){
      printf("Player %d score: %d\n", i, j);
      sprintf( buffer, "%d", player_points[j] );
      write( players[i], buffer, sizeof(buffer) );
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
