#include "UnkilledBlock.h"

UnkilledBlock::UnkilledBlock(int x, int y, int mapWidth, int mapHeight, int type, int lifesCount):Block(x,y,mapWidth,mapHeight,type) {   
    lives = lifesCount * 2;
    bonus = 0;
    loadSprites();
}

void UnkilledBlock::loadSprites() {
    texture.loadFromFile("images\\arkanoid.png");
    sprite.setTexture(texture);
    float width = Parameters::BLOCK_IMG_WIDTH;
    float height = Parameters::BLOCK_IMG_HEIGHT;
    switch (type)
    {
    case 0: sprite.setTextureRect(sf::IntRect(width * 0, height * 0, width, height));
        break;
    case 1: sprite.setTextureRect(sf::IntRect(width * 1, height * 4, width, height));
        break;
    case 2: sprite.setTextureRect(sf::IntRect(width * 1, height * 0, width, height));
        break;
    case 3: sprite.setTextureRect(sf::IntRect(width * 0, height * 2, width, height));
        break;
    case 4: sprite.setTextureRect(sf::IntRect(width * 1, height * 2, width, height));
        break;
    case 5: sprite.setTextureRect(sf::IntRect(width * 2, height * 1, width, height));
        break;
    case 6: sprite.setTextureRect(sf::IntRect(width * 0, height * 4, width, height));
        break;
    case 7: sprite.setTextureRect(sf::IntRect(width * 0, height * 6, width, height));
        break;
    case 8: sprite.setTextureRect(sf::IntRect(width * 2, height * 5, width, height));
        break;
    case 9: sprite.setTextureRect(sf::IntRect(width * 0, height * 5, width, height));
        break;
    default:
        break;
    }

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