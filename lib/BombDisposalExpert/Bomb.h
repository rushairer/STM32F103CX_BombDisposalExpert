#ifndef __BOMB_H_
#define __BOMB_H_

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
    void reset();
    BombStatus getStatus();
    int getDeciseconds();

protected:
    BombStatus _status;
    int _countDownSeconds;

private:
    unsigned long _timer;
    int _deciseconds;
};

#endif