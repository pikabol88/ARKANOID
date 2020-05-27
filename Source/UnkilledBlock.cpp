#include "UnkilledBlock.h"

UnkilledBlock::UnkilledBlock(int x, int y, int mapWidth, int mapHeight, int type, int lifesCount):Block(x,y,mapWidth,mapHeight,type) {   
    lives = lifesCount * 2;
    bonus = 0;
    loadSprites();
}

void UnkilledBlock::loadSprites() {
    texture.loadFromFile("images\\unkilled_blocks.png");
    setSprites();
}

bool UnkilledBlock::destroyBlock(Score &score) {
    lives--;
    score.incrementScore(1);
    if (lives == 0) {
        Block::destroyBlock(score);
        return true;
    }
    return false;
}