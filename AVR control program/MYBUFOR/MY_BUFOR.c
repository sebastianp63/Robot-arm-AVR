/*
 * MY_BUFOR.c
 *
 *  Created on: 2 lut 2017
 *      Author: Seba
 */



#include<avr/io.h>
#include<avr/interrupt.h>

#include "MY_BUFOR.h"

void uartInit( uint16_t ubrr){

	UBRRH = (uint8_t)(ubrr>>8);
	UBRRL =(uint8_t) ubrr;

	UCSRB = (1<<TXEN)|(1<<RXEN);
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
	UCSRB |= (1<<RXCIE)|(1<<RXEN)|(1<<TXEN);
}

//definiujemy funkcj� pobieraj�c� jeden bajt z bufora cyklicznego
char uartGet(void) {
	if ( UART_RxHead == UART_RxTail ) return 0; //sprawdzamy czy indeksy s� r�wne

	// obliczamy i zapamietujemy nowy indeks
	UART_RxTail = (UART_RxTail + 1) & UART_RX_BUF_MASK;
	// zwracamy bajt pobierany z bufora jako rezultat funkcji
	return UART_RxBuf[UART_RxTail];
}


// definiujemy funkcj� dodaj�c� jeden bajtdoz bufora cyklicznego
void uart_putc( char data ) {
	uint8_t tmp_head;

    tmp_head  = (UART_TxHead + 1) & UART_TX_BUF_MASK;

          // p�tla oczekuje je�eli brak miejsca w buforze cyklicznym na kolejne znaki
    while ( tmp_head == UART_TxTail ){}

    UART_TxBuf[tmp_head] = data;
    UART_TxHead = tmp_head;

    // inicjalizujemy przerwanie wyst�puj�ce, gdy bufor jest pusty, dzi�ki
    // czemu w dalszej cz�ci wysy�aniem danych zajmie si� ju� procedura
    // obs�ugi przerwania
    UCSRB |= (1<<UDRIE);
}

// wysy�anie pojedy�czych znak�w
void uartPutc( char data ) {
		while ( !( UCSRA & (1<<UDRE)) );
		UDR = data;
	}

char * uartGetString( char * buf, int maxSize ){

	char character;
	int index=0;
	do{
		character = uartGet();

			if(character == 13) break;
			else { if(character >= 31 ){buf[index++]=character;} }
			if(index>maxSize) break;

	}while(character);

	buf[index++] = 0;

	return buf;
}

void uart_puts( char *s ){
	while(*s) uart_putc(*s++);
}


ISR (USART_RXC_vect) {
	uint8_t tmp_head;
	char data;

	data = UDR; // pobieramy bajt danych z bufora
	tmp_head = (UART_RxHead + 1) & UART_RX_BUF_MASK; // obliczanie nowego indeksu

	// sprawdzenie czybufor sie przepe�ni�
	if ( tmp_head == UART_RxTail) {}
	else {
	UART_RxHead = tmp_head; // zapamietanie indeksu
		UART_RxBuf[tmp_head] = data; // wpisanie nowych danych do bufora
	}
}

ISR( USART_UDRE_vect)  {
    // sprawdzamy czy indeksy s� r�ne
    if ( UART_TxHead != UART_TxTail ) {
    	// obliczamy i zapami�tujemy nowy indeks ogona w�a (mo�e si� zr�wna� z g�ow�)
    	UART_TxTail = (UART_TxTail + 1) & UART_TX_BUF_MASK;



    	// zwracamy bajt pobrany z bufora  jako rezultat funkcji
    	UDR = UART_TxBuf[UART_TxTail];
    } else {
	// zerujemy flag� przerwania wyst�puj�cego gdy bufor pusty
	UCSRB &= ~(1<<UDRIE);
    }
}
