int intro(); // prints stuff

int waiting(int server_socket, int numplayers, int scores[], char * letters, int activeplayer, char * buffer); //block until receive message, return the message

int playround(); //print game state, ask for a letter, send it to server