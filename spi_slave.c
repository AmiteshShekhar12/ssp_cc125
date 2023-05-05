#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define MISO PB3
#define MOSI PB2
#define SCK PB1
#define SS PB0
#define baud 9600
void spiInit()					
{
	DDRB &= ~((1<<MOSI)|(1<<SCK)|(1<<SS));
 						
	DDRB |= (1<<MISO);
						
	SPCR = (1<<SPE);
}

char spiReceive()			
{
	while(!(SPSR & (1<<SPIF)));
	return(SPDR);
}

void configUART()
{
    UCSR0B=(1<<TXEN0);
	UCSR0C=(1<<USBS0)|(3<<UCSZ00);
	uint16_t baud_val = ((F_CPU/(16*baud))-1);
	UBRR0H = (baud_val>>8);
	UBRR0L=baud_val;
}

void UART_Transmit(char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0=data;
}


int main(void)
{
    configUART();
    uint8_t data;
    while(1)
    {
        data = spiReceive();
    }
    UART_Transmit(data); 
}