#include "Buzzer.h"

void InitMusic()
{
	DDRD |= (1<<DDD4); 
	TCCR1A |= (1<<COM1B1);  
	TCCR1B |= (1<<WGM13) | (1<<CS11); 
}

void ExitMusic()
{
	DDRD &= ~(1 << DDD4);
	TCCR1A &= ~(1<<COM1B1);  
	TCCR1B &= ~((1 << WGM13) | (1 << CS11));
}

void PlayTone(uint16_t frequency)
{
	if (frequency == 0)
	{
		OCR1B = 0; 
	}
	else
	{
		OCR1B = DEFAULT_VOLUME;
		ICR1H = (frequency >> 8); 
		ICR1L = frequency;
	}
}

void PlaySound(char key)
{
	/*
	switch (key)
	{
		case '0': PlayTone(C0); _delay_ms(200); PlayTone(0);  break;
		case '1': PlayTone(C1); _delay_ms(200); PlayTone(0);  break;
		case '2': PlayTone(C2); _delay_ms(200); PlayTone(0);  break;
		case '3': PlayTone(C3); _delay_ms(200); PlayTone(0);  break;
		case '4': PlayTone(C4); _delay_ms(200); PlayTone(0);  break;
		case '5': PlayTone(C5); _delay_ms(200); PlayTone(0);  break;
		case '6': PlayTone(C6); _delay_ms(200); PlayTone(0);  break;
		case '7': PlayTone(C7); _delay_ms(200); PlayTone(0);  break;
		case '8': PlayTone(C8); _delay_ms(200); PlayTone(0);  break;
		case '9': PlayTone(C9); _delay_ms(200); PlayTone(0);  break;
		case '*': PlayTone(C_STAR); _delay_ms(200); PlayTone(0);  break;
		case '#': PlayTone(C_HASH); _delay_ms(200); PlayTone(0);  break;
		default: PlayTone(0); _delay_ms(200); PlayTone(0);  break; 
	}
	*/
	 PlayTone(C_STAR); _delay_ms(200); PlayTone(0);
}

void AccessSound(){
	for (uint8_t i=0;i<2;i++){
		PlayTone(C_STAR); _delay_ms(400); PlayTone(0);_delay_ms(400);
	}
}

void LockSound(){
	for (int i=0;i<500;i++){
		PlayTone(C_STAR); _delay_ms(300); PlayTone(0);_delay_ms(300);
	}
}

void DeniedSound(){
	for (uint8_t i=0;i<3;i++){
		PlayTone(C_STAR); _delay_ms(300); PlayTone(0);_delay_ms(300);
	}
}

void AlarmSound()
{
	for (int i=0;i<50;i++){
		PlayTone(C4); _delay_ms(250); PlayTone(0);_delay_ms(250);
	}
}