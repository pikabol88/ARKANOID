#ifndef BONUS_H
#define BONUS_H
#pragma once
#include <SFML/Graphics.hpp>

#include "Object.h"
#include "Block.h"

class Bonus :public Object {

public:

    typedef enum bonusType {
        NONE,
        CHANGE_PADLE_SIZE = 1,
        CHANGE_BALL_SPEED = 2,
        STICK_BALL = 3,
        CHANCE = 4,
        MOVING_BLOCK = 5,
        SECOND_BALL = 6
    } bonusType_t;

    Bonus( int width, int height);
    ~Bonus();

    void createBonus(Block *block);
    void deleteBonus();
    void setBonusType();
    bonusType_t getBonusType();
    void update(float time);
    void activate();
    bool isActiv();
    bool isExist();
    bool isRun();
    void runBonus();

    void fail();

    bool inMove = true;

protected:
        
    bool run = 0;
    bonusType_t type;
    int lives = 0;
   
    bool activated = 0;

    virtual void loadSprites() override; 
};

#endif // !BONUS_H