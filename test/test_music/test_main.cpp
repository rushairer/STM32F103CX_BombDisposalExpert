#include <Arduino.h>
#include <unity.h>
#define BUZZER_PIN PA1
#define NOTE_C4 262
#define NOTE_E4 330
#define NOTE_G4 392
#define NOTE_C5 523
#define NOTE_A4 440
#define NOTE_A3 220

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

int melody[] = {
    NOTE_A3, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_C4};
//    NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_E4, NOTE_C4};

void setup()
{
    pinMode(BUZZER_PIN, OUTPUT);
    for (int i = 0; i < 8; i++)
    {
        int noteDuration = 250;
        tone(BUZZER_PIN, melody[i], noteDuration);
        delay(noteDuration * 1.3); //
        noTone(BUZZER_PIN);
        delay(50);
    }
}

void loop()
{
}