#ifndef UNKILLEDBLOCK_H
#define UNKILLEDBLOCK_H
#pragma once
#include "Block.h"

class UnkilledBlock: public Block {
public:
    UnkilledBlock(int x, int y, int mapWidth, int mapHeight, int type, int lives);

private:
    void loadSprites() override;
    bool destroyBlock(Score & score) override;
    void move(float timeoverride) {};
};

#endif // !UNKILLEDBLOCK_H