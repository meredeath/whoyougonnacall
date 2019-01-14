#include <stdlib.h>
#include <stdio.h>
#include "clientmethods.h"

#define clear printf("\033[H\033[J")

int intro() { // prints stuff
	clear;
	printf("Welcome to GHOST!\n");
  	printf("Here are your options:\n");
  	printf("\n");
  	printf("1. Read Instructions\n");
  	printf("2. Join Game\n");
  	printf("\n");
  	printf("Choose an option (1 or 2): ");
  	char input[16];
  	fgets(input, 16, stdin);
  	if(!strncmp(input,"1",1)) {
  		
  	}

}

char * waiting(int server_socket); //block until receive message, return the message

int round(); //print game state, ask for a letter, send it to server