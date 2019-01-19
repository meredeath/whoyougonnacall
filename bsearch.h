#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#ifndef BSEARCH_H
#define BSEARCH_H

int binsearch(char * your_word);
int wordlen(char * word);

#endif
