/*
 * main.c
 *
 *  Created on: 18 sty 2017
 *      Author: Seba
 */

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include "MYBUFOR/MY_BUFOR.h"

//makrodefinicja dla potrów sterujacych kirunkiem obrotów silnika
#define DIR1 (1<<PD7)
#define DIR2 (1<<PD6)
#define DIR3 (1<<PD5)
#define DIR4 (1<<PD4)

#define MIN 130     	 // minimalne wychylenie serwa bior¹c poduwage zakres pracy chwytaka
#define MAX 270    		 // maksymalne wychylenie serwa

void servoLeft(); 		 // deklaracja funkcji sterujacej serwem w lewo
void servoRight();		 // deklaracja funkcji sterujacej serwem w prawo

volatile uint8_t pwm1,pwm2,pwm3,pwm4,pwm5,pwm6;
volatile uint16_t freq=300;	// ustawienie licznika dla PWM

int main(void)
{
	uartInit( __UBRR);

	////// *************Inicjalizacja przerwan dla programowego PWM************/////
	TCCR2|=(1<<WGM21);  // ustawienie trybu przerwania CTC
	TCCR2|=(1<<CS21);	// preskaler 8
	TIMSK|=(1<<OCIE2);  // zezwolenie na przerwanie
	OCR2=50;			// 16 000 000 / 8 / 50 = 40 000 kHz
	/* ustawienie portów jako wyjscia dla PWM */
	DDRC|=(1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3)|(1<<PC4)|(1<<PC5);
	/*PORTC|=(1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3)|(1<<PC4)|(1<<PC5);*/
	////// *******************************************************************//////

	//////************** INICALIZACJA PWM DLA SERWA *************************///////
	OCR1A=150; // po³o¿enie pocz¹tkowe serwomechanizmu
	DDRB |= (1 << PB1); // ustawienie sprzêtowego PWM dla portu PB1(0C1A)
	TCCR1A |= (1 << COM1A1); // przy porownaniu licznika z wartoscia OCR1A, stan niski na PB1,
	//tryb pracy Fast PWM (14)
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	TCCR1B |= (1 << CS21) | (1 << CS20); // ustawienie preskalera 32
	//przerwanie co 20ms
	ICR1 = 10000; //  16 000 000 / 32 / 50 Hz = 10 000 (ICR1 =10000)
	//////*******************************************************************///////

	// USATWIENIE WYJSC NA PORCIE D DLA SYNGA£OW STERUJACYCH KIERUNKIEM
	DDRD|=DIR1|DIR2|DIR3|DIR4;
	sei(); // zezwolenie na przerwania

	uint8_t f1=0;
	uint8_t f2=0;
	uint8_t f3=0;


	while(1)
	{
	// Petla switch odbierajaca przesy³ane znaki w celu ustawienia
	// odpowiednich wyjsc pwm dla poszegolnych silników, kierunku obrotu
	// a takze wywo³ania funkcji steruj¹cych serwem
			switch(uartGet())
			{
			case 'w':pwm6=50; pwm5=50; PORTD&=~DIR1; PORTD|=DIR4; uart_puts("UP_1\r\n");  break;
			case 'e':pwm6=50; pwm5=50; PORTD|=DIR1;  PORTD&=~DIR4; uart_puts("DOWN_1\r\n"); break;
			case 'a':pwm4=50; PORTD&=~DIR2; uart_puts("UP_2\r\n"); break;

			case 's':pwm4=50; PORTD|=DIR2; uart_puts("DOWN_2\r\n");  break;
			case 'z':pwm3=50; PORTD&=~DIR3; uart_puts("LEFT\r\n");  break;
			case 'x':pwm3=50; PORTD|=DIR3; uart_puts("RIGHT\r\n");  break;
			case 'j':pwm6=0; pwm5=0; uart_puts("STOP\r\n");break;
			case 'h':pwm3=0; uart_puts("STOP\r\n"); break;
			case 'g':pwm4=0; uart_puts("STOP\r\n"); break;
			case 'l':servoLeft(); uart_puts("OPEN\r\n");  break;
			case 'p':servoRight(); uart_puts("CLOSE\r\n"); break;
			}
	}
}
  // obs³uga przerwania dla PWM
	ISR(TIMER2_COMP_vect)
	{
		static uint16_t ctn; // licznik dla PWM
		// sterowanie wyjsciami
		if(ctn>=pwm1) PORTC|=(1<<PC0); else PORTC&=~(1<<PC0);
		if(ctn>=pwm2) PORTC|=(1<<PC1); else PORTC&=~(1<<PC1);
		if(ctn>=pwm3) PORTC|=(1<<PC2); else PORTC&=~(1<<PC2);
		if(ctn>=pwm4) PORTC|=(1<<PC3); else PORTC&=~(1<<PC3);
		if(ctn>=pwm5) PORTC|=(1<<PC4); else PORTC&=~(1<<PC4);
		if(ctn>=pwm6) PORTC|=(1<<PC5); else PORTC&=~(1<<PC5);
		ctn++; //zwiekszanie licznika
		if(ctn>freq)
			 ctn=0; // zerowanie licznika po przekroczeniu wartosci
	}

	// funckja sterujaca obrotem serwa w lewo
	void servoLeft(){
		{
			OCR1A+=10; // zmiana k¹ta serwa
			if(OCR1A>=MAX)OCR1A=MAX; //ograniczenie ruchu
		}
	}
	// funckja sterujaca obrotem serwa w prawo
	void servoRight(){
		{
			OCR1A-=10; // zmiana k¹ta serwa
			if(OCR1A<=MIN) OCR1A=MIN; //ograniczenie ruchu
		}
	}











