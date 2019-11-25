/*
 * error_handling.h
 *
 *  Created on: Nov 24, 2019
 *      Author: nidal
 */

#ifndef ERROR_HANDLING_H_
#define ERROR_HANDLING_H_

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

void die(char * msg)
{
	char error_message[100];
	strcpy(error_message,"[!!] Fatal Error ");
	strcat(error_message,msg);
	perror(error_message);
	exit(1); //EXIT_FAILURE
}

//Eror check memory allocation.
void *ec_malloc(unsigned int size)
{
	void *ptr;
	ptr = malloc(size);
	if (ptr == NULL) die("memory allocation.");	//Die in peace.
	return ptr;
}


void dump(const unsigned char *data_buffer, const unsigned int length)
{
  unsigned char byte;
  unsigned int i, j;
  for(i=0; i < length; i++)
    {
      byte = data_buffer[i];
      printf("%02x ", data_buffer[i]);  // Display byte in hex.
      if(((i%16)==15) || (i==length-1))
        {
          for(j=0; j < 15-(i%16); j++) printf("   ");
          printf("| ");
          for(j=(i-(i%16)); j <= i; j++)
            {  // Display printable bytes from line.
              byte = data_buffer[j];
              if((byte > 31) && (byte < 127)) // Outside printable char range
              printf("%c", byte);
              else printf(".");
            }
            printf("\n"); // End of the dump line (each line is 16 bytes)
         } // End if
     } // End for
}

#endif /* ERROR_HANDLING_H_ */
