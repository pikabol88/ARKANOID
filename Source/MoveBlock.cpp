#include "MoveBlock.h"

MoveBlock::MoveBlock(int x, int y, int mapWidth, int mapHeight, int maxWidth, int minWidth, int type, int lifesCount):Block(x, y, mapWidth, mapHeight, type) {
    MAX_WIDTH = maxWidth;
    MIN_WIDTH = minWidth;
    lives = lifesCount * 2;
    setSpeed(Parameters::MOVING_BLOCK_SPEED);
    loadSprites();
}

void MoveBlock::move(float time) {
    chooseDirection();
    switch (direction) {
    case 0: displacement.x = getSpeed(); break;
    case 1: displacement.x = -getSpeed();  break;
    }
    setX(getX() + displacement.x * time);
    sprite.setPosition(getX(),getY());
}

void MoveBlock::chooseDirection() {
    if (getX() > MAX_WIDTH - getWidth() - getSpeed()) {
        direction = Parameters::LEFT;
    }
    if (getX() < MIN_WIDTH + getSpeed()) {
        direction = Parameters::RIGHT;
    }
}

bool MoveBlock::destroyBlock(Score &score) {
    lives--;
    if (lives == 0) {
        Block::destroyBlock(score);
        score.incrementScore(Parameters::SCORE_FOR_BLOCK);
        return true;
    }
    return false;
}
