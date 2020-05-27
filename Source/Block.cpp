#include "Block.h"

Block::Block(int x, int y, int mapWidth, int mapHeight, int typeBlock){
    setX(x);
    setY(y);
    setWidth(mapWidth);
    setHeight(mapHeight);
    bonus = true;
    type = typeBlock;
    this->loadSprites();
};

Block::~Block() {
    setX(0);
    setY(0);
    setWidth(0);
    setHeight(0);
    resizeSprite(sf::Vector2f(0, 0));
}

void Block::loadSprites() {
    texture.loadFromFile("images\\usual_blocks.png");
    setSprites();
}

void Block::setSprites() {
    sprite.setTexture(texture);
    int width = TexSet::BLOCK_WIDTH;
    int height = TexSet::BLOCK_HEIGHT;
    sprite.setTextureRect(sf::IntRect(TexSet::BLOCK_X, TexSet::BLOCK_Y + height * type, width, height));
}

bool Block::isBonus() {
    return (bonus);
}

bool Block::destroyBlock(Score &score){
    coordinate.x = 0;
    coordinate.y = 0;
    size.x = 0;
    size.y = 0;
    sprite.setScale(0, 0);
    score.incrementScore(5);
    return true;
}