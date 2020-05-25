#ifndef MOVEBLOCK_H
#define MOVEBLOCK_H
#pragma once
#include "Block.h"

class MoveBlock : public Block {
public:
    MoveBlock(int x, int y, int mapWidth, int mapHeight, int maxWidth, int minWidth, int type, int lifesCount);
    void move(float time) override;

private:

    int direction;
    int MAX_WIDTH;
    int MIN_WIDTH;
    void chooseDirection();
    bool destroyBlock(Score &score) override;
};

#endif // !MOVEBLOCK_H