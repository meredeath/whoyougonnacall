#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <errno.h>

#include "dict.h"

int main() {

	// key_t key;
	int shmid;
	char (*data)[NUM_WORDS][MAX_WORD_LEN];

	shmid = shmget(DICT_ARR_KEY, NUM_WORDS*MAX_WORD_LEN*sizeof(char), 0644 | IPC_CREAT);

	data = shmat(shmid, (void *)0, 0);

	shmdt(data);
	shmctl(shmid, IPC_RMID, NULL);
	printf("The segment has been deleted.\n");
	
	return 0;
}

