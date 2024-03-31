#include <Arduino.h>
#include <TM1638.h> // required because the way arduino deals with libraries
#include <TM1640.h>
#include "BombDisposalExpert.h"

#define ISDEV 1

#define SDA_PIN PB7
#define SCL_PIN PB6

#define BTN1_PIN PB3
#define BTN2_PIN PA15

#define BUZZER_PIN PA1

#define SILENCE_NOTE 31
#define ACTION_NOTE 1175
#define DANGRE_NOTE 1319

#define LINE1_PIN PB12
#define LINE2_PIN PB13
#define LINE3_PIN PB14
#define LINE4_PIN PB15
#define LINE5_PIN PA8

TM1640 module(SDA_PIN, SCL_PIN, 4);

BombDisposalExpert bombDisposalExpert(&module, BUZZER_PIN);

void setup()
{
    pinMode(BTN1_PIN, INPUT_PULLUP);
    pinMode(BTN2_PIN, INPUT_PULLUP);

    pinMode(LINE1_PIN, INPUT_PULLUP);
    pinMode(LINE2_PIN, INPUT_PULLUP);
    pinMode(LINE3_PIN, INPUT_PULLUP);
    pinMode(LINE4_PIN, INPUT_PULLUP);
    pinMode(LINE5_PIN, INPUT_PULLUP);

    bombDisposalExpert.setup();
}

void loop()
{

    bombDisposalExpert.loop();

    if ((digitalRead(BTN1_PIN) == LOW) && (digitalRead(BTN2_PIN) == LOW))
    {
        if (bombDisposalExpert.getStatus() == BOMB_DISPOSAL_EXPERT_STATUS_PLAYING)
        {
            bombDisposalExpert.reset();
            delay(300);
        }
    }
    else
    {
        if (digitalRead(BTN1_PIN) == LOW)
        {
            if (bombDisposalExpert.getStatus() != BOMB_DISPOSAL_EXPERT_STATUS_PLAYING)
            {
                bombDisposalExpert.select();
                tone(BUZZER_PIN, bombDisposalExpert.getSetting().isDevMode ? SILENCE_NOTE : ACTION_NOTE);
                delay(30);
                noTone(BUZZER_PIN, true);
                delay(300);
            }
        }
        if (digitalRead(BTN2_PIN) == LOW)
        {
            if (bombDisposalExpert.getStatus() != BOMB_DISPOSAL_EXPERT_STATUS_PLAYING)
            {
                bombDisposalExpert.start();
                tone(BUZZER_PIN, bombDisposalExpert.getSetting().isDevMode ? SILENCE_NOTE : ACTION_NOTE);
                delay(30);
                noTone(BUZZER_PIN, true);
                delay(300);
            }
        }
    }

    bombDisposalExpert.setLineStatus(0, digitalRead(LINE1_PIN));
    bombDisposalExpert.setLineStatus(1, digitalRead(LINE2_PIN));
    bombDisposalExpert.setLineStatus(2, digitalRead(LINE3_PIN));
    bombDisposalExpert.setLineStatus(3, digitalRead(LINE4_PIN));
    bombDisposalExpert.setLineStatus(4, digitalRead(LINE5_PIN));
}