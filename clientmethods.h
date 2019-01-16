int intro(); // prints stuff

int waiting(int numplayers, int scores[], char * letters, int activeplayer); //block until receive message, return the message

int playround(int server_socket, int numplayers, int scores[], char * letters, int activeplayer); //print game state, ask for a letter, send it to server

int printstate(int numplayers, int scores[], char * letters, int activeplayer); // helper function

int firstplay(int server_socket, int numplayers, int scores[], char * letters, int activeplayer);

int normround(int server_socket, int numplayers, int scores[], char * letters, int activeplayer);

int winround(); // reads from server the index of the loser, displays message to user

int loseround(); // displays message to user

int wingame();

int losegame();

int enterblock(); // "press enter to continue"

int displayheader();

int displayline(char * toprint); // toprint must be shorter than 64 (not null) characters, otherwise only the first 63 non-null characters will be displayed; also DO NOT pass any \n characters

int displayquestion(char * toprint); //same as displaylie(), but for when you want user input after it is printed

int gameover(); // tells the user the server shut them down.

int challenge(int server_socket, int numplayers, int scores[], char * letters, int activeplayer); // tells user that they have been challenged, asks for completed word and sends the word to the server


