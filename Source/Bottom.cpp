#include "Bottom.h"

Bottom::Bottom(int x, int y, int width, int height) {
    coordinate.x = x;
    coordinate.y = y;
    setWidth(width);
    setHeight(height);
    loadSprites();
}

Bottom::~Bottom(){}

void Bottom::loadSprites() {
    texture.loadFromFile("images\\bottom.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(TexSet::BOTTOM_X, TexSet::BOTTOM_Y, TexSet::BOTTOM_WIDTH, TexSet::BALL_HEIGHT));
    sprite.setScale(getWidth() / sprite.getLocalBounds().width, getHeight() / sprite.getLocalBounds().height);
}