#include <Arduino.h>
#include <unity.h>
#include <TM1638.h> // required because the way arduino deals with libraries
#include <TM1640.h>
#include "Bomb.h"

#define SDA_PIN PB7
#define SCL_PIN PB6

#define BTN1_PIN PB3
#define BTN2_PIN PA15

TM1640 module(SDA_PIN, SCL_PIN, 4);
Bomb bomb;

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void setup()
{
    pinMode(BTN1_PIN, INPUT_PULLUP);
    pinMode(BTN2_PIN, INPUT_PULLUP);

    module.setDisplayToString("BOMB");
    delay(3000);
    module.clearDisplay();

    bomb.setup();
    bomb.setDecisecondsOnChangeFunc(
        [](int deciseconds)
        {
            module.setDisplayToDecNumber(deciseconds, _BV(2));
        });

    bomb.setExplodingFunc(
        []()
        {
            for (int i = 0; i < 3; i++)
            {
                module.setDisplayToString("    ");
                delay(300);
                module.setDisplayToString("0000");
                delay(300);
                module.setDisplayToString("8888");
                delay(300);
            }
        });
}

void loop()
{
    if (digitalRead(BTN1_PIN) == LOW && bomb.getStatus() == BOMB_STATUS_NORMAL)
    {
        bomb.start(10);
    }
    bomb.loop();
}