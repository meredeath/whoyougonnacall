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

