#ifndef BUZZER_H_
#define BUZZER_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define C0   110  //  0
#define C1   123  //  1
#define C2   131  //  2
#define C3   147  //  3
#define C4   165  //  4
#define C5   175  //  5
#define C6   185  //  6
#define C7   196  //  7
#define C8   208  //  8
#define C9   220  //  9
#define C_STAR  100 //  *
#define C_HASH  105 //  #

#define DEFAULT_VOLUME 100

void InitMusic();
void ExitMusic();
void PlayTone(uint16_t frequency);
void PlaySound(char key);
void AccessSound();
void LockSound();
void DeniedSound();
void AlarmSound();

#endif /* BUZZER_H_ */