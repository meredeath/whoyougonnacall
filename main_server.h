#ifndef MAIN_SERVER
#define MAIN_SERVER

#define NUM_PLAYERS 2
#define BUFFER_SIZE 256

void print_scores(int numplayers);
int waiting(int curr);
static void sighandler(int signo);
int write_num_to_player(int k);
int print_inplay(int cur, char *letters);
int clean_inplay(char *letters);

#endif
