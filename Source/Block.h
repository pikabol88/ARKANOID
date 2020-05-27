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
        lgreen = 0,
        violet = 1,
        gray = 2,
        green = 3,
        yellow = 4,
        lblue = 5,
        orange = 6,
        blue = 7,
        red = 8
    } blockcolor_t;

    int type;
    int lives = 0;
    bool bonus = 1;

    virtual void loadSprites() override;

    void setSprites();

};

#endif // !BLOCK_H
