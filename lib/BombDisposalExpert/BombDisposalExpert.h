#ifndef __BOMB_DISPOSAL_EXPERT_H_
#define __BOMB_DISPOSAL_EXPERT_H_

#include "Bomb.h"
#include <TM1640.h>

#define LINE_NUMBER 5

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
    BOMB_DISPOSAL_EXPERT_SETTING_INDEX_CHANGE_SECONDS = 1,
    BOMB_DISPOSAL_EXPERT_SETTING_INDEX_DEVMODE = 2,
} BombDisposalExpertSettingIndex;

typedef enum
{
    BOMB_DISPOSAL_EXPERT_LINE_TYPE_DANGER = 0,
    BOMB_DISPOSAL_EXPERT_LINE_TYPE_SAFE = 1,
    BOMB_DISPOSAL_EXPERT_LINE_TYPE_BAD = 2,
    BOMB_DISPOSAL_EXPERT_LINE_TYPE_GOOD = 3,
    BOMB_DISPOSAL_EXPERT_LINE_TYPE_NOTHING = 4,
} BombDisposalExpertLineType;

typedef struct
{
    unsigned int countDownSeconds;
    unsigned int changeSeconds;
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
    void setLineStatus(int number, int status);

protected:
    BombDisposalExpertStatus _status;
    Bomb _bomb;
    TM1640 *_tm1640;
    int _buzzerPin;
    BombDisposalExpertSetting _setting;
    BombDisposalExpertSettingIndex _settingIndex;
    int _lineStatus[LINE_NUMBER];
    unsigned long _lineTimers[LINE_NUMBER];
    BombDisposalExpertLineType _lines[LINE_NUMBER];
    void checkLine(int number);
    void shuffleArray(BombDisposalExpertLineType arr[], int size);
    void defusedAction();
    void explodingAction();
};

#endif