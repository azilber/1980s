// ********************** START OF BOCA.H **********************
//
//
// This header file has all of the definitions and prototypes
// needed to use the BocaHandler class.


#ifndef _BOCA_DOT_H
#define _BOCA_DOT_H

#include "rs232.h"
#include "pc8250.h"

struct boca_data {
    int status_register;
    struct isr_data_block *data_pointers[ 8 ];
};

class BocaHandler : public Handler {
    private :
        struct boca_data isr_info;
        irq_name irq;
        RS232Error connected;
    public :
        BocaHandler( irq_name irq_line,
                     int status_register_address );
        ~BocaHandler( void );
        virtual RS232Error AddPort( RS232PortName port_name,
                                    struct isr_data_block *data );
        virtual void DeletePort( RS232PortName port_name );
};

#endif // #ifndef _BOCA_DOT_H

// ************************ END OF BOCA.H ***********************

