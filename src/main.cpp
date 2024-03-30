#include <Arduino.h>
#include <TM1638.h> // required because the way arduino deals with libraries
#include <TM1640.h>

#define ISDEV 1

#define SDA_PIN PB7
#define SCL_PIN PB6

#define BTN1_PIN PB3
#define BTN2_PIN PA15

#define BEE_PIN PA1

#define ACTION_NOTE 1175
#define DANGRE_NOTE 1319

#ifdef ISDEV
#define COUNT_NOTE 31
#else
#define COUNT_NOTE 880
#endif

#define LINE1_PIN PB12
#define LINE2_PIN PB13
#define LINE3_PIN PB14
#define LINE4_PIN PB15
#define LINE5_PIN PA8

TM1640 module(SDA_PIN, SCL_PIN, 4);

int number = 0;
int i = 0;

int notes[] = {
    31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 93,
    98, 104, 110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233,
    247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587,
    622, 659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397,
    1480, 1568, 1661, 1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960,
    3136, 3322, 3520, 3729, 3951, 4186, 4435, 4699, 4978};

void setup()
{
    pinMode(BTN1_PIN, INPUT_PULLUP);
    pinMode(BTN2_PIN, INPUT_PULLUP);

    pinMode(LINE1_PIN, INPUT_PULLUP);
    pinMode(LINE2_PIN, INPUT_PULLUP);
    pinMode(LINE3_PIN, INPUT_PULLUP);
    pinMode(LINE4_PIN, INPUT_PULLUP);
    pinMode(LINE5_PIN, INPUT_PULLUP);

    module.setDisplayToString("GAME");
    delay(100);
}

void loop()
{
    int notesLength = sizeof(notes) / sizeof(notes[0]);
    if (digitalRead(BTN1_PIN) == LOW)
    {
        if (i < notesLength - 1)
        {
            i = i + 1;
            number = notes[i];
            tone(BEE_PIN, number);
        }
    }
    if (digitalRead(BTN2_PIN) == LOW)
    {
        if (i >= 1)
        {
            i = i - 1;
            number = notes[i];
            tone(BEE_PIN, number);
        }
    }

    static unsigned long timer = millis();
    static int deciSeconds = 600;
    if (millis() - timer >= 100)
    {
        timer += 100;
        deciSeconds--; // 100 milliSeconds is equal to 1 deciSecond

        if (deciSeconds % 10 == 0)
        {
            tone(BEE_PIN, COUNT_NOTE);
        }

        if (deciSeconds == 0)
        { // Reset to 0 after counting for 1000 seconds.
            deciSeconds = 600;
        }
        module.setDisplayToDecNumber(deciSeconds, _BV(2));
    }
    else if (millis() - timer >= 30)
    {
        noTone(BEE_PIN, true);
    }
}