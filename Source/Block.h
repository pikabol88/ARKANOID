#ifndef BLOCK_H
#define BLOCK_H
#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Score.h"

class Block :public Object {

public:

    Block(int x, int y, int mapWidth, int mapHeight, int typeBlock);
    ~Block();

    virtual bool destroyBlock(Score &score);    
    virtual void move(float time) {};
    bool isBonus();
    unsigned int hitCount;

protected:

    typedef enum blockcolor {
        blue = 0,
        lblue = 1,
        green = 2,
        lgreen = 3,
        yellow = 4,
        red = 5,
        voilet = 6,
        brown = 7,
        orange = 8,
        gray = 9
    } blockcolor_t;

    int type;
    int lives = 0;
    bool bonus = 1;

    virtual void loadSprites() override;

};

#endif // !BLOCK_H
