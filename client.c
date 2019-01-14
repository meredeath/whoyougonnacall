#include "networking.h"

#define clear printf("\033[H\033[J")

int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  // welcome
  clear;
  printf("Welcome to GHOST!\n");
  printf("Here are your options:\n");

  // allow them to join or read instructions


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
