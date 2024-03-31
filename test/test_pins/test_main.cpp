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
    // module.clearDisplay();

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
        static unsigned long timer1 = millis();
        if (millis() - timer1 >= 600 && (millis() - timer1) < 2000)
        {
            module.setDisplayToString("L  1");
        }
        else if (millis() - timer1 > 2000)
        {
            timer1 = millis();
        }
    }
    if (digitalRead(LINE2_PIN) == HIGH)
    {
        static unsigned long timer2 = millis();
        if (millis() - timer2 >= 600 && (millis() - timer2) < 2000)
        {
            module.setDisplayToString("L  2");
        }
        else if (millis() - timer2 > 2000)
        {
            timer2 = millis();
        }
    }
    if (digitalRead(LINE3_PIN) == HIGH)
    {
        static unsigned long timer3 = millis();
        if (millis() - timer3 >= 600 && (millis() - timer3) < 2000)
        {
            module.setDisplayToString("L  3");
        }
        else if (millis() - timer3 > 2000)
        {
            timer3 = millis();
        }
    }
    if (digitalRead(LINE4_PIN) == HIGH)
    {
        static unsigned long timer4 = millis();
        if (millis() - timer4 >= 600 && (millis() - timer4) < 2000)
        {
            module.setDisplayToString("L  4");
        }
        else if (millis() - timer4 > 2000)
        {
            timer4 = millis();
        }
    }
    if (digitalRead(LINE5_PIN) == HIGH)
    {
        static unsigned long timer5 = millis();
        if (millis() - timer5 >= 600 && (millis() - timer5) < 2000)
        {
            module.setDisplayToString("L  5");
        }
        else if(millis() - timer5 > 2000)
        {
            timer5 = millis();
        }
    }
}