#ifndef _thwgamehelper_h
#define _thwgamehelper_h

#include <Arduino.h>
#include <IS32FL3236A.h>

class thwgamehelper
{
public:
    explicit thwgamehelper(IS32FL3236A *device);
    void begin();
    void setParam();
    void ledtest();
    void setRing(uint8_t number, uint8_t dim, bool update = 1);
    void setDifficulty(uint8_t difficulty);
    void setPlayerNum(bool onetwo);
    void setScoreP1(uint8_t score);
    void setScoreP2(uint8_t score);
    float_t readVBat(float value);
private:
    uint8_t LED_NUM_RING[20] = {12,13,14,15,16,23,29,30,31,32,33,34,35,0,1,2,3,4,5,6};
    uint8_t LED_PLAYER_1[5]  = {28,27,26,25,24};
    uint8_t LED_PLAYER_2[5]  = {11,10,9,8,7};
    uint8_t LED_DIFFICULTY[4]= {20,19,18,17};
    uint8_t LED_PLAYER_NUM[2]= {21,22};
    IS32FL3236A* _device;
};


#endif