/*
Ross Rucho
10/04/2019
COMP 530 HW3 HW3.c

This program is an implementation of homework 1 using threads

Honor Pledge

On my honor, I pledge that I have neither given nor received aid on this assignment.

Ross Rucho
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"

#define OUTPUT_SIZE 80

// Declare bounded buffers
struct boundedBuffer buffer12;
struct boundedBuffer buffer23;
struct boundedBuffer buffer34;

// Thread1 consumes characters from stdin and produces characters for buffer12
void *inputThread(void *arg)
{
  // Declare local variables
  char currentChar;

  // Loop to continuously read characters from stdin
  do
  {
    // Consume a character
    currentChar = getchar();

    // Produce a character
    deposit(&buffer12, currentChar);

  }while(currentChar!=EOF);
}

// Thread2 consumes characters from buffer12 and produces characters for buffer23
void *returnThread(void *arg)
{
  // Declare local variables
  char currentChar;

  // Loop to continuously process characters from thread1
  while(currentChar!=EOF)
  {
    // Consume a character
    currentChar = remoove(&buffer12);

    // Converts newline characters to space characters
    if(currentChar=='\n')
    {
      currentChar = ' ';
    }

    // Produce a character
    deposit(&buffer23, currentChar);
  }
}

// Thread3 consumes characters from buffer23 and produces characters for buffer34
void *asteriskThread(void *arg)
{
  // Declare local variables
  char currentChar;
  char internalBuffer;

  // Initialize the internal buffer
  internalBuffer = remoove(&buffer23);

  // Loop to continuously process characters from thread2
  while(internalBuffer!=EOF)
  {
    // Consume a character
    currentChar = remoove(&buffer23);

    // Converts back to back asterisks into carrot symbols
    if(internalBuffer=='*' && currentChar=='*')
    {
      internalBuffer='^';
      currentChar = remoove(&buffer23);
    }

    // Produce a character
    deposit(&buffer34, internalBuffer);
    internalBuffer = currentChar;
  }

  // Propagate the EOF
  deposit(&buffer34, internalBuffer);
}

// Thread4 consumes characters from buffer34 and produces characters for stdout
void *outputThread(void *arg)
{
  // Declare local variables
  char currentChar;
  char internalBuffer[OUTPUT_SIZE];
  int ind=0;

  // Consume a character
  currentChar = remoove(&buffer34);

  // Loop to continuously output characters from thread3
  while(currentChar!=EOF)
  {
    // Update internal buffer
    internalBuffer[ind]=currentChar;
    ind++;

    // Determine when the internal buffer has 80 characters
    if(ind == OUTPUT_SIZE)
    {
      // Produce output
      for(int i=0; i<OUTPUT_SIZE; i++)
      {
        putchar(internalBuffer[i]);
      }

      // Terminate output with a newline and reset internal buffer
      putchar('\n');
      ind=0;
    }

    // Consume a character
    currentChar = remoove(&buffer34);
  }
}

int main(int argc, char ** argv)
{
  // Define bounded buffers
  buffer12 = *boundedBufferInit();
  buffer23 = *boundedBufferInit();
  buffer34 = *boundedBufferInit();

  // Define threads
  pthread_t thread1, thread2, thread3, thread4;

  // Create threads
  pthread_create(&thread1, NULL, inputThread, NULL);
  pthread_create(&thread2, NULL, returnThread, NULL);
  pthread_create(&thread3, NULL, asteriskThread, NULL);
  pthread_create(&thread4, NULL, outputThread, NULL);

  // Join threads upon program termination
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  pthread_join(thread4, NULL);

  // Terminate semaphores
  sem_destroy(&(buffer12.fullBuffers));
  sem_destroy(&(buffer12.emptyBuffers));
  sem_destroy(&(buffer23.fullBuffers));
  sem_destroy(&(buffer23.emptyBuffers));
  sem_destroy(&(buffer34.fullBuffers));
  sem_destroy(&(buffer34.emptyBuffers));

  return 0;
}
