#include "Ball.h"
#include "Score.h"


void Ball::checkMapCollision(Map &map, Bonus *bonus, Score *score, int type) {
    float *delta = nullptr;
    (type == 0) ? (delta = &displacement.x) : (delta = &displacement.y);
    sf::Vector2i blockCount(map.getBlocksCount());
    for (int i = 0; i < blockCount.x; i++) {
        for (int j = 0; j < blockCount.y; j++) {
            if (checkBlockVerticalCollision(map, bonus,  map.blocks[i][j], score)) {
                *delta = -*(delta);
            }
            else if (checkBlockHorizontalCollision(map, bonus, map.blocks[i][j], score)) {
                *delta = -*(delta);
            }
        }
    }
    if (map.moveBlock) {
        if (checkBlockVerticalCollision(map, bonus, map.moveBlock,score)){
            *delta = -*(delta);
        }
        else if (checkBlockHorizontalCollision(map, bonus, map.moveBlock,score)) {
            *delta = -*(delta);
        }
    }
}

bool Ball::checkBlockVerticalCollision(Map &map,Bonus *bonus, Block *block, Score *score) {
    if (sf::FloatRect(getX() + getWidth() / 2, getY(), 1, getHeight()).intersects(block->getGlobalBounds())) {
        checkBonusCollision(bonus, block);
        if (!block->destroyBlock(*score)) {
            if ((block->hitCount++) % 2 != 0) {
                return true;
            }
        } else {
            map.decrementBlockCount();
            return true;
        }
    }
    return false;
}

bool Ball::checkBlockHorizontalCollision(Map &map,Bonus *bonus, Block *block, Score *score) {
    if (sf::FloatRect(getX(), getY() + getHeight() / 2, getWidth(), 1).intersects(block->getGlobalBounds())) {
        checkBonusCollision(bonus, block);
        if (!block->destroyBlock(*score)) {
            if ((block->hitCount++) % 2 != 0) {
                return true;
            }
        }  else {
            map.decrementBlockCount();
            return true;
        }
    }
    return false;
}

void Ball::checkBonusCollision(Bonus *bonus, Block *block) {
    if (!bonus->isExist()) {
        if (block->isBonus()) {
            bonus->createBonus(block);
        } else {
            bonus->deleteBonus();
        }
    }
}


void Ball::checkWallCollision(int winH) {
    if (getX() < 0 || getX() + getWidth() > winH) {
        displacement.x = -displacement.x;
    }
    if (getY() < 0) {
        displacement.y = -displacement.y;
    }
}

bool Ball::checkPadleCollision(Object &paddle) {
    if (sf::FloatRect(getX(), getY(), getWidth(), getHeight()).intersects(paddle.getGlobalBounds())) {
        displacement.y = -displacement.y;
        return 1;
    }
}

void Ball::checkAnotherBallCollision(Object &secondBall) {
        if (this->getRect().intersects(secondBall.getGlobalBounds())) {
            displacement.x = -displacement.x;
        }
    
}