/*
Ross Rucho
09/18/2019
COMP 530 HW2 530shell.c

This program implements a simple Linux shell as specified in the COMP 530 homework 2 write-up

Honor Pledge

On my honor, I pledge that I have neither given nor received aid on this assignment.

Ross Rucho
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_LIMIT 10000  // Arbitrary buffer limit of 10000 characters
#define ARGUMENT_LIMIT 10000 // Arbitrary argument limit of 10000 arguments

// Declare Variables
char input[BUFFER_LIMIT+1];  // Input buffer of BUFFER_LIMIT characters plus the final null terminator

// This function processes and formats an input stream of characters
int getCommand()
{
  // Declare Variables
  char currentChar;
  int ind=0, args=-1;

  // Continuously read single characters from stdin
  do {
    // Acquire current character
    currentChar = getchar();

    // Conditional logic to process the input string into a command and arguments
    if (currentChar!=EOF && currentChar!='	' && currentChar!=' ' && currentChar!='\n' && ind!=BUFFER_LIMIT) {  // The current character is not the end of file or a whitespace
      // Append current character onto the input buffer                                                                character or a newline character and the input buffer is not full
      input[ind] = currentChar;
      ind++;
    } else if((currentChar=='	' || currentChar==' ') && ind!=0 && input[ind-1]!='\0') {  // The current character is a whitespace character
      // Convert the first whitespace character after a token to the null                  the input buffer is not empty and the previous
      // terminator (the token is either the command or one of its arguments)              character is not the null terminator
      input[ind]='\0';
      args++;
      ind++;
    } else if(currentChar=='\n') {  // The current character is a newline
      //  Variable execution for the newline character
      if(ind==0) {  // The input buffer is empty
        // Append the null terminator to the input buffer
        input[ind]='\0';
      } else if(input[ind-1]!='\0') {  // The previous character is not a null terminator
        // Place a null terminator to signify the end of the final token
        input[ind]='\0';
        args++;
      }
    } else if(ind==BUFFER_LIMIT) {  // Evaluates the arbitrary character limit on the input buffer
      // Place a null terminator to signify the end of the input buffer
      input[ind]='\0';
    } else if(currentChar==EOF) {  // The current character is the end of file character
      // Terminate the beginning of the input buffer with the EOF
      input[0]=EOF;
    }
  } while(ind<BUFFER_LIMIT && currentChar!=EOF && currentChar!='\n');

  // Return the number of arguments
  return args;
}

int main(int argc, char ** argv)
{
  // Declare Variables
  char *file;  //  Pointer to command to be executed
  char *arguments[ARGUMENT_LIMIT];  // Array of pointers to the command arguments
  int active = 1, count, ind, args;
  pid_t pid;

  // Loop to acquire and execute commands
  while(active) {
    // Initialize Variables
    file = NULL;  // file needs to be a NULL pointer if no input is given
    for(int i = 0; i<ARGUMENT_LIMIT; i++) {  // Every pointer in arguments needs to be a null pointer
      arguments[i] = NULL;
    }

    // Start every command prompt line with the string "% "
    printf("%% ");

    // Wait for user to enter a command
    args = getCommand();

    // Ensure that a command has been entered
    if(input[0]!='\0' && input[0]!=EOF) {
      // Define local variables
      ind = 0;
      count = 1;
      file = input;  // Assign the command pointer to be the first token in the input buffer
      arguments[0] = input;  // Assign the first argument pointer to be the first token in the input buffer

      // Loop through input buffer until the command and arguments have been read
      while(count <= args) {
        if(input[ind]=='\0') {
          //  Assign the next argument pointer to be the next token in the input buffer
          arguments[count] = &input[ind+1];
          count++;
        }
        ind++;
      }
    }

    // Create a child process to execute the command or quit if EOF is reached
    if (file!=NULL) {
      pid = fork();

      // Conditional logic to control the execution of both parent and child
      if (pid < 0) {  // An error has occurred with system call fork()
        fprintf(stderr, "Fork system call has failed\n");
        active = 0;
      } else if (pid == 0) { // Child process execution
        // Child process execs the command
        execvp(file, arguments);

        // The only way to reach this code is if exec fails
        // Child process acknowledges error and returns control to parent
        fprintf(stderr, "Exec failed. Returning execution to parent\n");
        active = 0;

      } else { // Parent process execution
        // Wait until child terminates
        wait(NULL);
      }
    }else {
      if(input[0]==EOF) {  // Terminate execution because the EOF has been received
        active = 0;
      }
    }
  }

  return 0;
}
