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
    texture.loadFromFile("images\\arkanoid.png");
    sprite.setTexture(texture);
    int width = Parameters::BLOCK_IMG_WIDTH;
    int height = Parameters::BLOCK_IMG_HEIGHT;

    switch (type) {
    case 0: sprite.setTextureRect(sf::IntRect(width * 2, height * 2, width, height));
        break;
    case 1: sprite.setTextureRect(sf::IntRect(width * 1, height * 5, width, height));
        break;
    case 2: sprite.setTextureRect(sf::IntRect(width * 1, height * 1, width, height));
        break;
    case 3: sprite.setTextureRect(sf::IntRect(width * 0, height * 1, width, height));
        break;
    case 4: sprite.setTextureRect(sf::IntRect(width * 1, height * 3, width, height));
        break;
    case 5: sprite.setTextureRect(sf::IntRect(width * 2, height * 2, width, height));
        break;
    case 6: sprite.setTextureRect(sf::IntRect(width * 0, height * 3, width, height));
        break;
    case 7: sprite.setTextureRect(sf::IntRect(width * 1, height * 6, width, height));
        break;
    case 8: sprite.setTextureRect(sf::IntRect(width * 2, height * 0, width, height));
        break;
    case 9: sprite.setTextureRect(sf::IntRect(width * 2, height * 4, width, height));
        break;
    default:
        break;
    }

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