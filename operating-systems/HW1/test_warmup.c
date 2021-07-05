// Ross Rucho
// 09/01/2019
// COMP 530 HW1
// This program reads in 80 character line strings from an input and modifies
// them according to specific rules before printing them out

/*
 Honor Pledge

 On my honor, I pledge that I have neither given nor received aid on this assignment.

 Ross Rucho
 */

// Collaborated with jmoore98 while testing program behavior with test cases

#include <stdio.h>

// Generates output streams of 80 characters in length
void generateOutput()
{
  // Declare Variables
  char output[81];  // Length of 81 to include the newline
  int currentChar, ind=0;

  // Loop to continuously read single characters from stdin
  do {
    currentChar = getchar();

    // Evaluates if the end of file has been reached
    if (feof(stdin) || ferror(stdin))
    {
      // End of file is reached while a full line is ready to print
      if (ind==80) {
        output[ind]=10;  // New line character has decimal value 10 in ASCII table

        // Loop through the output and print the 80 character line
        for (int i=0; i<=80; i++) {
          putchar(output[i]);
        }
      }
      break;
    }

    // Evaluates the newline rule
    if (currentChar==10)  // New line character has decimal value 10 in ASCII table
    {
      currentChar=32;
    }

    // Evaluates the adjacent asterisks rule
    if (currentChar==42 && output[ind-1]==42)  // * character has decimal value 42 in ASCII table
    {
      currentChar=94;  // ^ character has decimal value 94 in ASCII table
      ind--;
    }

    // Evaluates the 80 character length rule
    if (ind==80)
    {
      output[ind]=10;  // New line character has decimal value 10 in ASCII table

      // Loop through the output and print the 80 character line
      for (int i=0; i<=80; i++) {
        putchar(output[i]);
      }

      // Place current character and reset index
      output[0]=currentChar;
      ind=1;

    }else {
      // Add the correct character to the array of 80 characters
      output[ind]=currentChar;
      ind++;
    }

  } while(currentChar!=EOF);
}

int main(int argc, char ** argv)
{
  generateOutput();
  return 0;
}
