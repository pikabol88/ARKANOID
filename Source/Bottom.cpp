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
    sprite.setTextureRect(sf::IntRect(0, 900, 1330, 80));
    sprite.setScale(getX() / sprite.getLocalBounds().width, getY() / sprite.getLocalBounds().height);
}