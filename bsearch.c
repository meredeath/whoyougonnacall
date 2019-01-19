#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#include "dict.h"
#include "bsearch.h"

// finished binary search but still have to change function name
// and return statement
int binsearch(char * your_word)
{
  // key_t key;
  int shmid;
  char (* data)[NUM_WORDS][MAX_WORD_LEN];

  // set up shared memory
  // key = ftok("mykey", 'f');
  shmid = shmget(DICT_ARR_KEY, NUM_WORDS * MAX_WORD_LEN * sizeof(char), 0644 | IPC_CREAT);
  data = shmat(shmid, (void *) 0, SHM_RDONLY);
  /*
  int counter = 81520 - 1;

  while(counter > 80000)
    {
      printf("%s\n", (* data)[counter]);
      counter--;
    }
  */

  int high = NUM_WORDS - 1;
  int low = 0;
  int counter = 0;

  // see if the prefix is valid
  while (low <= high)
    {
      counter++;
      // printf("counter: %d\n", counter);
      char * my_word = (* data)[(int) ((high + low) / 2)];
      
      if (strncmp(my_word, your_word, wordlen(your_word)) > 0)
	{
	  // looking too high
	  printf("At word: [%s], too high\n", my_word);
	  high = (int) ((high + low) / 2 - 1);
	}
      else if (strcmp(my_word, your_word) < 0)
	{
	  // looking too low
	  printf("At word: [%s], too low\n", my_word);
	  low = (int) ((high + low) / 2 + 1);
	}
      else
	{
	  printf("The prefixes are equal this is a valid prefix. %d iterations\n", counter);
	  break;
	}
    }

  if (high < low)
    {
      // prefix does not exist this word is incorrect
      return -1;
    }
  

  high = NUM_WORDS - 1;
  low = 0;
  counter = 0;
  
  while (low <= high)
    {
      counter++;
      // printf("counter: %d\n", counter);
      char * my_word = (* data)[(int) ((high + low) / 2)];
      
      if (strcmp(my_word, your_word) > 0)
	{
	  // looking too high
	  printf("At word: [%s], too high\n", my_word);
	  high = (int) ((high + low) / 2 - 1);
	}
      else if (strcmp(my_word, your_word) < 0)
	{
	  // looking too low
	  printf("At word: [%s], too low\n", my_word);
	  low = (int) ((high + low) / 2 + 1);
	}
      else
	{
	  printf("The two words %s and %s are equal. %d iterations\n", my_word, your_word, counter);
	  return 1;
	}
    }


  
  printf("high: %d; low: %d\n", high, low); 
  return 0;
  
}

int wordlen(char * word)
{
  int counter = 0;
  char myword[100];

  strcpy(myword, word);

  printf("%s\n", myword);
  
  while (myword[counter])
    {
      counter += 1;
      word += 1;
    }

  return counter;
}
