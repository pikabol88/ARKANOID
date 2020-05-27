#include "StoneBlock.h"

StoneBlock::StoneBlock(int x, int y, int mapWidth, int mapHeight, int type) :Block(x, y, mapWidth, mapHeight, type) {
    bonus = 0;
    loadSprites();
}

void StoneBlock::loadSprites() {
    texture.loadFromFile("images\\stone_blocks.png");
 }

bool StoneBlock::destroyBlock(Score &score) { 
    return false;
}