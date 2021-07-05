/*
Ross Rucho
11/20/2019
COMP 530 HW6 buffer.c

This file contains the definitions and implementations for the functions declared in buffer.h
Together, buffer.h and buffer.c define the bounded buffer abstract data type

Note: This version can be shared between processes while the HW3 version can only be shared between threads

Honor Pledge

On my honor, I pledge that I have neither given nor received aid on this assignment.

Ross Rucho
*/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/mman.h>
#include "buffer.h"

// Initializes and returns a boundedBuffer struct
struct boundedBuffer* boundedBufferInit()
{
  // Declare required arguments for using mmap
  void* addr=NULL;  // Kernel is permitted to choose the starting address for the memory map
  int protections = PROT_READ|PROT_WRITE;  // Memory mapped pages can be written and read
  int flags = MAP_SHARED|MAP_ANONYMOUS;  // Memory mapping is shared with other processes and is not backed by a file
  int fd = -1;  // This argument may be ignored because of MAP_ANONYMOUS, but -1 is sometimes required
  off_t offset = 0;  // This argument should be 0 because of MAP_ANONYMOUS

  // Declare and allocate memory for an instance of struct boundedBuffer
  struct boundedBuffer *bBuffer = mmap(addr, BOUND_BUFFER_BYTES, protections, flags, fd, offset);

  // Initialize boundedBuffer members
  sem_init(&(bBuffer->fullBuffers), 1, 0);
  sem_init(&(bBuffer->emptyBuffers), 1, BUFFER_SIZE);
  bBuffer->nextIn = 0;
  bBuffer->nextOut = 0;

  // Returns the initialized struct
  return bBuffer;
}

// Produces a single character for the bounded buffer
void deposit(struct boundedBuffer *boundBuf, char c)
{
  // Decrement the semaphore storing the number of empty buffers
  sem_wait(&((*boundBuf).emptyBuffers));

  // Produce a character for the buffer
  (*boundBuf).buf[(*boundBuf).nextIn] = c;
  (*boundBuf).nextIn = ((*boundBuf).nextIn+1) % BUFFER_SIZE;

  // Increment the semaphore storing the number of full buffers
  sem_post(&((*boundBuf).fullBuffers));
}

// Consumes a single character from the bounded buffer
char remoove(struct boundedBuffer *boundBuf)
{
  // Declare local variables
  char c;  // Character that stores the value of the buffer index

  // Decrement the semaphore storing the number of full buffers
  sem_wait(&((*boundBuf).fullBuffers));

  // Consume a character from the buffer
  c = (*boundBuf).buf[(*boundBuf).nextOut];
  (*boundBuf).nextOut = ((*boundBuf).nextOut+1) % BUFFER_SIZE;

  // Increment the semaphore storing the number of empty buffers
  sem_post(&((*boundBuf).emptyBuffers));

  // Return the removed character
  return c;
}
