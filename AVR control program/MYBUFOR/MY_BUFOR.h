/*
 * MY_BUFOR.h
 *
 *  Created on: 2 lut 2017
 *      Author: Seba
 */

#ifndef MYBUFOR_MY_BUFOR_H_
#define MYBUFOR_MY_BUFOR_H_

#define UART_BAUD 9600
#define __UBRR ((F_CPU+UART_BAUD*8UL) / (16UL*UART_BAUD)-1)

#define UART_RX_BUF_SIZE 16 // definiujemy bufor o rozmiarze 32 bajtów
#define UART_RX_BUF_MASK (UART_RX_BUF_SIZE-1) // definiujemy maskê dla bufora

#define UART_TX_BUF_SIZE 16 // definiujemy bufor o rozmiarze 16 bajtów
// definiujemy maskê dla naszego bufora
#define UART_TX_BUF_MASK ( UART_TX_BUF_SIZE - 1)

volatile char UART_RxBuf[UART_RX_BUF_SIZE]; // definiujemy bufor

volatile char UART_TxBuf[UART_TX_BUF_SIZE];

volatile uint8_t UART_RxHead;
volatile uint8_t UART_RxTail;

volatile uint8_t UART_TxHead; // indeks oznaczaj¹cy „g³owê wê¿a”
volatile uint8_t UART_TxTail; // indeks oznaczaj¹cy „ogon wê¿a”

void uartInit( uint16_t ubrr);
char uartGet(void);
void uartPutc( char data );
void uart_putc( char data );
void uart_puts( char *s );
char * uartGetString( char * buf, int maxSize );

#endif /* MYBUFOR_MY_BUFOR_H_ */
