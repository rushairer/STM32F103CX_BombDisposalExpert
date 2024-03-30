#include <Arduino.h>
#include <unity.h>
#include <TM1638.h> // required because the way arduino deals with libraries
#include <TM1640.h>

#define SDA_PIN PB7
#define SCL_PIN PB6

#define BTN1_PIN PB3
#define BTN2_PIN PA15

#define LINE1_PIN PB12
#define LINE2_PIN PB13
#define LINE3_PIN PB14
#define LINE4_PIN PB15
#define LINE5_PIN PA8

TM1640 module(SDA_PIN, SCL_PIN, 4);

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

    pinMode(LINE1_PIN, INPUT_PULLUP);
    pinMode(LINE2_PIN, INPUT_PULLUP);
    pinMode(LINE3_PIN, INPUT_PULLUP);
    pinMode(LINE4_PIN, INPUT_PULLUP);
    pinMode(LINE5_PIN, INPUT_PULLUP);

    module.setDisplayToString("pins");
    delay(3000);
}

void loop()
{
    module.setDisplayToString("....");
    module.clearDisplay();

    if (digitalRead(BTN1_PIN) == LOW)
    {
        module.setDisplayToString("B  1");
        delay(1000);
    }
    if (digitalRead(BTN2_PIN) == LOW)
    {
        module.setDisplayToString("B  2");
        delay(1000);
    }
    if (digitalRead(LINE1_PIN) == HIGH)
    {
        module.setDisplayToString("L  1");
        delay(1000);
    }
    if (digitalRead(LINE2_PIN) == HIGH)
    {
        module.setDisplayToString("L  2");
        delay(1000);
    }
    if (digitalRead(LINE3_PIN) == HIGH)
    {
        module.setDisplayToString("L  3");
        delay(1000);
    }
    if (digitalRead(LINE4_PIN) == HIGH)
    {
        module.setDisplayToString("L  4");
        delay(1000);
    }
    if (digitalRead(LINE5_PIN) == HIGH)
    {
        module.setDisplayToString("L  5");
        delay(1000);
    }
}