#ifndef __BOMB_DISPOSAL_EXPERT_H_
#define __BOMB_DISPOSAL_EXPERT_H_

#include "Bomb.h"
#include <TM1640.h>

typedef enum
{
    BOMB_DISPOSAL_EXPERT_STATUS_NORMAL = 0,
    BOMB_DISPOSAL_EXPERT_STATUS_PLAYING = 1,
    BOMB_DISPOSAL_EXPERT_STATUS_SETTING = 2,
    BOMB_DISPOSAL_EXPERT_STATUS_GAMEOVER = 3,
} BombDisposalExpertStatus;

typedef enum
{
    BOMB_DISPOSAL_EXPERT_SETTING_INDEX_SECONDS = 0,
    BOMB_DISPOSAL_EXPERT_SETTING_INDEX_DEVMODE = 1,
} BombDisposalExpertSettingIndex;

typedef struct
{
    unsigned int countDownSeconds;
    unsigned short isDevMode;
} BombDisposalExpertSetting;

class BombDisposalExpert
{
public:
    BombDisposalExpert(TM1640 *tm1640, int buzzerPin);
    virtual ~BombDisposalExpert();

    void setup();
    void loop();

    void reset();
    BombDisposalExpertStatus getStatus();
    BombDisposalExpertSetting getSetting();
    void select();
    void start();

protected:
    BombDisposalExpertStatus _status;
    Bomb _bomb;
    TM1640 *_tm1640;
    int _buzzerPin;
    BombDisposalExpertSetting _setting;
    BombDisposalExpertSettingIndex _settingIndex;

protected:
};

#endif