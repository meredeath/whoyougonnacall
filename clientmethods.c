#include <stdlib.h>
#include <stdio.h>
#include "clientmethods.h"

#define clear printf("\033[H\033[J")

int intro() { // prints stuff
  	char input[16];
  	while(1) {
  		clear;
		printf("Welcome to GHOST!\nHere are your options:\n\n[1] Read Instructions\n[2] Join Game\n\nChoose an option (1 or 2): ");
		fgets(input, 16, stdin);
	  	if(!strncmp(input,"1",1)) {
	  		clear;
	  		printf("Insert Instructions Here\n", ); // What do we want to put here?
	  		printf("Press Enter to return to the main menu.");
	  		fgets(input, 16, stdin);
	  		continue; // goes back to main menu
	  	}
	  	if(!strncmp(input,"2",1)) {
	  		break;
	  		// should now go to wait after intro() is done
	  	}
	  	clear;
	  	printf("░░░░▄▄▄▄▀▀▀▀▀▀▀▀▄▄▄▄▄▄\n░░░░█░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░▀▀▄░░░█░░░▒▒▒▒▒▒░░░░░░░░▒▒▒░░█\n░░█░░░░░░▄██▀▄▄░░░░░▄▄▄░░░█\n░▀▒▄▄▄▒░█▀▀▀▀▄▄█░░░██▄▄█░░░█\n█▒█▒▄░▀▄▄▄▀░░░░░░░░█░░░▒▒▒▒▒█\n█▒█░█▀▄▄░░░░░█▀░░░░▀▄░░▄▀▀▀▄▒█\n░█▀▄░█▄░█▀▄▄░▀░▀▀░▄▄▀░░░░█░░█\n░░█░░▀▄▀█▄▄░█▀▀▀▄▄▄▄▀▀█▀██░█\n░░░█░░██░░▀█▄▄▄█▄▄█▄████░█\n░░░░█░░░▀▀▄░█░░░█░███████░█\n░░░░░▀▄░░░▀▀▄▄▄█▄█▄█▄█▄▀░░█\n░░░░░░░▀▄▄░▒▒▒▒░░░░░░░░░░█\n░░░░░░░░░░▀▀▄▄░▒▒▒▒▒▒▒▒▒▒░█\n░░░░░░░░░░░░░░▀▄▄▄▄▄░░░░░█\nPlease follow directions");
	}
}

char * waiting(int server_socket); //block until receive message, return the message

int round(); //print game state, ask for a letter, send it to server