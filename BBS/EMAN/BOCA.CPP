// *********************** START OF BOCA.CPP ***********************
//
//

#include <dos.h>
#include "rs232.h"
#include "pc8250.h"
#include "_pc8250.h"
#include "pcirq.h"
#include "boca.h"
#include "_msdos.h"

void boca_isr( struct boca_data *isr_info )
{
    int mask;
    int i;

    STI();
    for ( ; ; ) {
        mask = INPUT( isr_info->status_register );
        if ( ( mask & 0xff ) == 0 )
            break;
        for ( i = 0 ; i < 7 ; i++ ) {
            if ( mask & 1 )
                if ( isr_info->data_pointers[ i ] )
                    isr_8250( isr_info->data_pointers[ i ] );
            mask >>= 1;
        }
    }
}

BocaHandler::BocaHandler( irq_name irq_line,
                          int status_register_address )
{
    int i;

    isr_info.status_register = status_register_address;
    for ( i = 0 ; i < 8 ; i++ )
        isr_info.data_pointers[ i ] = 0;
    irq = irq_line;
    connected = ConnectToIrq( irq,
                              &isr_info,
                              (void (*)( void *)) boca_isr );
}

BocaHandler::~BocaHandler( void )
{
    if ( connected == RS232_SUCCESS )
        DisconnectFromIRQ( irq );
}

RS232Error BocaHandler::AddPort( RS232PortName port_name,
                                 struct isr_data_block *data )
{
    if ( connected != RS232_SUCCESS )
        return connected;
    if ( isr_info.data_pointers[ port_name ] )
        return RS232_PORT_IN_USE;
    isr_info.data_pointers[ port_name ] = data;
    return RS232_SUCCESS;
}

void BocaHandler::DeletePort( RS232PortName port_name )
{
    isr_info.data_pointers[ port_name ] = 0;
}

// *********************** END OF BOCA.CPP ***********************

