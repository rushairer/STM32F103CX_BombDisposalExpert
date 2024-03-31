#ifndef __BOMB_H_
#define __BOMB_H_

#include <functional>

typedef enum
{
    BOMB_STATUS_NORMAL = 0,
    BOMB_STATUS_COUNTDOWN = 1,
    BOMB_STATUS_EXPLODING = 2,
    BOMB_STATUS_DEFUSED = 3,
    BOMB_STATUS_EXPLODED = 4,
} BombStatus;

class Bomb
{
public:
    Bomb();
    virtual ~Bomb();

    void setup();
    void loop();

    void start(int countDownSeconds);
    void defuse();
    void reset();
    BombStatus getStatus();
    int getDeciseconds();
    void setDecisecondsOnChangeFunc(std::function<void(int)> decisecondsOnChangeFunc);
    void setExplodingFunc(std::function<void()> explodingFunc);

protected:
    BombStatus _status;
    int _countDownSeconds;
    std::function<void(int)> _decisecondsOnChangeFunc;
    std::function<void()> _explodingFunc;

private:
    unsigned long _timer;
    int _deciseconds;
};

#endif