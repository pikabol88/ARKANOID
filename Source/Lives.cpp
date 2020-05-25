#include "Lives.h"

Live::Live(float coordinateX, float coordinateY,int liveW, int liveH) {
    setWidth(liveW);
    setHeight(liveH);
    setX(coordinateX);
    setY(coordinateY);
    loadSprites();
}

void Live::failLive() {
    sprite.setColor(sf::Color::Black);
}

void Live::drawingLive(sf::RenderWindow * m_window) {
    sprite.setPosition(getX(), getY());
    m_window->draw(sprite);
}

void Live::loadSprites() {
    texture.loadFromFile("images\\arkanoid.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(1637, 650, 65, 65));
    sprite.setScale(getWidth() / sprite.getLocalBounds().width, getHeight() / sprite.getLocalBounds().height);
}
