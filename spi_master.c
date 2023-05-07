#define F_CPU 160000000UL
#include<avr/io.h>
#include<util/delay.h>
#define MISO DDRB3
#define MOSI DDRB2
#define SCK DDRB1
#define SS DDRB0
void spiInit(void)
{
    DDRB |=(1<<MOSI)|(1<<SCK)|(1<<SS);
    DDRB &= ~(1<<MISO);
    PORTB |=(1<<SS);
    SPCR |=(1<<SPE)|(1<<MSTR)|(1<<SPR0);
    SPCR &=~(1<<SPI2X);
}

void spiWrite(char data)
{
    char flush_buffer;
	SPDR = data;			
	while(!(SPSR & (1<<SPIF)));
	flush_buffer = SPDR; //to clear SPIF flag
}

int main(void)
{
    uint8_t count = 0;
    while(1)
    {
        spiWrite(count);
        count++;
        _delay_ms(500);
    }
}
