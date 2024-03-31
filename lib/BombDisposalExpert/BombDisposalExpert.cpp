#include "BombDisposalExpert.h"

#define SILENCE_NOTE 31
#define COUNT_NOTE 880
#define ACTION_NOTE 1175
#define DANGRE_NOTE 1319

BombDisposalExpert::BombDisposalExpert(TM1640 *tm1640, int buzzerPin)
    : _tm1640(tm1640),
      _buzzerPin(buzzerPin),
      _lines{BOMB_DISPOSAL_EXPERT_LINE_TYPE_DANGER,
             BOMB_DISPOSAL_EXPERT_LINE_TYPE_SAFE,
             BOMB_DISPOSAL_EXPERT_LINE_TYPE_BAD,
             BOMB_DISPOSAL_EXPERT_LINE_TYPE_GOOD,
             BOMB_DISPOSAL_EXPERT_LINE_TYPE_NOTHING}
{
}

BombDisposalExpert::~BombDisposalExpert()
{
    _tm1640 = nullptr;
}

void BombDisposalExpert::setup()
{
    _setting.countDownSeconds = 60;
    _setting.changeSeconds = 20;
    _setting.isDevMode = 1;
    _settingIndex = BOMB_DISPOSAL_EXPERT_SETTING_INDEX_SECONDS;
    reset();
    _bomb.setup();
    _bomb.setDecisecondsOnChangeFunc(
        [this](int deciseconds)
        {
            this->_tm1640->setDisplayToDecNumber(deciseconds, _BV(2));
            static unsigned long toneTimer = millis();
            if (deciseconds != 0 && deciseconds % 10 == 0)
            {
                toneTimer = millis();
            }
            if (millis() - toneTimer < 30)
            {
                tone(_buzzerPin, _setting.isDevMode ? SILENCE_NOTE : COUNT_NOTE);
            }
            else
            {
                noTone(_buzzerPin, true);
            }
        });
    _bomb.setExplodingFunc(
        [this]()
        {
            tone(_buzzerPin, _setting.isDevMode ? SILENCE_NOTE : DANGRE_NOTE);
            for (int i = 0; i < 3; i++)
            {
                this->_tm1640->setDisplayToString("    ");
                delay(300);
                this->_tm1640->setDisplayToString("0000");
                delay(300);
                this->_tm1640->setDisplayToString("8888");
                delay(300);
            }
            this->_status = BOMB_DISPOSAL_EXPERT_STATUS_GAMEOVER;
            noTone(this->_buzzerPin, true);
        });
}

void BombDisposalExpert::loop()
{
    _bomb.loop();
    if (_status == BOMB_DISPOSAL_EXPERT_STATUS_NORMAL)
    {
        static unsigned long screenTimer = millis();
        if (millis() - screenTimer <= 500)
        {
            int hasError = 0;
            for (int i = 0; i < LINE_NUMBER; i++)
            {
                if (_lineStatus[i] == HIGH)
                {
                    hasError = 1;
                    break;
                }
            }
            if (hasError)
            {
                _tm1640->setDisplayToString("----");
            }
            else
            {
                _tm1640->setDisplayToString("BOMB");
            }
        }
        else if (millis() - screenTimer > 500 && millis() - screenTimer <= 1000)
        {
            _tm1640->clearDisplay();
        }
        else
        {
            screenTimer = millis();
        }
    }
    else if (_status == BOMB_DISPOSAL_EXPERT_STATUS_SETTING)
    {
        char text[4];
        switch (_settingIndex)
        {
        case BOMB_DISPOSAL_EXPERT_SETTING_INDEX_DEVMODE:
            sprintf(text, "D  %d", _setting.isDevMode);
            break;
        case BOMB_DISPOSAL_EXPERT_SETTING_INDEX_SECONDS:
        default:
            if (_setting.countDownSeconds > 99)
            {
                sprintf(text, "S%d", _setting.countDownSeconds);
            }
            else if (_setting.countDownSeconds < 9)
            {
                sprintf(text, "S  %d", _setting.countDownSeconds);
            }
            else
            {
                sprintf(text, "S %d", _setting.countDownSeconds);
            }
            break;
        }
        _tm1640->setDisplayToString(text);
    }
    else if (_status == BOMB_DISPOSAL_EXPERT_STATUS_GAMEOVER)
    {
        _tm1640->setDisplayToString("OVER");
    }
}

void BombDisposalExpert::reset()
{
    _status = BOMB_DISPOSAL_EXPERT_STATUS_NORMAL;
    _bomb.reset();

    for (int i = 0; i < LINE_NUMBER; i++)
    {
        _lineStatus[i] = LOW;
    }

    _lines[0] = BOMB_DISPOSAL_EXPERT_LINE_TYPE_DANGER;
    _lines[1] = BOMB_DISPOSAL_EXPERT_LINE_TYPE_SAFE;
    _lines[2] = BOMB_DISPOSAL_EXPERT_LINE_TYPE_BAD;
    _lines[3] = BOMB_DISPOSAL_EXPERT_LINE_TYPE_GOOD;
    _lines[4] = BOMB_DISPOSAL_EXPERT_LINE_TYPE_NOTHING;

    shuffleArray(_lines, LINE_NUMBER);
}

BombDisposalExpertStatus BombDisposalExpert::getStatus()
{
    return _status;
}

BombDisposalExpertSetting BombDisposalExpert::getSetting()
{
    return _setting;
}

void BombDisposalExpert::select()
{
    if (_status == BOMB_DISPOSAL_EXPERT_STATUS_NORMAL)
    {
        _status = BOMB_DISPOSAL_EXPERT_STATUS_SETTING;
        _settingIndex = BOMB_DISPOSAL_EXPERT_SETTING_INDEX_SECONDS;
    }
    else if (_status == BOMB_DISPOSAL_EXPERT_STATUS_SETTING)
    {
        if ((int)_settingIndex + 1 > (int)BOMB_DISPOSAL_EXPERT_SETTING_INDEX_DEVMODE)
        {
            _status = BOMB_DISPOSAL_EXPERT_STATUS_NORMAL;
        }
        else
        {
            _settingIndex = BombDisposalExpertSettingIndex((int)_settingIndex + 1);
        }
    }
    else if (_status == BOMB_DISPOSAL_EXPERT_STATUS_GAMEOVER)
    {
        _status = BOMB_DISPOSAL_EXPERT_STATUS_NORMAL;
    }
}

void BombDisposalExpert::start()
{
    if (_status == BOMB_DISPOSAL_EXPERT_STATUS_NORMAL)
    {
        _status = BOMB_DISPOSAL_EXPERT_STATUS_PLAYING;
        _bomb.start(_setting.countDownSeconds);
    }
    else if (_status == BOMB_DISPOSAL_EXPERT_STATUS_SETTING)
    {
        switch (_settingIndex)
        {
        case BOMB_DISPOSAL_EXPERT_SETTING_INDEX_DEVMODE:
            _setting.isDevMode = !_setting.isDevMode;
            break;
        case BOMB_DISPOSAL_EXPERT_SETTING_INDEX_SECONDS:
            _setting.countDownSeconds = _setting.countDownSeconds + 10;
            if (_setting.countDownSeconds > 120)
            {
                _setting.countDownSeconds = 10;
            }
        default:
            break;
        }
    }
    else if (_status == BOMB_DISPOSAL_EXPERT_STATUS_GAMEOVER)
    {
        _status = BOMB_DISPOSAL_EXPERT_STATUS_NORMAL;
    }
}

void BombDisposalExpert::setLineStatus(int number, int status)
{
    if (_status == BOMB_DISPOSAL_EXPERT_STATUS_PLAYING)
    {
        if (status == HIGH && _lineStatus[number] == LOW)
        {
            if (millis() - _lineTimers[number] > 300)
            {
                _lineStatus[number] = status;
                _lineTimers[number] = millis();

                _tm1640->setDisplayToDecNumber(_lines[number]);
                checkLine(number);

                noTone(_buzzerPin, true);
                delay(1000);
            }
        }
    }
    else if (_status == BOMB_DISPOSAL_EXPERT_STATUS_NORMAL)
    {
        _lineStatus[number] = status;
    }
}

void BombDisposalExpert::checkLine(int number)
{

    switch (_lines[number])
    {
    case BOMB_DISPOSAL_EXPERT_LINE_TYPE_DANGER:
        _bomb.setDeciseconds(0);
        break;
    case BOMB_DISPOSAL_EXPERT_LINE_TYPE_BAD:
        _bomb.setDeciseconds(_bomb.getDeciseconds() > _setting.changeSeconds * 10 ? _bomb.getDeciseconds() - _setting.changeSeconds * 10 : 0);
        break;
    case BOMB_DISPOSAL_EXPERT_LINE_TYPE_GOOD:
        _bomb.setDeciseconds(_bomb.getDeciseconds() + _setting.changeSeconds * 10);
        break;
    case BOMB_DISPOSAL_EXPERT_LINE_TYPE_SAFE:
        _bomb.defuse();
        defusedAction();
        break;
    case BOMB_DISPOSAL_EXPERT_LINE_TYPE_NOTHING:
    default:
        break;
    }

    _lines[number] = BOMB_DISPOSAL_EXPERT_LINE_TYPE_NOTHING;
}

void BombDisposalExpert::defusedAction()
{
    for (int i = 0; i < 3; i++)
    {
        this->_tm1640->setDisplayToString("    ");
        delay(300);
        this->_tm1640->setDisplayToString("GOOD");
        delay(300);
        this->_tm1640->setDisplayToString("VVVV");
        delay(300);
    }
    this->_status = BOMB_DISPOSAL_EXPERT_STATUS_GAMEOVER;
}

void BombDisposalExpert::shuffleArray(BombDisposalExpertLineType arr[], int size)
{
    for (int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        BombDisposalExpertLineType temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}