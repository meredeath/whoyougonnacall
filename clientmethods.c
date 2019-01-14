#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "clientmethods.h"
#include "networking.h"


#define clear printf("\033[H\033[J")

int intro() { // prints stuff
  	char input[16];
  	while(1) {
  		clear;
		printf("Welcome to GHOST!\nHere are your options:\n\n[1] Read Instructions\n[2] Join Game\n\nChoose an option (1 or 2): ");
		fgets(input, 16, stdin);
	  	if(!strncmp(input,"1",1)) {
	  		clear;
	  		printf("Insert Instructions Here\n"); // What do we want to put here?
	  		printf("Press Enter to return to the main menu.");
	  		fgets(input, 16, stdin);
	  		continue; // goes back to main menu
	  	}
	  	if(!strncmp(input,"2",1)) {
	  		break;
	  		// should now go to wait after intro() is done
	  	}
	  	clear;
	  	printf("░░░░▄▄▄▄▀▀▀▀▀▀▀▀▄▄▄▄▄▄\n░░░░█░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░▀▀▄\n░░░█░░░▒▒▒▒▒▒░░░░░░░░▒▒▒░░█\n░░█░░░░░░▄██▀▄▄░░░░░▄▄▄░░░█\n░▀▒▄▄▄▒░█▀▀▀▀▄▄█░░░██▄▄█░░░█\n█▒█▒▄░▀▄▄▄▀░░░░░░░░█░░░▒▒▒▒▒█\n█▒█░█▀▄▄░░░░░█▀░░░░▀▄░░▄▀▀▀▄▒█\n░█▀▄░█▄░█▀▄▄░▀░▀▀░▄▄▀░░░░█░░█\n░░█░░▀▄▀█▄▄░█▀▀▀▄▄▄▄▀▀█▀██░█\n░░░█░░██░░▀█▄▄▄█▄▄█▄████░█\n░░░░█░░░▀▀▄░█░░░█░███████░█\n░░░░░▀▄░░░▀▀▄▄▄█▄█▄█▄█▄▀░░█\n░░░░░░░▀▄▄░▒▒▒▒░░░░░░░░░░█\n░░░░░░░░░░▀▀▄▄░▒▒▒▒▒▒▒▒▒▒░█\n░░░░░░░░░░░░░░▀▄▄▄▄▄░░░░░█\nPlease follow directions\n");
		break;
	}
	return 0;
}

int waiting(int server_socket, int numplayers, int scores[], char * letters, int activeplayer, char * buffer) { //block until receive message, return the message
	clear;
	for(int i = 0; i < numplayers; i++) {
		printf("Player %d's score: %d\n", i, scores[i]);
	}
	printf("\nLetters in play: %s\n", letters);
	printf("\nWaiting for Player %d...\n", activeplayer);
	int err = read( server_socket, buffer, sizeof(buffer) );
	if(err == -1) {
		strncpy(buffer, "error", BUFFER_SIZE);
		return -1;
	}
	return 0;
}

int playround() { //print game state, ask for a letter, send it to server
	// fscanf(stdin, "%s", buffer);
 //    write( server_socket, buffer, sizeof(buffer) );
	return 0;
}

//TESTING
int main() {
	intro();
	int scores[3];
	scores[0] = 3;
	scores[1] = 5;
	scores[2] = 4;
	char buffer[BUFFER_SIZE];
	waiting(2019, 3, scores, "bla", 2, buffer );
	printf("%s\n", buffer);
	return 0;
}