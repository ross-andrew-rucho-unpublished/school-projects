/*
Ross Rucho
10/30/2019
COMP 530 HW5 HW5server.c

A server program that provides the service of executing commands as part of a distributed
shell system. The server main process accepts an incoming socket connection, uses fork()
to create a child process that will execute a single command from the client. The main
process then loops continuously reading in additional commands until EOF

Overall, this program accepts input strings from its client program, executes the commands
that the input string represents and sends the response string back to the client.

The server has one parameter: the port number that will be used
for the "welcoming" socket where the client makes a connection.

Honor Pledge

On my honor, I pledge that I have neither given nor received aid on this assignment

Ross Rucho
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

#include "Socket.h"

#define MAX_LINE 10000  // Arbitrary limit of 10000 characters
#define MAX_TMP 10000  // Arbitrary limit of 10000 characters
#define ARGUMENT_LIMIT 10000  // Arbitrary argument limit of 10000 arguments

/* variables to hold socket descriptors */
  ServerSocket welcome_socket;
  Socket connect_socket;

void shell_service(void);

int main(int argc, char* argv[])
{
  pid_t spid, term_pid; /* pid_t is typedef for Linux process ID */ 
  int chld_status;
  bool forever = true;

  if (argc < 2)
     {
      printf("No port specified\n");
      return (-1);
     }

  /* create a "welcoming" socket at the specified port */
  welcome_socket = ServerSocket_new(atoi(argv[1]));
  if (welcome_socket < 0)
      {
      printf("Failed new server socket\n");
      return (-1);
     }

  /* accept an incoming client connection; blocks the
  * process until a connection attempt by a client.
  * creates a new data transfer socket.
  */
  connect_socket = ServerSocket_accept(welcome_socket);
  if (connect_socket < 0)
  {
    printf("Failed accept on server socket\n");
    exit (-1);
  }

  // Execute shell service routine and exit
  Socket_close(welcome_socket);
  shell_service();
  Socket_close(connect_socket);
  exit (0);
}

void shell_service(void)
{
  // Declare and define variables
  int ind, currentChar, args, returnChar, count;
  bool forever = true;
  char *command;  // Pointer to command to be executed
  char *arguments[ARGUMENT_LIMIT];  // Array of pointers to the command arguments
  char input[MAX_LINE+1];  // Input buffer of MAX_LINE characters plus the final null terminator
  unsigned char new_line[MAX_LINE];
  unsigned char tmp_name[MAX_TMP];
  unsigned char id_str[MAX_TMP];
  int id, rc, child_status, c, c2;
  pid_t pid, term_pid;
  char eMessage[] = "An error has occurred while executing the command\n";

  while (forever) {  /* actually, until EOF on connect socket */
      /* get a null-terminated string from the client on the data
       * transfer socket up to the maximim input line size.  Continue
       * getting strings from the client until EOF on the socket.
       */

      // Initialize Variables
      command = NULL;
      for(int i=0; i<ARGUMENT_LIMIT; i++) {
        arguments[i] = NULL;
      }

      // Initialize local variables
      ind = 0;
      args = -1;

      // Continuously read single characters from the socket
      do {
        // Acquire current character
        currentChar = Socket_getc(connect_socket);

        // Conditional logic to process the input string into a command and arguments
        if(currentChar!=EOF && currentChar!='	' && currentChar!=' ' && currentChar!='\n' && ind!=MAX_LINE) {  // The current character is not the end of file or a whitespace character
          // Append current character onto the input buffer                                                                             a newline character or a null terminator and the input buffer is not full
          input[ind] = currentChar;
          ind++;
        }else if((currentChar=='	' || currentChar==' ') && ind!=0 && input[ind-1]!='\0') {  // The current character is a whitespace character
          // Convert the first whitespace character after a token to the null                         the input buffer is not empty and the previous
          // terminator (the token is either the command or one of its arguments)                     character is not the null terminator
          input[ind]='\0';
          args++;
          ind++;
        }else if(currentChar=='\n') {  // The current character is a newline
          // Variable execution for the newline character
          if(ind==0) {  // The input buffer is empty
            // Append the null terminator to the input buffer
            input[ind]='\0';
          }else if(input[ind-1]!='\0') {
            // Place a null terminator to signify the end of the final token
            input[ind]='\0';
            args++;
          }
        }else if(ind==MAX_LINE) {  // Evaluates the arbitrary maximum line limit on the input buffer
          // Place a null terminator to signify the end of the input buffer
          input[ind]='\0';
        }else if(currentChar==EOF) {  // The current character is the end of file character
          // Terminate the beginning of the input buffer with the EOF
          printf("Socket_getc EOF or error\n");
          return;  // Assume socket EOF ends service for this client
        }
      }while(ind<MAX_LINE && currentChar!='\n');

      //  Ensure that a command has been entered
      if(input[0]!='\0') {
        // Initialize variables
        ind = 0;
        count = 1;
        command = input;  // Assign the command pointer to be the first token in the input buffer
        arguments[0] = input;  // Assign the first argument pointer to be the first token in the input buffer

        // Loop through input buffer until the command anad arguments have been read
        while(count <= args) {
          if(input[ind]=='\0') {
            // Assign the next argument pointer to be the next token in the input buffer
            arguments[count] = &input[ind+1];
            count++;
          }
          ind++;
        }
      }

      // Variable names for file handles
      FILE *tmpFP;
      FILE *fp;

      // Get the parent process ID and use it to create a file name for the temporary
      // file with the format "tmpxxxxx" where xxxxx is the ID
      id = (int) getpid();
      sprintf(id_str, "%d", id);
      strcpy(tmp_name, "tmp");
      strcat(tmp_name, id_str);

      // Create a child process to execute the command
      if(command!=NULL) {
        pid = fork();

        // Conditional logic to control the execution of both parent and child
        if(pid < 0) {  // An error has occurred with system call fork()
          // Send error message to client
          for(int k=0; k<sizeof(eMessage); k++) {
            c = eMessage[k];
            c2 = Socket_putc(c, connect_socket);
            if(c2==EOF) {
              printf("Socket_putc EOF or error\n");
              return;
            }
          }
          c2 = Socket_putc('\0', connect_socket);
          if(c2==EOF) {
            printf("Socket_putc EOF or error\n");
            return;
          }
        }else if(pid==0) {  // Child process execution
          // Dynamically redirect stdout to the named temporary file for writing
          fp = freopen(tmp_name, "w", stdout);

          // Child process execs the command
          execvp(command, arguments);

          // The only way to reach this code is if exec fails
          // Child process acknowledges error and returns control to parent
          fprintf(stdout, "Exec failed. Returning execution to parent\n");
          forever = false;
        }else {  // Parent process execution
          // Wait until child terminates
          term_pid = waitpid(pid, &child_status, 0);

          if(!WIFEXITED(child_status) || (tmpFP = fopen(tmp_name, "r"))==NULL) {
            for(int k=0; k<sizeof(eMessage); k++) {
              c = eMessage[k];
              c2 = Socket_putc(c, connect_socket);
              if(c2==EOF) {
                printf("Socket_putc EOF or error\n");
                return;
              }
            }
            c2 = Socket_putc('\0', connect_socket);
            if(c2 == EOF) {
              printf("Socket_putc EOF or error\n");
              return;
            }
            exit(-1);
          }

          while(!feof(tmpFP)) {
            // Get line from file
            if(fgets(new_line, sizeof(new_line), tmpFP)==NULL) {
              c2 = Socket_putc('\0', connect_socket);
              if(c2 == EOF) {
                printf("Data transfer termination error\n");
                return;
              }
              break;
            }else {
              // Initialize variables
              count = strlen(new_line);

              // Send new_line back to the client on the data transfer socket
              for(int i = 0; i < count; i++) {
                c = new_line[i];
                c2 = Socket_putc(c, connect_socket);
                if(c2 == EOF) {
                  printf("Socket_putc EOF or error\n");
                  return;  // Assume socket EOF ends service for this client
                }
              }
            }
          }

          // Delete the temporary file
          remove(tmp_name);
        }
      }else {
        c2 = Socket_putc('\0', connect_socket);
        if(c2 == EOF) {
          printf("Socket_putc EOF or error\n");
          return;  // Assume socket EOF ends service for this client
        }
      }

    } /* end while loop of the service process */

  return;
}
