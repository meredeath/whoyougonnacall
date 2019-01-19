#ifndef MAIN_SERVER
#define MAIN_SERVER

#define NUM_PLAYERS 2
#define BUFFER_SIZE 256

int players_waiting(int curr);
int swap(int player);
static void sighandler(int signo);

#endif
