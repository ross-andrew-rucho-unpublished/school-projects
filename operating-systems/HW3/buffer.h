/*
Ross Rucho
10/04/2019
COMP 530 HW3 buffer.h

This header file contains declarations and definitions for a bounded buffer abstract data type
Together, buffer.h and buffer.c define the bounded buffer abstract data type

Honor Pledge

On my honor, I pledge that I have neither given nor received aid on this assignment.

Ross Rucho
*/

#ifndef _BUFFER_H
#define _BUFFER_H

#define BUFFER_SIZE 80

#include <semaphore.h>

// Define the bounded buffer data structure
struct boundedBuffer
{
  sem_t fullBuffers;  // Counting semaphore that stores the number of full buffers
  sem_t emptyBuffers;  // Counting semaphore that stores the number of empty buffers
  char buf[BUFFER_SIZE];  // Character array that stores characters that are in the buffer
  int nextIn;  // Integer that stores the index of the next empty buffer
  int nextOut;  // Integer that stores the index of the next full buffer
};

// Initializes and returns a boundedBuffer struct
extern struct boundedBuffer* boundedBufferInit();

// Produces a single character for the bounded buffer
extern void deposit(struct boundedBuffer *boundBuf, char c);

// Consumes a single character from the bounded buffer
extern char remoove(struct boundedBuffer *boundBuf);

#endif
