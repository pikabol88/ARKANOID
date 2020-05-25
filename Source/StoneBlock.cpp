#include "StoneBlock.h"

StoneBlock::StoneBlock(int x, int y, int mapWidth, int mapHeight, int type) :Block(x, y, mapWidth, mapHeight, type) {
    bonus = 0;
    loadSprites();
}

void StoneBlock::loadSprites() {
    texture.loadFromFile("images\\stoneblocks3.png");
    sprite.setTexture(texture);
    float width = Parameters::BLOCK_IMG_WIDTH;
    float height = Parameters::BLOCK_IMG_HEIGHT;
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

bool StoneBlock::destroyBlock(Score &score) { 
    return false;
}