/******************************************************************/
/* serial.c   Dr. Juan Gonzalez Gomez. January, 2009              */
/*----------------------------------------------------------------*/
/* Serial communications in Linux                                 */
/*----------------------------------------------------------------*/
/* GPL LICENSE                                                    */
/******************************************************************/

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "bzfunctions.h"

/******************************************************************************/
/* Open the serial port                                                       */
/*----------------------------------------------------------------------------*/
/* INPUT:                                                                     */
/*   -serial_name: Serial device name                                         */
/*   -baud: Serial speed. The constants Bxxxx are used, were xxxx  is the     */ 
/*          speed. They are defined in termios.h. For example: B9600, B19200..*/
/*          For more information type "man termios"                           */
/*                                                                            */
/* RETURNS:                                                                   */
/*   -The Serial device descriptor  (-1 if there is an error)                 */
/******************************************************************************/

int check_message(char message[MAX_MESSAGE_LENGTH])
{
  int msgLength=0;      //-- Length of the message
  int i;
  
  msgLength = strlen(message);            //Calculate length
  //if (debug == ON) printf("message: %s, %d\n\r", message, msgLength);   //print it
  //Check starting byte
  if(message[0] != MessageFirstByte) {
    printf ("Error, header byte incorrect %c\n\r", message[1]);
    return -1;
  }
  //Check last byte
  if(message[msgLength-1] != MessageLastByte) {
    printf ("Error, last byte incorrect\n\r");
    return -1;
  }
  //Check message payload is hex
  for(i=1;i<msgLength-1;i++){
    if(!isxdigit(message[i])) {
      printf ("Error, digit not in hex format\n\r");
      perror("INPUT");
      return -1;
    }
  }
  //if (debug == ON) printf( "Input is hex\n" );
  //if (debug == ON) printf("message: %s\n\r", message);
  return 0;
}




