#include "thwgamehelper.h"

thwgamehelper::thwgamehelper(IS32FL3236A *device)
{
    _device = device;
}
void thwgamehelper::begin()
{
    _device->begin();
    _device->sleep(0);
    _device->setFrequency(1);
    _device->clear();
    _device->update();
}
void thwgamehelper::setParam()
{
    for (int i = 0; i < 20; i++)
    {
        _device->setLedParam(LED_NUM_RING[i], IS32FL3236A_IMAX3, 1);
        _device->setLedPwm(LED_NUM_RING[i], 0);
    }
    for (int i = 0; i < 5; i++)
    {
        _device->setLedParam(LED_PLAYER_1[i], IS32FL3236A_IMAX4, 1);
        _device->setLedPwm(LED_PLAYER_1[i], 0);
    }
    for (int i = 0; i < 5; i++)
    {
        _device->setLedParam(LED_PLAYER_2[i], IS32FL3236A_IMAX4, 1);
        _device->setLedPwm(LED_PLAYER_2[i], 0);
    }
    for (int i = 0; i < 4; i++)
    {
        _device->setLedParam(LED_DIFFICULTY[i], IS32FL3236A_IMAX4, 1);
        _device->setLedPwm(LED_DIFFICULTY[i], 0);
    }
    for (int i = 0; i < 2; i++)
    {
        _device->setLedParam(LED_PLAYER_NUM[i], IS32FL3236A_IMAX4, 1);
        _device->setLedPwm(LED_PLAYER_NUM[i], 0);
    }
    _device->update();
}
void thwgamehelper::ledtest(bool clear)
{
    for (int i = 0; i < 20; i++)
    {
        _device->setLedPwm(LED_NUM_RING[i], 255);
        _device->update();
    }
    for (int i = 0; i < 5; i++)
    {
        _device->setLedPwm(LED_PLAYER_1[i], 128);
        _device->update();
    }
    for (int i = 0; i < 5; i++)
    {
        _device->setLedPwm(LED_PLAYER_2[i], 128);
        _device->update();
    }
    for (int i = 0; i < 4; i++)
    {
        _device->setLedPwm(LED_DIFFICULTY[i], 255);
        _device->update();
    }
    for (int i = 0; i < 2; i++)
    {
        _device->setLedPwm(LED_PLAYER_NUM[i], 128);
        _device->update();
    }
    if (clear == 1)
    {
        delay(2000);
        _device->clear();
        _device->update();
    }
}
void thwgamehelper::setRing(uint8_t number, uint8_t dim, bool update)
{
    if (number > 19)
    {
        number = 19;
    }
    if (number < 0)
    {
        number = 0;
    }
    _device->setLedPwm(LED_NUM_RING[number], dim);
    if (update == 1)
    {
        _device->update();
    }
}
void thwgamehelper::setDifficulty(uint8_t difficulty)
{
    if (difficulty > 3)
    {
        difficulty = 3;
    }
    if (difficulty < 0)
    {
        difficulty = 0;
    }
    switch (difficulty)
    {
    case 0:
        _device->setLedPwm(LED_DIFFICULTY[0], 32);
        _device->setLedPwm(LED_DIFFICULTY[1], 0);
        _device->setLedPwm(LED_DIFFICULTY[2], 0);
        _device->setLedPwm(LED_DIFFICULTY[3], 0);
        _device->update();
        break;
    case 1:
        _device->setLedPwm(LED_DIFFICULTY[0], 0);
        _device->setLedPwm(LED_DIFFICULTY[1], 255);
        _device->setLedPwm(LED_DIFFICULTY[2], 0);
        _device->setLedPwm(LED_DIFFICULTY[3], 0);
        _device->update();
        break;
    case 2:
        _device->setLedPwm(LED_DIFFICULTY[0], 0);
        _device->setLedPwm(LED_DIFFICULTY[1], 0);
        _device->setLedPwm(LED_DIFFICULTY[2], 128);
        _device->setLedPwm(LED_DIFFICULTY[3], 0);
        _device->update();
        break;
    case 3:
        _device->setLedPwm(LED_DIFFICULTY[0], 0);
        _device->setLedPwm(LED_DIFFICULTY[1], 0);
        _device->setLedPwm(LED_DIFFICULTY[2], 0);
        _device->setLedPwm(LED_DIFFICULTY[3], 64);
        _device->update();
        break;

    default:
        break;
    }
}
void thwgamehelper::setPlayerNum(bool onetwo){
    if (onetwo == 0)
    {
        _device->setLedPwm(LED_PLAYER_NUM[0],48);
        _device->setLedPwm(LED_PLAYER_NUM[1],0);
        _device->update();
    }
    if (onetwo == 1)
    {
        _device->setLedPwm(LED_PLAYER_NUM[0],0);
        _device->setLedPwm(LED_PLAYER_NUM[1],48);
        _device->update();
    }  
}
void thwgamehelper::setScoreP1(uint8_t score)
{
    if (score > 5)
    {
        score = 5;
    }
    if (score < 0)
    {
        score = 0;
    }
    switch (score)
    {
    case 0:
        _device->setLedPwm(LED_PLAYER_1[0],0);
        _device->setLedPwm(LED_PLAYER_1[1],0);
        _device->setLedPwm(LED_PLAYER_1[2],0);
        _device->setLedPwm(LED_PLAYER_1[3],0);
        _device->setLedPwm(LED_PLAYER_1[4],0);
        _device->update();
        break;
    case 1:
        _device->setLedPwm(LED_PLAYER_1[0],48);
        _device->setLedPwm(LED_PLAYER_1[1],0);
        _device->setLedPwm(LED_PLAYER_1[2],0);
        _device->setLedPwm(LED_PLAYER_1[3],0);
        _device->setLedPwm(LED_PLAYER_1[4],0);
        _device->update();
        break;
    case 2:
        _device->setLedPwm(LED_PLAYER_1[0],48);
        _device->setLedPwm(LED_PLAYER_1[1],48);
        _device->setLedPwm(LED_PLAYER_1[2],0);
        _device->setLedPwm(LED_PLAYER_1[3],0);
        _device->setLedPwm(LED_PLAYER_1[4],0);
        _device->update();
        break;
    case 3:
        _device->setLedPwm(LED_PLAYER_1[0],48);
        _device->setLedPwm(LED_PLAYER_1[1],48);
        _device->setLedPwm(LED_PLAYER_1[2],48);
        _device->setLedPwm(LED_PLAYER_1[3],0);
        _device->setLedPwm(LED_PLAYER_1[4],0);
        _device->update();
        break;
    case 4:
        _device->setLedPwm(LED_PLAYER_1[0],48);
        _device->setLedPwm(LED_PLAYER_1[1],48);
        _device->setLedPwm(LED_PLAYER_1[2],48);
        _device->setLedPwm(LED_PLAYER_1[3],48);
        _device->setLedPwm(LED_PLAYER_1[4],0);
        _device->update();
        break;
    case 5:
        _device->setLedPwm(LED_PLAYER_1[0],48);
        _device->setLedPwm(LED_PLAYER_1[1],48);
        _device->setLedPwm(LED_PLAYER_1[2],48);
        _device->setLedPwm(LED_PLAYER_1[3],48);
        _device->setLedPwm(LED_PLAYER_1[4],48);
        _device->update();
        break;
    
    default:
        break;
    }
    
}
void thwgamehelper::setScoreP2(uint8_t score)
{
    if (score > 5)
    {
        score = 5;
    }
    if (score < 0)
    {
        score = 0;
    }
    switch (score)
    {
    case 0:
        _device->setLedPwm(LED_PLAYER_2[0],0);
        _device->setLedPwm(LED_PLAYER_2[1],0);
        _device->setLedPwm(LED_PLAYER_2[2],0);
        _device->setLedPwm(LED_PLAYER_2[3],0);
        _device->setLedPwm(LED_PLAYER_2[4],0);
        _device->update();
        break;
    case 1:
        _device->setLedPwm(LED_PLAYER_2[0],48);
        _device->setLedPwm(LED_PLAYER_2[1],0);
        _device->setLedPwm(LED_PLAYER_2[2],0);
        _device->setLedPwm(LED_PLAYER_2[3],0);
        _device->setLedPwm(LED_PLAYER_2[4],0);
        _device->update();
        break;
    case 2:
        _device->setLedPwm(LED_PLAYER_2[0],48);
        _device->setLedPwm(LED_PLAYER_2[1],48);
        _device->setLedPwm(LED_PLAYER_2[2],0);
        _device->setLedPwm(LED_PLAYER_2[3],0);
        _device->setLedPwm(LED_PLAYER_2[4],0);
        _device->update();
        break;
    case 3:
        _device->setLedPwm(LED_PLAYER_2[0],48);
        _device->setLedPwm(LED_PLAYER_2[1],48);
        _device->setLedPwm(LED_PLAYER_2[2],48);
        _device->setLedPwm(LED_PLAYER_2[3],0);
        _device->setLedPwm(LED_PLAYER_2[4],0);
        _device->update();
        break;
    case 4:
        _device->setLedPwm(LED_PLAYER_2[0],48);
        _device->setLedPwm(LED_PLAYER_2[1],48);
        _device->setLedPwm(LED_PLAYER_2[2],48);
        _device->setLedPwm(LED_PLAYER_2[3],48);
        _device->setLedPwm(LED_PLAYER_2[4],0);
        _device->update();
        break;
    case 5:
        _device->setLedPwm(LED_PLAYER_2[0],48);
        _device->setLedPwm(LED_PLAYER_2[1],48);
        _device->setLedPwm(LED_PLAYER_2[2],48);
        _device->setLedPwm(LED_PLAYER_2[3],48);
        _device->setLedPwm(LED_PLAYER_2[4],48);
        _device->update();
        break;
    
    default:
        break;
    }
    
}
float_t thwgamehelper::readVBat(float value){
    float analogVoltage = 0;
    float out = 0;
    analogVoltage = (float(value)/1024)*3.28;
    out = analogVoltage*1.667777777777;
    return out;
}