/*
Ross Rucho
10/16/2019
COMP 530 HW4 HW4.c

This program is an implementation of homework 1 using message passing (Linux pipes) and processes

Honor Pledge

On my honor, I pledge that I have neither given nor received aid on this assignment.

Ross Rucho
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define OUTPUT_SIZE 80

int main(int argc, char ** argv)
{
  // Declare pipes
  int pipe12[2], pipe23[2], pipe34[2];

  // Create pipes
  if(pipe(pipe12) == -1 || pipe(pipe23) == -1 || pipe(pipe34) == -1) {
    fprintf(stderr, "Creation of at least one pipe has failed\n");
    return 1;
  }

  // Declare processes
  pid_t pid1;
  pid_t pid2;
  pid_t pid3;

  // Create a child process to execute the first stage of the pipeline
  pid1 = fork();

  // Separates the execution for the parent and child 1
  if(pid1 > 0) {  // Parent process execution
    // Create a child process to execute the second stage of the pipeline
    pid2 = fork();

    // Separates the execution for the parent and child 2
    if(pid2 > 0) {  // Parent process execution
      // Create a child process to execute the third stage of the pipeline
      pid3 = fork();

      // Separates the execution for the parent and child 3
      if(pid3 > 0) {  // Parent process execution to produce characters for stdout
        // Close pipes that will not be used
        close(pipe12[0]);
        close(pipe12[1]);
        close(pipe23[0]);
        close(pipe23[1]);
        close(pipe34[1]);

        // Declare local variables
        char currentChar;
        char internalBuffer[OUTPUT_SIZE];
        int ind=0;

        // Consume a character
        read(pipe34[0], &currentChar, sizeof(char));

        // Loop to continuously output character from child 3
        while(currentChar!=EOF) {
          // Update internal buffer
          internalBuffer[ind] = currentChar;
          ind++;

          // Determine when the internal buffer has 80 characters
          if(ind == OUTPUT_SIZE) {
            // Produce output
            for(int i=0; i<OUTPUT_SIZE; i++) {
              putchar(internalBuffer[i]);
            }

            // Terminate output with a newline and reset internal buffer
            putchar('\n');
            ind = 0;
          }

          // Consume a character
          read(pipe34[0], &currentChar, sizeof(char));
        }

        // Wait until child processes terminate
        wait(NULL);
        wait(NULL);
        wait(NULL);

      }else if(pid3==0) {  // Child 3 process execution to produce characters for parent process
        // Close pipes that will not be used
        close(pipe12[0]);
        close(pipe12[1]);
        close(pipe23[1]);
        close(pipe34[0]);

        // Declare local variables
        char currentChar;
        char internalBuffer;

        // Initialize the internal buffer
        read(pipe23[0], &internalBuffer, sizeof(char));

        // Loop to continuously process characters from child 2
        while(internalBuffer!=EOF) {
          // Consume a character
          read(pipe23[0], &currentChar, sizeof(char));

          // Converts back to back asterisks into carrot symbols
          if(internalBuffer=='*' && currentChar=='*') {
            internalBuffer = '^';
            read(pipe23[0], &currentChar, sizeof(char));
          }

          // Produce a character
          write(pipe34[1], &internalBuffer, sizeof(char));
          internalBuffer = currentChar;
        }

        // Propagate the EOF
        write(pipe34[1], &internalBuffer, sizeof(char));
      }else {  // An error has occurred with the system call fork() for child 3
        fprintf(stderr, "Fork system call has failed for child 3\n");
        return 1;
      }
    }else if(pid2==0) {  // Child 2 process execution to produce characters for child 3
      // Close pipes that will not be used
      close(pipe12[1]);
      close(pipe23[0]);
      close(pipe34[0]);
      close(pipe34[1]);

      // Declare local variables
      char currentChar;

      // Loop to continuously process characters from child 1
      while(currentChar!=EOF) {
        // Consume a character
        read(pipe12[0], &currentChar, sizeof(char));

        // Converts newline characters to space characters
        if(currentChar=='\n') {
          currentChar = ' ';
        }

        // Produce a character
        write(pipe23[1], &currentChar, sizeof(char));
      }
    }else {  // An error has occurred with the system call fork() for child 2
      fprintf(stderr, "Fork system call has failed for child 2\n");
      return 1;
    }
  }else if(pid1==0) {  // Child 1 process execution to produce characters for child 2
    // Close pipes that will not be used
    close(pipe12[0]);
    close(pipe23[0]);
    close(pipe23[1]);
    close(pipe34[0]);
    close(pipe34[1]);

    // Declare local variables
    char currentChar;

    // Loop to continuously read characters from stdin
    do {
      // Consume a character
      currentChar = getchar();

      // Produce a character
      write(pipe12[1], &currentChar, sizeof(char));
    }while(currentChar!=EOF);
  }else {  // An error has occurred with the system call fork() for child 1
    fprintf(stderr, "Fork system call has failed for child 1\n");
    return 1;
  }

  return 0;
}
