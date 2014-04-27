// ******************** START OF TEST232.CPP ********************
//
//
//
// This test program is used to test various RS232 classes.
//

#include "portable.h"
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "rs232.h"
#include "textwind.h"
#include "biosport.h"
#include "fossil.h"

// The window count can range from 1 to 4.  The window_parms array will
// be modified depending on the value of WINDOW_COUNT.

#define SPEED 19200

RS232 *Ports[ 4 ] = { 0, 0, 0, 0 };
RS232 *Port = 0;
RS232PortName port_names[ 4 ] = { COM1, COM2, COM3, COM4 };

int main()
{
    int i;
    int c;
    char buffer[ 81 ];

 i=1;
    if ( i == 1 ) {
	switch ( i ) {
	    default :
		Ports[ i ] = new FOSSIL( port_names[ i ],
					SPEED, 'N', 8, 1, 1, 1 );
	}
	if ( Ports[ i ]->ErrorStatus() == RS232_SUCCESS ) {

	      /* Main code in here. */
	    printf("Port opened succesfully!\n");

	  Ports[i]->Write("Port opened succesfully!");
	  Ports[i]->Write("Waiting 5 seconds.!");
	  sleep(5);

	} else {
		printf("Error opening port!\n");

	     exit(1);


	}
    }

   Ports[i]->Write("Removing Port in 1 second.");

 delete Ports[i];

  printf("Removed the port.\n");

}