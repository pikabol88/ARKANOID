#ifndef STONEBLOCK_H
#define STONEBLOCK_H
#pragma once
#include "Block.h"

class StoneBlock : public Block {
public:
    StoneBlock(int x, int y, int mapWidth, int mapHeight, int type);
    
private:
    void loadSprites() override;
    bool destroyBlock(Score &score) override;
    void move(float time)override{};
};

#endif // !STONEBLOCK_H