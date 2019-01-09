#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>

#define DICT_ARR_KEY 12358

#define MAX_WORD_LEN 40

#define DICT_FILENAME "dictall.txt"

#define NUM_WORDS 100000

// finished binary search but still have to change function name
// and return statement
int main()
{
  // key_t key;
  int shmid;
  char (* data)[NUM_WORDS][MAX_WORD_LEN];

  // set up shared memory
  // key = ftok("mykey", 'f');
  shmid = shmget(DICT_ARR_KEY, NUM_WORDS * MAX_WORD_LEN * sizeof(char), 0644 | IPC_CREAT);
  data = shmat(shmid, (void *) 0, SHM_RDONLY);

  int high = NUM_WORDS - 1;
  int low = 0;
  int counter = 0;
  
  while (high >= low)
    {
      counter++;
      printf("counter: %d\n", counter);
      char * my_word = (* data)[low + (high - low) / 2];
      char * your_word = "kitty";
      
      if (strcmp(my_word, your_word) == 0)
	{
	  printf("The two words %s and %s are equal. %d iterations\n", my_word, your_word, counter);
	  return 0;
	}
      else if (strcmp(my_word, your_word) < 0)
	{
	  // looking too low
	  low = low + (high - low) / 2 + 1;
	}
      else
	{
	  // looking too high
	  high = low + (high - low) /2 - 1;
	}
    }
  
  printf("high: %d; low: %d\n", high, low); 
}
