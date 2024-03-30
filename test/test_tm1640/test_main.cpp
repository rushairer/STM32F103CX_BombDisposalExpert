#include <Arduino.h>
#include <unity.h>
#include <TM1638.h> // required because the way arduino deals with libraries
#include <TM1640.h>
#include <TM16xxMatrix.h>

#define SDA_PIN PB7
#define SCL_PIN PB6

TM1640 module(SDA_PIN, SCL_PIN, 4);

#define MATRIX_NUMCOLUMNS 4
#define MATRIX_NUMROWS 8

TM16xxMatrix matrix(&module, MATRIX_NUMCOLUMNS, MATRIX_NUMROWS);

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
    module.setDisplayToString("test");
    delay(3000);
    module.clearDisplay();

    matrix.setAll(true);
    delay(200);

    for (int i = 0; i < MATRIX_NUMCOLUMNS; i++)
    {
        for (int j = 0; j <= 0xFF; j++)
        {
            matrix.setColumn(i, j);
            delay(5);
        }
        delay(200);
    }
    matrix.setAll(false);

    for (int i = 0; i < MATRIX_NUMROWS; i++)
    {
        for (int j = 0; j < MATRIX_NUMCOLUMNS; j++)
        {
            matrix.setPixel(j, i, true);
            delay(50);
            matrix.setPixel(j, i, false);
        }
    }

    UNITY_BEGIN(); // IMPORTANT LINE!
}

void loop()
{
    static unsigned long timer = millis();
    static int deciSeconds = 600;
    if (millis() - timer >= 100)
    {
        timer += 100;
        deciSeconds--; // 100 milliSeconds is equal to 1 deciSecond

        if (deciSeconds == 0)
        {
            UNITY_END(); // stop unit testing
        }
        module.setDisplayToDecNumber(deciSeconds, _BV(2));
    }
}