/*
 * usart_private_regs.h
 *
 * Created: 5/1/2023 7:33:49 AM
 *  Author: Mohamed Abdel-Wahab
 *	EMAIL : mohamedhegay22@gmail.com
 */ 


#ifndef USART_PRIVATE_REGS_H_
#define USART_PRIVATE_REGS_H_


/* ------------------------------------------------------- Includes ---------------------------------------------------------------------*/
#include "../../STD_LIBRARIES/STD_TYPES.h"
#include "../../STD_LIBRARIES/bit_math.h"


/* ------------------------------------------------------ Macro Declarations ------------------------------------------------------------*/

/************************************************************************/
/* MAPING OF USART REGISTERS                                            */
/************************************************************************/


/* USART I/O Data Register*/
#ifndef UDR
#define UDR   (*(volatile uint8_t*)0x2C)
#endif 

/* USART Control and Status Register A*/
#ifndef UCSRA
#define UCSRA   (*(volatile uint8_t*)0x2B)


/* USART Control and Status Register B*/
#ifndef UCSRB
#define UCSRB   (*(volatile uint8_t*)0x2A)
#endif

/* USART Control and Status Register C*/
#ifndef UCSRC
#define UCSRC   (*(volatile uint8_t*)0x40)
#endif

/* USART Baud Rate Low Register*/
#ifndef UBRRL
#define UBRRL   (*(volatile uint8_t*)0x29)
#endif

/* USART Baud Rate High Register*/
#ifndef UBRRH
#define UBRRH   (*(volatile uint8_t*)0x40)
#endif

/************************************************************************/
/* DEFING THE USART REGISTERS BITS                                      */
/************************************************************************/

/*UCSRA – USART Control and Status Register A BITS*/

/*Bit 7 – RXC: USART Receive Complete*/
#ifndef RXC
#define RXC  (7u)
#endif

/*Bit 6 – TXC: USART Transmit Complete*/
#ifndef TXC
#define TXC  (6u)
#endif

/*Bit 5 – UDRE: USART Data Register Empty*/
#ifndef UDRE
#define UDRE  (5u)
#endif

/*Bit 4 – FE: Frame Error*/
#ifndef FE
#define FE  (4u)
#endif

/*Bit 3 – DOR: Data OverRunr*/
#ifndef DOR
#define DOR	  (3u)
#endif

/*Bit 2 – PE: Parity Error*/
#ifndef PE
#define PE	  (2u)
#endif

/*Bit 1 – U2X: Double the USART Transmission Speed*/
#ifndef U2X
#define U2X	  (1u)
#endif

/*Bit 0 – MPCM: Multi-processor Communication Mode*/
#ifndef MPCM
#define MPCM	  (0u)
#endif


/*UCSRA – USART Control and Status Register B BITS*/

/*Bit 7 – RXCIE: RX Complete Interrupt Enable*/
#ifndef RXCIE
#define RXCIE  (7u)
#endif

/* Bit 6 – TXCIE: TX Complete Interrupt Enable*/
#ifndef TXCIE
#define TXCIE  (6u)
#endif

/*Bit 5 – UDRIE: USART Data Register Empty Interrupt Enable*/
#ifndef UDRIE
#define UDRIE  (5u)
#endif

/*Bit 4 – RXEN: Receiver Enable*/
#ifndef RXEN
#define RXEN  (4u)
#endif

/* Bit 3 – TXEN: Transmitter Enable*/
#ifndef TXEN
#define TXEN	  (3u)
#endif

/*Bit 2 – UCSZ2: Character Size*/
#ifndef UCSZ2
#define UCSZ2	  (2u)
#endif

/*Bit 1 – RXB8: Receive Data Bit 8*/
#ifndef RXB8
#define RXB8	  (1u)
#endif

/*Bit 0 – TXB8: Transmit Data Bit 8*/
#ifndef TXB8
#define TXB8	  (0u)
#endif


/*UCSRA – USART Control and Status Register C BITS*/

/*Bit 7 – URSEL: Register Select*/
#ifndef URSEL
#define URSEL  (7u)
#endif

/* Bit 6 – UMSEL: USART Mode Select*/
#ifndef UMSEL
#define UMSEL  (6u)
#endif

/*Bit 5:4 – UPM1:0: Parity Mode*/
#ifndef UPM1
#define UPM1  (5u)
#endif
#ifndef UPM0
#define UPM0  (4u)
#endif


/* Bit 3 – USBS: Stop Bit Select*/
#ifndef USBS
#define USBS	  (3u)
#endif

/*Bit 2:1 – UCSZ1:0: Character Size*/
#ifndef UCSZ1
#define UCSZ1	  (2u)
#endif
#ifndef UCSZ0
#define UCSZ0	  (1u)
#endif

/* Bit 0 – UCPOL: Clock Polarity*/
#ifndef UCPOL
#define UCPOL	  (0u)
#endif

/************************************************************************/
/*USART INTERRUPT VECTORS                                               */
/************************************************************************/

/* USART, Rx Complete */
#define USART_RXC_vect_num		13
#define USART_RXC_vect			__vector_13
#define SIG_USART_RECV			__vector_13
#define SIG_UART_RECV			__vector_13

/* USART Data Register Empty */
#define USART_UDRE_vect_num		14
#define USART_UDRE_vect			__vector_14
#define SIG_USART_DATA			__vector_14
#define SIG_UART_DATA			__vector_14
/* USART, Tx Complete */
#define USART_TXC_vect            __vector_15
#define USART_TXC_vect_num        15

#ifndef ISR
#define ISR(INT_VECT) void INT_VECT(void) __attribute__((signal,used));\
void INT_VECT(void)
#endif




#endif



#endif /* USART_PRIVATE_REGS_H_ */