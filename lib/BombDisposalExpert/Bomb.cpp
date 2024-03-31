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
            if (_decisecondsOnChangeFunc != nullptr)
            {
                _decisecondsOnChangeFunc(_deciseconds);
            }

            if (_deciseconds == 0)
            {
                _status = BOMB_STATUS_EXPLODING;
                if (_explodingFunc != nullptr)
                {
                    _explodingFunc();
                }
            }
        }
    }
    else if (_status == BOMB_STATUS_EXPLODING)
    {
        _status = BOMB_STATUS_EXPLODED;
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

void Bomb::defuse()
{
    _status = BOMB_STATUS_DEFUSED;
}

BombStatus Bomb::getStatus()
{
    return _status;
}

int Bomb::getDeciseconds()
{
    return _deciseconds;
}

void Bomb::setDecisecondsOnChangeFunc(std::function<void(int)> decisecondsOnChangeFunc)
{
    _decisecondsOnChangeFunc = decisecondsOnChangeFunc;
}

void Bomb::setExplodingFunc(std::function<void()> explodingFunc)
{
    _explodingFunc = explodingFunc;
}