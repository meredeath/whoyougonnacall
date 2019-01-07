#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <errno.h>

// // Info for compatibility with other files

// /// top of file

// #define DICT_ARR_KEY 12358

// #define MAX_WORD_LEN 40

// #define NUM_WORDS 100000

// ////// in ur program

// 	int shmid;
// 	char (*data)[NUM_WORDS][MAX_WORD_LEN]; // pointer to 2d array

// 	shmid = shmget(DICT_ARR_KEY, NUM_WORDS*MAX_WORD_LEN*sizeof(char), 0644 | IPC_CREAT);

// 	data = shmat(shmid, (void *)0, 0);

// 	/// now do stuff with data



#define DICT_ARR_KEY 12358

#define MAX_WORD_LEN 40

#define DICT_FILENAME "dictall.txt"

#define NUM_WORDS 100000

int main() {

	// key_t key;
	int shmid;
	char (*data)[NUM_WORDS][MAX_WORD_LEN];

	// key = ftok("./keyfile", 'R');
	// printf("13: %s\n", strerror(errno));
	shmid = shmget(DICT_ARR_KEY, NUM_WORDS*MAX_WORD_LEN*sizeof(char), 0644 | IPC_CREAT);
	// printf("15: %d \n",shmid);
	data = shmat(shmid, (void *)0, 0);
	// printf("17\n");


	int fd = open(DICT_FILENAME, O_RDONLY);

	FILE * fp = fdopen(fd, "r");

	char word[MAX_WORD_LEN];

	int index = 0;

	while(fgets(word,MAX_WORD_LEN,fp)) {
		word[strlen(word) - 1]=0;
		strncpy((*data)[index],word,MAX_WORD_LEN);
		printf("%s\n", word);
		index++;
	}

	// char userinput[256];
	
	// printf("Do you want to delete the data?\n");
	// fgets(userinput, 256, stdin);
	// if(!strncmp(userinput,"yes",3)) {
	// 	shmdt(data);
	// 	shmctl(shmid, IPC_RMID, NULL);
	// }



	return 0;
}

