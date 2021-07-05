/*
Ross Rucho
11/20/2019
COMP 530 HW6 HW6.c

This program is an implementation of homework 1 using processes and shared memory

Shared memory is implemented using memory mapped files. The function mmap is located in the
corresponding buffer.c file for HW6 and mmap is used exactly like calloc was used in HW3. As
an overview, mmap dedicates a segment of virtual memory and assigns a byte-for-byte correlation
with some portion of a file or a file-like resource.

Source: https://en.wikipedia.org/wiki/Memory-mapped_file

Honor Pledge

On my honor, I pledge that I have neither given nor received aid on this assignment.

Ross Rucho
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <signal.h>
#include "buffer.h"

#define OUTPUT_SIZE 80

// Prototypes for functions related to process creation/maintenance
pid_t forkChild(void (*func)(void*));

// Declare bounded buffer structures
struct boundedBuffer* buffer12;
struct boundedBuffer* buffer23;
struct boundedBuffer* buffer34;

// The first child process consumes characters from stdin and produces characters for buffer12
void inputProcess(void *arg)
{
  // Declare local variables
  char currentChar;

  // Loop to continuously read characters from stdin
  do
  {
    // Consume a character
    currentChar = getchar();

    // Produce a character
    deposit(buffer12, currentChar);

  }while(currentChar!=EOF);

  // Terminate the process
  exit(EXIT_SUCCESS);

  return;
}

// The second child process consumes characters from buffer12 and produces characters for buffer23
void returnProcess(void *arg)
{
  // Declare local variables
  char currentChar;

  // Loop to continuously process characters from thread1
  while(currentChar!=EOF)
  {
    // Consume a character
    currentChar = remoove(buffer12);

    // Converts newline characters to space characters
    if(currentChar=='\n')
    {
      currentChar = ' ';
    }

    // Produce a character
    deposit(buffer23, currentChar);
  }

  // Terminate the process
  exit(EXIT_SUCCESS);

  return;
}

// The third child process consumes characters from buffer23 and produces characters for buffer34
void asteriskProcess(void *arg)
{
  // Declare local variables
  char currentChar;
  char internalBuffer;

  // Initialize the internal buffer
  internalBuffer = remoove(buffer23);

  // Loop to continuously process characters from thread2
  while(internalBuffer!=EOF)
  {
    // Consume a character
    currentChar = remoove(buffer23);

    // Converts back to back asterisks into carrot symbols
    if(internalBuffer=='*' && currentChar=='*')
    {
      internalBuffer='^';
      currentChar = remoove(buffer23);
    }

    // Produce a character
    deposit(buffer34, internalBuffer);
    internalBuffer = currentChar;
  }

  // Propagate the EOF
  deposit(buffer34, internalBuffer);

  // Terminate the process
  exit(EXIT_SUCCESS);

  return;
}

// The fourth child process consumes characters from buffer34 and produces characters for stdout
void outputProcess(void *arg)
{
  // Declare local variables
  char currentChar;
  char internalBuffer[OUTPUT_SIZE];
  int ind=0;

  // Consume a character
  currentChar = remoove(buffer34);

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
    currentChar = remoove(buffer34);
  }

  // Terminate the process
  exit(EXIT_SUCCESS);

  return;
}

int main(int argc, char ** argv)
{
  // Define bounded buffers
  buffer12 = boundedBufferInit();
  buffer23 = boundedBufferInit();
  buffer34 = boundedBufferInit();

  // Define child processes
  pid_t childpids[4];

  // Fork children
  childpids[0] = forkChild(inputProcess);
  childpids[1] = forkChild(returnProcess);
  childpids[2] = forkChild(asteriskProcess);
  childpids[3] = forkChild(outputProcess);

  // Wait for child processes to terminate
  wait(NULL);
  wait(NULL);
  wait(NULL);
  wait(NULL);

  // Terminate semaphores
  sem_destroy(&(buffer12->fullBuffers));
  sem_destroy(&(buffer12->emptyBuffers));
  sem_destroy(&(buffer23->fullBuffers));
  sem_destroy(&(buffer23->emptyBuffers));
  sem_destroy(&(buffer34->fullBuffers));
  sem_destroy(&(buffer34->emptyBuffers));

  // Terminate memory map
  munmap(buffer12, BOUND_BUFFER_BYTES);
  munmap(buffer23, BOUND_BUFFER_BYTES);
  munmap(buffer34, BOUND_BUFFER_BYTES);

  return 0;
}

// This function accepts as input a pointer to a function
// This function returns the pid of the forked process
pid_t forkChild(void (*function)(void*)) {
  // Declare local variables
  pid_t childpid;

  // Fork the child process
  childpid = fork();

  // Variable logic to control process execution
  if(childpid < 0) {
    perror("fork error");
    exit(EXIT_FAILURE);
  }else if(childpid == 0) {
    (*function)(NULL);
  }else {
    return childpid;
  }
}
