#include "Bomb.h"
#include <Arduino.h>

Bomb::Bomb()
{
}

Bomb::~Bomb()
{
}
void Bomb::setup()
{
    reset();
}

void Bomb::loop()
{
    if (_status == BOMB_STATUS_COUNTDOWN)
    {
        if (millis() - _timer >= 100)
        {
            _timer += 100;
            _deciseconds--;

            if (_deciseconds == 0)
            {
                _status = BOMB_STATUS_EXPLODING;
            }
        }
    }
    else if (_status == BOMB_STATUS_EXPLODING)
    {
    }
}

void Bomb::reset()
{
    _status = BOMB_STATUS_NORMAL;
    _deciseconds = 0;
    _timer = 0;
}

void Bomb::start(int countDownSeconds)
{
    _deciseconds = countDownSeconds * 10;
    _timer = millis();
    _status = BOMB_STATUS_COUNTDOWN;
}

BombStatus Bomb::getStatus()
{
    return _status;
}

int Bomb::getDeciseconds()
{
    return _deciseconds;
}