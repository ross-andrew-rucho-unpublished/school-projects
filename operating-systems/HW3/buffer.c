/*
Ross Rucho
10/04/2019
COMP 530 HW3 buffer.c

This file contains the definitions and implementations for the functions declared in buffer.h
Together, buffer.h and buffer.c define the bounded buffer abstract data type

Honor Pledge

On my honor, I pledge that I have neither given nor received aid on this assignment.

Ross Rucho
*/

#include <stdlib.h>
#include <semaphore.h>
#include <assert.h>
#include "buffer.h"

#define BOUND_BUFFER_BYTES 1000  // 1000 bytes chosen arbitrarily

// Initializes and returns a boundedBuffer struct
struct boundedBuffer* boundedBufferInit()
{
  // Declare and allocate memory for an instance of struct boundedBuffer
  struct boundedBuffer *bBuffer = calloc(1, BOUND_BUFFER_BYTES);

  // Initialize boundedBuffer members
  sem_init(&(bBuffer->fullBuffers), 0, 0);
  sem_init(&(bBuffer->emptyBuffers), 0, BUFFER_SIZE);
  bBuffer->nextIn = 0;
  bBuffer->nextOut = 0;

  // Returns the initialized struct
  return bBuffer;
}

// Produces a single character for the bounded buffer
void deposit(struct boundedBuffer *boundBuf, char c)
{
  // Declare local variables
  int value;  // Integer that stores the value of a semaphore

  // Decrement the semaphore storing the number of empty buffers
  sem_wait(&((*boundBuf).emptyBuffers));

  // The number of empty buffers must be greater than or equal to 0
  //sem_getvalue(&((*boundBuf).emptyBuffers), &value);
  //assert(value >= 0);

  // Produce a character for the buffer
  (*boundBuf).buf[(*boundBuf).nextIn] = c;
  (*boundBuf).nextIn = ((*boundBuf).nextIn+1) % BUFFER_SIZE;

  // Increment the semaphore storing the number of full buffers
  sem_post(&((*boundBuf).fullBuffers));

  // The number of full buffers must be greater than 0
  //sem_getvalue(&((*boundBuf).fullBuffers), &value);
  //assert(value > 0);
}

// Consumes a single character from the bounded buffer
char remoove(struct boundedBuffer *boundBuf)
{
  // Declare local variables
  int value;  // Integer that stores the value of a semaphore
  char c;  // Character that stores the value of the buffer index

  // Decrement the semaphore storing the number of full buffers
  sem_wait(&((*boundBuf).fullBuffers));

  // The number of full buffers must be greater than or equal to 0
  //sem_getvalue(&((*boundBuf).fullBuffers), &value);
  //assert(value >= 0);

  // Consume a character from the buffer
  c = (*boundBuf).buf[(*boundBuf).nextOut];
  (*boundBuf).nextOut = ((*boundBuf).nextOut+1) % BUFFER_SIZE;

  // Increment the semaphore storing the number of empty buffers
  sem_post(&((*boundBuf).emptyBuffers));

  // The number of empty buffers must be greater than 0
  //sem_getvalue(&((*boundBuf).emptyBuffers), &value);
  //assert(value > 0);

  // Return the removed character
  return c;
}
